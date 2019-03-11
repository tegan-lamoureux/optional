#ifndef OPTIONAL_OAUTH_H
#define OPTIONAL_OAUTH_H

#include <string>
#include <ctime>
#include <memory>

#include "rapidjson/document.h"
#include "rest.h"

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
    OAuth(std::string oauth_uid_in, std::string redirect_uri_in, std::shared_ptr<Rest> rest_interface_in);
    OAuth(const OAuth& other);
    OAuth& operator=(const OAuth& other);

    std::string generate_authentication_url();
    bool accept_authentication_code(std::string code);
    
    OAuthStatus generate_tokens();

    std::string get_authentication_code();
    std::string get_access_token();
    OAuthStatus get_status();

    std::string debug();

    /**
     * @brief Checks if refresh token exists as local veriable, and if not, as file.
     * @return
     */
    bool load_refresh_token_from_disk();
    void save_refresh_token_to_disk();
    // TODO: See if some of these should be private

    bool refresh_token_valid();
    bool access_token_valid();

private:
    OAuth() = delete;

    const std::string access_token_post_url = "https://api.tdameritrade.com/v1/oauth2/token";
    const std::string refresh_token_file = "tok.dat";

    OAuthStatus authorization_status;

    std::string oauth_uid;
    std::string redirect_uri;
    std::string authentication_code;
    std::string refresh_token;
    std::string access_token;

    // FIXME: incorprate these into code
    std::time_t refresh_expiration;
    std::time_t access_expiration;

    // This should be completley internal and not passed in. FIXME
    std::shared_ptr<Rest> rest_interface;


    bool parsed_auth_json_is_valid(rapidjson::Document& auth_result);
};

}

#endif // OAUTH_H
