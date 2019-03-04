#include "rest.h"

#include <curl/curl.h>

Optional::Rest::Rest()
{
    curl_global_init(CURL_GLOBAL_ALL);
}

Optional::Rest::~Rest() {
    curl_global_cleanup();
}

std::string Optional::Rest::post(std::string post_url, std::string header, std::string post_data, bool& valid_data_out) {
    valid_data_out = false;

    std::string post_returned_data;
    std::scoped_lock(this->curl_lock);
    CURL *curl = curl_easy_init();
    CURLcode post_result;

    if(curl) {
        struct curl_slist *headers = nullptr;

        headers = curl_slist_append(headers, header.c_str());

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_URL, post_url.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, this->curl_post_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &post_returned_data);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L); // Set to 1L for debug output.
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data.c_str());

        post_result = curl_easy_perform(curl);

        if(post_result == CURLE_OK) {
            valid_data_out = true;
        }

        curl_easy_cleanup(curl);
    }

    return post_returned_data;
}

size_t Optional::Rest::curl_post_callback(void* contents, size_t size, size_t nmemb, void* return_data) {
    int bytes_handled = size * nmemb;
    static_cast<std::string*>(return_data)->append(static_cast<const char*>(contents), bytes_handled);
    return bytes_handled;
}
