#pragma once

#define CURL_STATICLIB
#include <curl/curl.h>
#include <iostream>
#include <vector>
#include <string>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

size_t discard_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
    return size * nmemb;
}

static bool curl_post(const std::string &url, const std::vector<std::string> &headers, const std::string &post_data, std::string &response)
{
    CURL *curl;
    CURLcode res;
    struct curl_slist *header_list = nullptr;

    curl = curl_easy_init();

    if (!curl) {
        curl_global_cleanup();
        return false;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data.c_str());

    for (const auto &header : headers) {
        header_list = curl_slist_append(header_list, header.c_str());
    }
    if (header_list) {
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);
    }

    res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return false;
    }

    curl_easy_cleanup(curl);
    if (header_list) {
        curl_slist_free_all(header_list);
    }

    return true;
}

static bool curl_delete(const std::string &url, const std::vector<std::string> &headers) {
    CURL *curl = curl_easy_init();
    if (!curl) {
        return false;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    struct curl_slist *headerlist = nullptr;
    for (const auto &header : headers) {
        headerlist = curl_slist_append(headerlist, header.c_str());
    }
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);

    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, discard_callback);

    CURLcode res = curl_easy_perform(curl);

    long http_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

    curl_slist_free_all(headerlist);
    curl_easy_cleanup(curl);

    if (res == CURLE_OK) {
        if (http_code == 204) {
            return true;
        }
    }

    return false;
}