// Copyright (c) 2018 The COLX developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "ziputil.h"
#include "tinyformat.h"

#include <minizip.h>

#include <cassert>
#include <exception>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost;

static vector<string> GetDirectoryContent(const string& path)
{
    assert(!path.empty());

    vector<string> fileList;
    if (!filesystem::exists(path))
        return fileList;
    else if (filesystem::is_regular_file(path)) {
        fileList.push_back(path);
        return fileList;
    } else if (filesystem::is_directory(path)) {
        filesystem::recursive_directory_iterator it{path};
        while (it != filesystem::recursive_directory_iterator{}) {
            if (filesystem::is_regular_file(it->path()))
                fileList.push_back(it->path().string());

            ++it;
        }
        return fileList;
    } else {
        assert(false); // unexpected
        return fileList;
    }
}

static void AppendArg(const string& arg, string& arguments)
{
    arguments.append(arg);
    arguments.push_back('\0');
}

static vector<const char*> BuildArgv(const string& arguments)
{
    vector<const char*> argv;

    // this algo skips two empty arguments followed by each other
    for (size_t i = 0; i < arguments.size(); ++i) {
        argv.push_back(&arguments[i]);
        i = arguments.find('\0', i + 1);
    }

    return argv;
}

static string strError;
static void AppendStr(const char *s)
{
    assert(s);
    if (s) strError.append(s);
}

bool ZipCreate(const string& strOutputPath, const string& strInputPath, string& err)
{
    try {
        if (filesystem::exists(strOutputPath) && !filesystem::remove(strOutputPath)) {
            err = strprintf("Failed to create archive, file %s is write-protected", strOutputPath);
            return false;
        }

        if (!filesystem::exists(strInputPath)) {
            err = strprintf("Path %s does not exist", strInputPath);
            return false;
        }

        vector<string> fileList = GetDirectoryContent(strInputPath);
        if (fileList.empty()) {
            err = strprintf("Path %s does not contain any files", strInputPath);
            return false;
        }

        string arguments;
        AppendArg("", arguments);
        AppendArg("-o", arguments);
        AppendArg("-5", arguments);
        AppendArg(strOutputPath, arguments);
        for (const string& f : fileList)
            AppendArg(f, arguments);

        vector<const char*> argv = BuildArgv(arguments);

        strError.clear();
        if (0 == main_zip(argv.size(), &argv[0], AppendStr))
            return true;
        else {
            err = strError;
            return false;
        }
    } catch (const std::exception& e) {
        err = e.what();
        return false;
    }
}

bool ZipExtract(const string& strInputPath, const string& strOutputPath, string& err)
{
    try {
        if (!filesystem::exists(strInputPath)) {
            err = strprintf("Path %s does not exist", strInputPath);
            return false;
        }

        if (!filesystem::exists(strOutputPath)) {
            err = strprintf("Path %s does not exist", strOutputPath);
            return false;
        }

        if (!filesystem::is_directory(strOutputPath)) {
            err = strprintf("Path %s is not a directory", strOutputPath);
            return false;
        }

        string arguments;
        AppendArg("", arguments);
        AppendArg("-x", arguments);
        AppendArg("-o", arguments);
        AppendArg(strInputPath, arguments);
        AppendArg("-d", arguments);
        AppendArg(strOutputPath, arguments);

        vector<const char*> argv = BuildArgv(arguments);

        strError.clear();
        filesystem::path cwd = filesystem::current_path();
        int res = main_unzip(argv.size(), &argv[0], AppendStr);
        filesystem::current_path(cwd);

        if (0 == res)
            return true;
        else {
            err = strError;
            return false;
        }
    } catch (const std::exception& e) {
        err = e.what();
        return false;
    }
}
