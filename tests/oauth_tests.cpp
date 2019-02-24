#include "gtest/gtest.h"
#include "oauth.h"

#include <curl/curl.h>
#include <string>

using namespace std;

namespace {

TEST(OAuthTests, curl_exists_and_can_be_used) {
    EXPECT_EQ(0, curl_global_init(CURL_GLOBAL_ALL));
}

TEST(OAuthTests, can_create_oauth_object) {
    Optional::OAuth oauth("user_id", "https://callback_uri.test");
}

TEST(OAuthTests, generate_authentication_url_composes_correct_string) {
    Optional::OAuth oauth("user_id", "https://callback_uri.test");
    const string expected_url = "https://auth.tdameritrade.com/auth?response_type=code&redirect_uri=https://callback_uri.test&client_id=user_id@AMER.OAUTHAP";
    
    EXPECT_STREQ(expected_url, oauth.generate_authentication_url());
}
    
TEST(OAuthTests, oauth_handles_bad_uid_and_url) {
    Optional::OAuth oauth("", "");
    const string expected_url = "https://auth.tdameritrade.com/auth?response_type=code&redirect_uri=https://null_value&client_id=null_value@AMER.OAUTHAP";

    EXPECT_STREQ(expected_url, oauth.generate_authentication_url());
}
    
TEST(OAuthTests, accept_authentication_code_accepts_good_code) {
    Optional::OAuth oauth("user_id", "https://callback_uri.test");
    
    const string provided_code = "http://callback_uri.test/?code=<THIS_IS_THE_RETURNED_AUTH_CODE>";
    const string expected_code = "<THIS_IS_THE_RETURNED_AUTH_CODE>";
    
    EXPECT_TRUE(oauth.accept_authentication_code(provided_code));
    EXPECT_STREQ(expected_code, oauth.get_authentication_code());
}

} // namespace
