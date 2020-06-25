// Copyright (c) 2018 The COLX developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef MINIZIP_H
#define MINIZIP_H

#ifndef ZEXPORT
#define ZEXPORT
#endif

#ifdef __cplusplus
extern "C" {
#endif

// error message callback
typedef void (*error_callback)(const char *);

// Usage : miniunz [-e] [-x] [-v] [-l] [-o] [-p password] file.zip [file_to_extr.] [-d extractdir]
// -e  Extract without pathname (junk paths)
// -x  Extract with pathname
// -v  list files
// -l  list files
// -d  directory to extract into
// -o  overwrite existing files
// -s  skip existing files
// -p  extract crypted file using password
extern int ZEXPORT main_unzip(int argc, const char *argv[], error_callback fptr);

// Usage : minizip [-o] [-a] [-0 to -9] [-p password] [-j] file.zip [files_to_add]
// -o  Overwrite existing file.zip
// -a  Append to existing file.zip
// -0  Store only
// -1  Compress faster
// -9  Compress better
// -j  Exclude path, store only the file name
extern int ZEXPORT main_zip(int argc, const char *argv[], error_callback fptr);

#ifdef __cplusplus
}
#endif

#endif // MINIZIP_H
