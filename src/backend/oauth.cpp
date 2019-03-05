#include "oauth.h"
#include <cstring>

// FIXME: Change these namespaces to split the frontend and backend? Maybe. Check.

Optional::OAuth::OAuth(std::string oauth_uid_in, std::string redirect_uri_in, Rest& rest_interface_in)
    : authorization_status(OAuthStatus::Unauthenticated)
    , oauth_uid(oauth_uid_in)
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
    // Check time better?
//    if (this->authorization_status == OAuthStatus::Valid) {
        return this->access_token;
//    }
//    else {
//        return "";
//    }
}

Optional::OAuthStatus Optional::OAuth::generate_tokens() {
    bool valid_data;

    if(this->authorization_status != OAuthStatus::Valid) {
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

        std::string post_header = "";

        std::string post_return_data = this->rest_interface.post(access_token_post_url, post_header, post_data, valid_data);

        if(valid_data) {
            rapidjson::Document auth_result;
            auth_result.Parse(post_return_data.c_str(),post_return_data.length());

            if(parsed_auth_result_is_valid(auth_result)) {
                this->refresh_expiration = std::time(nullptr) + auth_result["refresh_token_expires_in"].GetInt();
                this->access_expiration = std::time(nullptr) + auth_result["expires_in"].GetInt();
                this->refresh_token = auth_result["refresh_token"].GetString();
                this->access_token = auth_result["access_token"].GetString();

                this->authorization_status = OAuthStatus::Valid;
            }
            else {
                this->authorization_status = OAuthStatus::Invalid;
            }
        }
        else {
            this->authorization_status = OAuthStatus::Invalid;
        }

    }

    return this->authorization_status;
}

Optional::OAuthStatus Optional::OAuth::get_status() {
    if (this->refresh_expiration < std::time(nullptr) || this->access_expiration < std::time(nullptr)) {
        this->authorization_status = OAuthStatus::NeedsRefresh;
    }

    return this->authorization_status;
}



bool Optional::OAuth::parsed_auth_result_is_valid(rapidjson::Document& auth_result) {
    return auth_result.HasMember("access_token")
            && auth_result.HasMember("refresh_token")
            && auth_result.HasMember("refresh_token_expires_in")
            && auth_result.HasMember("expires_in");
}
