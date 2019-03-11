#include "oauth.h"

#include <fstream>
#include <algorithm>

// FIXME: Change these namespaces to split the frontend and backend? Maybe. Check.

Optional::OAuth::OAuth(std::string oauth_uid_in, std::string redirect_uri_in, std::shared_ptr<Rest> rest_interface_in)
    : oauth_uid(oauth_uid_in)
    , redirect_uri(redirect_uri_in)
    , authentication_code("")
    , refresh_token("")
    , access_token("")
    , rest_interface(rest_interface_in)
{
    if (this->redirect_uri.empty()) {
        this->redirect_uri = "https://null_value";
    }
    if (this->oauth_uid.empty()) {
        this->oauth_uid = "null_value";
    }

    // Try to load refresh token from disk and generate access token.
    if (this->load_refresh_token_from_disk() && this->refresh_token_valid()) {
        this->authorization_status = this->generate_tokens();
    }
}

Optional::OAuth::OAuth(const Optional::OAuth &other)
    : authorization_status(other.authorization_status)
    , oauth_uid(other.oauth_uid)
    , redirect_uri(other.redirect_uri)
    , authentication_code(other.authentication_code)
    , refresh_token(other.refresh_token)
    , access_token(other.access_token)
    , refresh_expiration(other.refresh_expiration)
    , access_expiration(other.access_expiration)
    , rest_interface(other.rest_interface)
{
}

Optional::OAuth &Optional::OAuth::operator=(const Optional::OAuth &other) {
    this->authorization_status = other.authorization_status;
    this->oauth_uid = other.oauth_uid;
    this->redirect_uri = other.redirect_uri;
    this->authentication_code = other.authentication_code;
    this->refresh_token = other.refresh_token;
    this->access_token = other.access_token;
    this->refresh_expiration = other.refresh_expiration;
    this->access_expiration = other.access_expiration;

    return *this;
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

std::string Optional::OAuth::get_access_token() {
    return this->access_token;
}

Optional::OAuthStatus Optional::OAuth::generate_tokens() {
    // Skip if valid.
    if(this->get_status() == OAuthStatus::Valid) {
        return OAuthStatus::Valid;
    }

    // Build up post data string depending on whether we need just a new access
    // token based on the existing refresh token or we need both a refresh and
    // access token.
    std::string post_data;
    if (this->refresh_token_valid()) {
        post_data =
                std::string("grant_type=refresh_token")
                + std::string("&refresh_token=")
                + this->refresh_token
                + std::string("&access_type=")
                + std::string("&code=")
                + std::string("&client_id=")
                + this->oauth_uid
                + std::string("&redirect_uri=");
    }
    else {
        post_data =
                std::string("grant_type=authorization_code")
                + std::string("&refresh_token=")
                + std::string("&access_type=offline")
                + std::string("&code=")
                + this->authentication_code
                + std::string("&client_id=")
                + this->oauth_uid
                + std::string("&redirect_uri=")
                + this->redirect_uri;
    }

    // Perform the REST query.
    bool valid_data_from_post;
    std::string post_return_data = this->rest_interface->post(access_token_post_url, std::string(""), post_data, valid_data_from_post);

    // Parse out and handle tokens if post was successfull.
    if(valid_data_from_post) {
        rapidjson::Document auth_result;
        auth_result.Parse(post_return_data.c_str(),post_return_data.length());

        if(parsed_auth_json_is_valid(auth_result)) {
            // If we needed a new refresh token as well, get those values too.
            if (this->refresh_token_valid() == false) {
                this->refresh_token = auth_result["refresh_token"].GetString();
                this->refresh_expiration = std::time(nullptr) + auth_result["refresh_token_expires_in"].GetInt();

                // Check to see if we have a valid refresh now (we always should)
                // and then save it to file if it wasn't valid.
                if (this->refresh_token_valid()) {
                    this->save_refresh_token_to_disk();
                }
            }

            // But always get the new access token.
            this->access_token = auth_result["access_token"].GetString();
            this->access_expiration = std::time(nullptr) + auth_result["expires_in"].GetInt();

            this->authorization_status = OAuthStatus::Valid;

        }
        else { // POST came back incorrect.
            this->authorization_status = OAuthStatus::Invalid;
        }
    }
    else { // POST had an error.
        this->authorization_status = OAuthStatus::Invalid;
    }

    return this->authorization_status;
}

Optional::OAuthStatus Optional::OAuth::get_status() {
    if (this->refresh_token.empty() || this->access_token.empty()) {
        this->authorization_status = OAuthStatus::Unauthenticated;
    }
    else if (this->refresh_token_valid() == false || this->access_token_valid() == false) {
        this->authorization_status = OAuthStatus::NeedsRefresh;
    }
    else {
        this->authorization_status = OAuthStatus::Valid;
    }

    return this->authorization_status;
}

bool Optional::OAuth::load_refresh_token_from_disk() {
    bool loaded = false;

    std::ifstream refresh_file(this->refresh_token_file);
    if (refresh_file.is_open()) {
        std::getline(refresh_file, this->refresh_token);

        std::string raw_refresh_expiration = "";
        std::getline(refresh_file, raw_refresh_expiration);
        this->refresh_expiration = static_cast<time_t>(atol(raw_refresh_expiration.c_str()));

        if (this->refresh_token.empty() == false
                && this->refresh_expiration > 0
                && this->refresh_expiration > std::time(nullptr))
        {
            // Mark as loaded and strip newlines.
            loaded = true;
            this->refresh_token.erase(std::remove(this->refresh_token.begin(), this->refresh_token.end(), '\n'), this->refresh_token.end());
        }

        refresh_file.close();
    }

    return loaded;
}

void Optional::OAuth::save_refresh_token_to_disk() {
    std::ofstream refresh_file(this->refresh_token_file);
    if (refresh_file.is_open()) {
        refresh_file << this->refresh_token << std::endl;
        refresh_file << this->refresh_expiration << std::endl;
        refresh_file.close();
    }
}

bool Optional::OAuth::refresh_token_valid() {
    bool valid = false;

    // Check if non-null and within expiration.
    if (this->refresh_token.empty() == false &&
            this->refresh_expiration > std::time(nullptr))
    {
        valid = true;
    }

    return valid;
}

bool Optional::OAuth::access_token_valid() {
    bool valid = false;

    // Check if refresh is valid, and also if non-empty and within expiration.
    if (this->refresh_token_valid()
            && this->access_token.empty() == false
            && this->access_expiration > std::time(nullptr))
    {
        valid = true;
    }

    return valid;
}

bool Optional::OAuth::parsed_auth_json_is_valid(rapidjson::Document& auth_result) {
    bool valid_refresh_grant_json =
            auth_result.HasMember("access_token")
            && auth_result.HasMember("expires_in")
            && auth_result.HasMember("token_type")
            && auth_result.HasMember("refresh_token") == false;

    bool valid_token_grant_json =
            auth_result.HasMember("access_token")
            && auth_result.HasMember("refresh_token")
            && auth_result.HasMember("token_type")
            && auth_result.HasMember("refresh_token_expires_in")
            && auth_result.HasMember("expires_in");

    return valid_refresh_grant_json || valid_token_grant_json;
}
