#include "oauth.h"

Optional::OAuth::OAuth(std::string oauth_uid_in, std::string redirect_uri_in)
    : authorization_status(Unauthenticated)
    , oauth_uid(oauth_uid_in)
    , redirect_uri(redirect_uri_in)
    , authentication_code("")
    , refresh_token("")
    , access_token("")
{
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

        if (location < code.length()) {
            authentication_code = code.substr(location + search_term.length());
            valid = true;
        }
    }

    return valid;
}

std::string Optional::OAuth::generate_refresh_token() {
    // left off here. post to this->access_token_post_url with the given
    // authentication code and user info. same for access token.
}

std::string Optional::OAuth::generate_access_token() {

}

std::string Optional::OAuth::debug()
{
    return this->authentication_code;
}
