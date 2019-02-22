#ifndef OPTIONAL_OAUTH_H
#define OPTIONAL_OAUTH_H

#include <string>

namespace Optional {

/**
 * @brief Internal status
 */
enum OAuthStatus {
    Unauthenticated, ///< Initial authentication state.
    Invalid,         ///< Invalid uid, uri, or access code.
    Valid,           ///< Valid code and refresh token. Ready to generate API access tokens.
    NeedsRefresh,    ///< Needs refresh token, either initial or updated (lapses at 90 days).
};


/**
 * @brief Handles OAuth credentials for logging into app and accessing trading account.
 */
class OAuth
{
public:
    OAuth(std::string oauth_uid_in, std::string redirect_uri_in);

    std::string generate_authentication_url();
    bool accept_authentication_code(std::string code);
    std::string generate_refresh_token();
    std::string generate_access_token();

    OAuthStatus get_status();

    std::string debug();

private:
    OAuth() = delete;

    const std::string access_token_post_url = "https://api.tdameritrade.com/v1/oauth2/token";

    OAuthStatus authorization_status;

    std::string oauth_uid;
    std::string redirect_uri;
    std::string authentication_code;
    std::string refresh_token;
    std::string access_token;
};

}

#endif // OAUTH_H
