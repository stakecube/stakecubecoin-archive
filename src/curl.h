// Copyright (c) 2018 The COLX developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_CURL_H
#define BITCOIN_CURL_H

#include <string>
#include <functional>

typedef std::string CUrl;
#define CURL_CANCEL_DOWNLOAD 1
#define CURL_CONTINUE_DOWNLOAD 0

/**
 * Progress callback.
 * @param[in] total download/upload size total
 * @param[in] now downlod/upload size by now
 * @return 1 - stop download, 0 - continue download
 */
typedef std::function<int (double total, double now)> ProgressReport;

/**
 * Extract URL to redirect to.
 * @param[in] url input http(s) address
 * @param[out] redirect output http(s) address
 * @param[out] error brief description on fail
 * @return true - success, false - fail
 */
bool CURLGetRedirect(const CUrl& url, CUrl& redirect, std::string& error);

/**
 * Download content to the memory buffer.
 * @param[in] url input http(s) address
 * @param[in] fn progress report function
 * @param[out] buff output buffer
 * @param[out] error brief description on fail
 * @return true - success, false - fail
 */
bool CURLDownloadToMem(const CUrl& url, ProgressReport fn, std::string& buff, std::string& error);

/**
 * Download content to the file by given path.
 * @param[in] url input http(s) address
 * @param[in] path path to the file where to save content
 * @param[in] fn progress report function
 * @param[out] error brief description on fail
 * @return true - success, false - fail
 */
bool CURLDownloadToFile(const CUrl& url, const std::string& path, ProgressReport fn, std::string& error);

#endif // BITCOIN_CURL_H
