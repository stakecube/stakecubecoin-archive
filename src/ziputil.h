// Copyright (c) 2018 The COLX developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_ZIPUTIL_H
#define BITCOIN_ZIPUTIL_H

#include <string>
#include <vector>

/**
 * Create zip archive, add input file/folder to the archive.
 * Folder recursively added to the archive. Overwrite existing archive.
 *
 * @param strOutputPath[in] path to the output zip file
 * @param strInputPath[in] path to the input file/folder
 * @param err[out] error description in case of fail
 * @return true - success, false - fail, see err for details
 */
bool ZipCreate(const std::string& strOutputPath, const std::string& strInputPath, std::string& err);

/**
 * Extract zip archive into specified folder.
 * Overwrite existing files in the output folder.
 *
 * @param strInputPath[in] path to the input zip file
 * @param strOutputPath[in] path to the output folder
 * @param err[out] error description in case of fail
 * @return true - success, false - fail, see err for details
 */
bool ZipExtract(const std::string& strInputPath, const std::string& strOutputPath, std::string& err);

#endif // BITCOIN_ZIPUTIL_H
