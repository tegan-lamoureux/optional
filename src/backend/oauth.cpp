#include "oauth.h"
#include <curl/curl.h>
#include <cstring>

// FIXME: Change these namespaces to split the frontend and backend? Maybe. Check.

Optional::OAuth::OAuth(std::string oauth_uid_in, std::string redirect_uri_in)
    : authorization_status(Unauthenticated)
    , oauth_uid(oauth_uid_in)
    , redirect_uri(redirect_uri_in)
    , authentication_code("")
    , refresh_token("")
    , access_token("")
{
    curl_global_init(CURL_GLOBAL_ALL);
    
    if (this->redirect_uri.empty()) {
        this->redirect_uri = "https://null_value";
    }
    if (this->oauth_uid.empty()) {
        this->oauth_uid = "null_value";
    }
}

Optional::OAuth::~OAuth() {
    curl_global_cleanup();

}

std::string Optional::OAuth::generate_authentication_url() {
    return std::string("https://auth.tdameritrade.com/auth?response_type=code&redirect_uri=")
            + this->redirect_uri
            + std::string("&client_id=")
            + this->oauth_uid
            + std::string("@AMER.OAUTHAP");
}

bool Optional::OAuth::accept_authentication_code(std::string code) {
    bool valid = false;
    const std::string search_term = "?code=";

    if (code.empty() == false) {
        auto location = code.find(search_term);

        if (location != std::string::npos && (location + search_term.length()) < code.length()) {
            this->authentication_code = code.substr(location + search_term.length());
            valid = true;
        }
    }

    return valid;
}

std::string Optional::OAuth::get_authentication_code() {
    return this->authentication_code;
}

Optional::OAuthStatus Optional::OAuth::generate_tokens() {
    CURL *curl = curl_easy_init();
    CURLcode post_result;
	
    if(curl && this->authorization_status != Valid) {
        std::string post_returned_data;
        std::string post_data =
                std::string("grant_type=authorization_code")
                + std::string("&refresh_token=")
                + std::string("&access_type=offline")
                + std::string("&code=")
                + this->authentication_code
                + std::string("&client_id=")
                + this->oauth_uid
                + std::string("&redirect_uri=")
                + this->redirect_uri;

        curl_easy_setopt(curl, CURLOPT_URL, this->access_token_post_url.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_post_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &post_returned_data);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L); // Set to 1L for debug output.
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data.c_str());
 
        post_result = curl_easy_perform(curl);

        if(post_result != CURLE_OK) {
            this->authorization_status = Invalid;
        }
        else {
            rapidjson::Document auth_result;
            auth_result.Parse(post_returned_data.c_str(),post_returned_data.length());

            if(parsed_auth_result_is_valid(auth_result)) {
                this->refresh_expiration = std::time(nullptr) + auth_result["refresh_token_expires_in"].GetInt();
                this->access_expiration = std::time(nullptr) + auth_result["expires_in"].GetInt();
                this->refresh_token = auth_result["refresh_token"].GetString();
                this->access_token = auth_result["access_token"].GetString();

                this->authorization_status = Valid;
            }
            else {
                this->authorization_status = Invalid;
            }
        }

        curl_easy_cleanup(curl);
    }

    return this->authorization_status;
}

size_t Optional::OAuth::curl_post_callback(void* contents, size_t size, size_t nmemb, void* return_data) {
    int bytes_handled = size * nmemb;
    static_cast<std::string*>(return_data)->append(static_cast<const char*>(contents), bytes_handled);
    return bytes_handled;
}

bool Optional::OAuth::parsed_auth_result_is_valid(rapidjson::Document& auth_result) {
    return auth_result.HasMember("access_token")
            && auth_result.HasMember("refresh_token")
            && auth_result.HasMember("refresh_token_expires_in")
            && auth_result.HasMember("expires_in");
}
