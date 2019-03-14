#include "rest.h"

#include <curl/curl.h>

Optional::Rest::Rest()
{
    curl_global_init(CURL_GLOBAL_ALL);
}

Optional::Rest::~Rest() {
    curl_global_cleanup();
}

std::string Optional::Rest::post(std::string url, std::string header, std::string data, bool& valid_data_out, bool verbose) {
    std::scoped_lock(this->curl_lock);

    valid_data_out = false;

    std::string post_returned_data;
    CURL *curl = curl_easy_init();
    CURLcode post_result;

    if(curl) {
        struct curl_slist *headers = nullptr;

        headers = curl_slist_append(headers, header.c_str());

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, this->curl_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &post_returned_data);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());

        if (verbose) {
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        }
        else {
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
        }

        post_result = curl_easy_perform(curl);

        if(post_result == CURLE_OK) {
            valid_data_out = true;
        }

        curl_easy_cleanup(curl);
    }

    return post_returned_data;
}

std::string Optional::Rest::get(std::string url, std::string header, bool& valid_data_out, bool verbose) {
    std::scoped_lock(this->curl_lock);

    valid_data_out = false;

    std::string get_returned_data;
    CURL *curl = curl_easy_init();
    CURLcode get_result;

    if(curl) {
        struct curl_slist *headers = nullptr;

        headers = curl_slist_append(headers, header.c_str());

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, this->curl_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &get_returned_data);

        if (verbose) {
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        }
        else {
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
        }

        get_result = curl_easy_perform(curl);

        if(get_result == CURLE_OK) {
            valid_data_out = true;
        }

        curl_easy_cleanup(curl);
    }

    return get_returned_data;
}

std::string Optional::Rest::url_encoding(std::string input) {
    CURL *curl = curl_easy_init();
    std::string encoded_string = "";

    if(curl) {
      char* encoded_buffer = curl_easy_escape(curl, input.c_str(), input.length());

      if(encoded_buffer) {
        encoded_string = std::string(encoded_buffer);
        curl_free(encoded_buffer);
      }

      curl_easy_cleanup(curl);
    }

    return encoded_string;
}


size_t Optional::Rest::curl_callback(void* contents, size_t size, size_t nmemb, void* return_data) {
    int bytes_handled = size * nmemb;
    static_cast<std::string*>(return_data)->append(static_cast<const char*>(contents), bytes_handled);
    return bytes_handled;
}
