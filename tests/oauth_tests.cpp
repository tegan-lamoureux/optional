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
    
    EXPECT_STREQ(expected_url.c_str(), oauth.generate_authentication_url().c_str());
}
    
TEST(OAuthTests, oauth_handles_bad_uid_and_url) {
    Optional::OAuth oauth("", "");
    const string expected_url = "https://auth.tdameritrade.com/auth?response_type=code&redirect_uri=https://null_value&client_id=null_value@AMER.OAUTHAP";

    EXPECT_STREQ(expected_url.c_str(), oauth.generate_authentication_url().c_str());
}
    
TEST(OAuthTests, accept_authentication_code_accepts_good_code) {
    Optional::OAuth oauth("user_id", "https://callback_uri.test");

    const string provided_code = "http://callback_uri.test/?code=<THIS_IS_THE_RETURNED_AUTH_CODE>";
    const string expected_code = "<THIS_IS_THE_RETURNED_AUTH_CODE>";

    EXPECT_TRUE(oauth.accept_authentication_code(provided_code));
    EXPECT_STREQ(expected_code.c_str(), oauth.get_authentication_code().c_str());
}

TEST(OAuthTests, accept_authentication_code_handles_bad_code) {
    Optional::OAuth oauth("user_id", "https://callback_uri.test");

    const string BAD_provided_code = "ht:/callbacri.23@#$@^<THIS_IS_THE_RETURNED_AUTH_CODE>";
    const string expected_code = "";

    EXPECT_FALSE(oauth.accept_authentication_code(BAD_provided_code));
    EXPECT_STREQ(expected_code.c_str(), oauth.get_authentication_code().c_str());
}

// There's no way to test this without legitimate credentials, so it's left as
// a shell test for an end user to check.
TEST(OAuthTests, DISABLED_refresh_code_is_retrieved_from_server) {
    Optional::OAuth oauth("user_id", "https://callback_uri.test");

    const string provided_code = "https://localhost/?code=some_code";

//    EXPECT_TRUE(oauth.accept_authentication_code(provided_code));
//    EXPECT_STREQ("", oauth.generate_tokens().c_str());
}



} // namespace
