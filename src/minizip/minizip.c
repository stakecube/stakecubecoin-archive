/* minizip.c
   Version 1.1, February 14h, 2010
   sample part of the MiniZip project

   Copyright (C) 1998-2010 Gilles Vollant
     http://www.winimage.com/zLibDll/minizip.html
   Modifications of Unzip for Zip64
     Copyright (C) 2007-2008 Even Rouault
   Modifications for Zip64 support
     Copyright (C) 2009-2010 Mathias Svensson
     http://result42.com

   This program is distributed under the terms of the same license as zlib.
   See the accompanying LICENSE file for the full text of the license.
*/

#if (!defined(_WIN32)) && (!defined(WIN32)) && (!defined(__APPLE__))
#  ifndef __USE_FILE_OFFSET64
#    define __USE_FILE_OFFSET64
#  endif
#  ifndef __USE_LARGEFILE64
#    define __USE_LARGEFILE64
#  endif
#  ifndef _LARGEFILE64_SOURCE
#    define _LARGEFILE64_SOURCE
#  endif
#  ifndef _FILE_OFFSET_BIT
#    define _FILE_OFFSET_BIT 64
#  endif
#endif

#ifdef __APPLE__
/* In darwin and perhaps other BSD variants off_t is a 64 bit value, hence no need for specific 64 bit functions */
#  define FOPEN_FUNC(filename, mode) fopen(filename, mode)
#  define FTELLO_FUNC(stream) ftello(stream)
#  define FSEEKO_FUNC(stream, offset, origin) fseeko(stream, offset, origin)
#else
#  define FOPEN_FUNC(filename, mode) fopen64(filename, mode)
#  define FTELLO_FUNC(stream) ftello64(stream)
#  define FSEEKO_FUNC(stream, offset, origin) fseeko64(stream, offset, origin)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include <assert.h>

#ifdef _WIN32
#  include <direct.h>
#  include <io.h>
#else
#  include <unistd.h>
#  include <utime.h>
#  include <sys/types.h>
#  include <sys/stat.h>
#endif

#include "zip.h"
#include "minizip.h"

#ifdef _WIN32
#  define USEWIN32IOAPI
#  include "iowin32.h"
#endif

#define WRITEBUFFERSIZE (16384)
#define MAXFILENAME     (256)

#define ERRORBUFSIZE    (256)
static error_callback printf_err = NULL;

static uLong filetime(const char *filename, tm_zip *tmzip, uLong *dostime)
{
    int ret = 0;
#ifdef _WIN32
    FILETIME ftLocal;
    HANDLE hFind;
    WIN32_FIND_DATAA ff32;

    hFind = FindFirstFileA(filename, &ff32);
    if (hFind != INVALID_HANDLE_VALUE)
    {
        FileTimeToLocalFileTime(&(ff32.ftLastWriteTime), &ftLocal);
        FileTimeToDosDateTime(&ftLocal,((LPWORD)dostime)+1,((LPWORD)dostime)+0);
        FindClose(hFind);
        ret = 1;
    }
#else
#if defined unix || defined __APPLE__
    struct stat s = {0};
    struct tm* filedate;
    time_t tm_t = 0;

    if (strcmp(filename,"-") != 0)
    {
        char name[MAXFILENAME+1];
        int len = strlen(filename);
        if (len > MAXFILENAME)
            len = MAXFILENAME;

        strncpy(name, filename, MAXFILENAME - 1);
        name[MAXFILENAME] = 0;

        if (name[len - 1] == '/')
            name[len - 1] = 0;

        /* not all systems allow stat'ing a file with / appended */
        if (stat(name,&s) == 0)
        {
            tm_t = s.st_mtime;
            ret = 1;
        }
    }

    filedate = localtime(&tm_t);

    tmzip->tm_sec  = filedate->tm_sec;
    tmzip->tm_min  = filedate->tm_min;
    tmzip->tm_hour = filedate->tm_hour;
    tmzip->tm_mday = filedate->tm_mday;
    tmzip->tm_mon  = filedate->tm_mon ;
    tmzip->tm_year = filedate->tm_year;
#endif
#endif
    return ret;
}

static int check_file_exists(const char* filename)
{
    FILE* ftestexist = FOPEN_FUNC(filename,"rb");
    if (ftestexist == NULL)
        return 0;
    fclose(ftestexist);
    return 1;
}

static int is_large_file(const char* filename)
{
    ZPOS64_T pos = 0;
    FILE* pFile = FOPEN_FUNC(filename, "rb");
    char errbuf[ERRORBUFSIZE] = {0};

    if (pFile == NULL)
        return 0;

    FSEEKO_FUNC(pFile, 0, SEEK_END);
    pos = FTELLO_FUNC(pFile);
    fclose(pFile);

    snprintf(errbuf, ERRORBUFSIZE, "File : %s is %lld bytes\n", filename, pos);
    printf_err(errbuf);

    return (pos >= 0xffffffff);
}

/* Calculate the CRC32 of a file, because to encrypt a file, we need known the CRC32 of the file before */
static int get_file_crc(const char* filenameinzip, void *buf, unsigned long size_buf, unsigned long* result_crc)
{
    FILE *fin = NULL;
    unsigned long calculate_crc = 0;
    unsigned long size_read = 0;
    int err = ZIP_OK;
    char errbuf[ERRORBUFSIZE] = {0};

    fin = FOPEN_FUNC(filenameinzip,"rb");
    if (fin == NULL)
        err = ZIP_ERRNO;
    else
    {
        do
        {
            size_read = (int)fread(buf,1,size_buf,fin);

            if ((size_read < size_buf) && (feof(fin) == 0))
            {
                snprintf(errbuf, ERRORBUFSIZE, "error in reading %s\n",filenameinzip);
                printf_err(errbuf);
                err = ZIP_ERRNO;
            }

            if (size_read > 0)
                calculate_crc = crc32(calculate_crc,buf,size_read);
        }
        while ((err == ZIP_OK) && (size_read > 0));
    }

    if (fin)
        fclose(fin);

    snprintf(errbuf, ERRORBUFSIZE, "file %s crc %lx\n", filenameinzip, calculate_crc);
    printf_err(errbuf);
    *result_crc = calculate_crc;
    return err;
}

extern int ZEXPORT main_zip(int argc, const char *argv[], error_callback fptr)
{
    printf_err = fptr;
    char errbuf[ERRORBUFSIZE] = {0};

    zipFile zf = NULL;
#ifdef USEWIN32IOAPI
    zlib_filefunc64_def ffunc = {0};
#endif
    const char *zipfilename = NULL;
    const char* password = NULL;
    const int size_buf = WRITEBUFFERSIZE;
    Bytef buf[WRITEBUFFERSIZE] = {0};
    int zipfilenamearg = 0;
    int errclose = 0;
    int err = 0;
    int i = 0;
    int opt_overwrite = APPEND_STATUS_CREATE;
    int opt_compress_level = Z_DEFAULT_COMPRESSION;
    int opt_exclude_path = 0;

    if (argc <= 1)
    {
        printf_err("missing input arguments\n");
        return 1;
    }

    /* Parse command line options */
    for (i = 1; i < argc; i++)
    {
        if ((*argv[i]) == '-')
        {
            const char *p = argv[i]+1;

            while ((*p) != '\0')
            {
                char c = *(p++);;
                if ((c == 'o') || (c == 'O'))
                    opt_overwrite = APPEND_STATUS_CREATEAFTER;
                if ((c == 'a') || (c == 'A'))
                    opt_overwrite = APPEND_STATUS_ADDINZIP;
                if ((c >= '0') && (c <= '9'))
                    opt_compress_level = (c - '0');
                if ((c == 'j') || (c == 'J'))
                    opt_exclude_path = 1;

                if (((c == 'p') || (c == 'P')) && (i+1 < argc))
                {
                    password=argv[i+1];
                    i++;
                }
            }
        }
        else
        {
            if (zipfilenamearg == 0)
                zipfilenamearg = i;
        }
    }

    if (zipfilenamearg == 0)
    {
        printf_err("missing zip filename argument\n");
        return 1;
    }
    zipfilename = argv[zipfilenamearg];

    if (opt_overwrite == 2)
    {
        /* If the file don't exist, we not append file */
        if (check_file_exists(zipfilename) == 0)
            opt_overwrite = 1;
    }
    else if (opt_overwrite == 0)
    {
        /* If ask the user what to do because append and overwrite args not set */
        if (check_file_exists(zipfilename) != 0)
        {
            snprintf(errbuf, ERRORBUFSIZE, "The file %s exists\n", zipfilename);
            printf_err(errbuf);
            return 1;
        }
    }

#ifdef USEWIN32IOAPI
    fill_win32_filefunc64A(&ffunc);
    zf = zipOpen2_64(zipfilename, opt_overwrite, NULL, &ffunc);
#else
    zf = zipOpen64(zipfilename, opt_overwrite);
#endif

    if (zf == NULL)
    {
        snprintf(errbuf, ERRORBUFSIZE, "error opening %s\n", zipfilename);
        printf_err(errbuf);
        err = ZIP_ERRNO;
    }
    else {
        snprintf(errbuf, ERRORBUFSIZE, "creating %s\n", zipfilename);
        printf_err(errbuf);
    }

    /* Go through command line args looking for files to add to zip */
    for (i = zipfilenamearg + 1; (i < argc) && (err == ZIP_OK); i++)
    {
        FILE *fin = NULL;
        int size_read = 0;
        const char* filenameinzip = argv[i];
        const char *savefilenameinzip;
        zip_fileinfo zi = {0};
        unsigned long crcFile = 0;
        int zip64 = 0;

        /* Skip command line options */
        if ((((*(argv[i])) == '-') || ((*(argv[i])) == '/')) && (strlen(argv[i]) == 2) &&
            ((argv[i][1] == 'o') || (argv[i][1] == 'O') || (argv[i][1] == 'a') || (argv[i][1] == 'A') ||
             (argv[i][1] == 'p') || (argv[i][1] == 'P') || ((argv[i][1] >= '0') && (argv[i][1] <= '9'))))
            continue;

        /* Get information about the file on disk so we can store it in zip */
        filetime(filenameinzip, &zi.tmz_date, &zi.dosDate);

        if ((password != NULL) && (err == ZIP_OK))
            err = get_file_crc(filenameinzip, buf, size_buf, &crcFile);

        zip64 = is_large_file(filenameinzip);

        /* Construct the filename that our file will be stored in the zip as.
           The path name saved, should not include a leading slash.
           If it did, windows/xp and dynazip couldn't read the zip file. */

        savefilenameinzip = filenameinzip;
        while (savefilenameinzip[0] == '\\' || savefilenameinzip[0] == '/')
            savefilenameinzip++;

        /* Should the file be stored with any path info at all? */
        if (opt_exclude_path)
        {
            const char *tmpptr = NULL;
            const char *lastslash = 0;

            for (tmpptr = savefilenameinzip; *tmpptr; tmpptr++)
            {
                if (*tmpptr == '\\' || *tmpptr == '/')
                    lastslash = tmpptr;
            }

            if (lastslash != NULL)
                savefilenameinzip = lastslash + 1; /* base filename follows last slash. */
        }

        /* Add to zip file */
        err = zipOpenNewFileInZip3_64(zf, savefilenameinzip, &zi,
                    NULL, 0, NULL, 0, NULL /* comment*/,
                    (opt_compress_level != 0) ? Z_DEFLATED : 0,
                    opt_compress_level,0,
                    /* -MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY, */
                    -MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY,
                    password, crcFile, zip64);

        if (err != ZIP_OK) {
            snprintf(errbuf, ERRORBUFSIZE, "error in opening %s in zipfile (%d)\n", filenameinzip, err);
            printf_err(errbuf);
        }
        else
        {
            fin = FOPEN_FUNC(filenameinzip, "rb");
            if (fin == NULL)
            {
                err = ZIP_ERRNO;
                snprintf(errbuf, ERRORBUFSIZE, "error in opening %s for reading\n", filenameinzip);
                printf_err(errbuf);
            }
        }

        if (err == ZIP_OK)
        {
            /* Read contents of file and write it to zip */
            do
            {
                size_read = (int)fread(buf, 1, size_buf, fin);
                if ((size_read < size_buf) && (feof(fin) == 0))
                {
                    snprintf(errbuf, ERRORBUFSIZE, "error in reading %s\n",filenameinzip);
                    printf_err(errbuf);
                    err = ZIP_ERRNO;
                }

                if (size_read > 0)
                {
                    err = zipWriteInFileInZip(zf, buf, size_read);
                    if (err < 0) {
                        snprintf(errbuf, ERRORBUFSIZE, "error in writing %s in the zipfile (%d)\n", filenameinzip, err);
                        printf_err(errbuf);
                    }
                }
            }
            while ((err == ZIP_OK) && (size_read > 0));
        }

        if (fin)
            fclose(fin);

        if (err < 0)
            err = ZIP_ERRNO;
        else
        {
            err = zipCloseFileInZip(zf);
            if (err != ZIP_OK) {
                snprintf(errbuf, ERRORBUFSIZE, "error in closing %s in the zipfile (%d)\n", filenameinzip, err);
                printf_err(errbuf);
            }
        }
    }

    errclose = zipClose(zf, NULL);
    if (errclose != ZIP_OK) {
        snprintf(errbuf, ERRORBUFSIZE, "error in closing %s (%d)\n", zipfilename, errclose);
        printf_err(errbuf);
    }

    return err;
}
