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
TEST(OAuthTests, /*DISABLED_*/refresh_code_is_retrieved_from_server) {
    Optional::OAuth oauth("TEUX0001", "https://localhost");

    const string provided_code = "https://localhost/?code=wjMTgrX5t1x0mr6b9GnvU2z36YhY5v6lbkmrCYPwuOWBGZPY9IZQ7K434s0EXFhILg75nahDhm77Ybfn4H%2BUuMRxoEXNnF02hoR6%2BgO%2BNd6DMIZ2dHJrgrHQjO6u7NbBa9iAQy8jzPHV4ieuAcCddhjC9iMSRLNX0N3Y88nIswdyT8Gdcb%2B30vILd4Eh0Uf%2BCgCxWDkbczWxLvoI3aNLLogIdXsAsN7TYf%2B7OU6L1SWqwOFW1rpUJiZcn2B7VWBESAf2SJB9uBZuomjc2Kieuz5o7YQB%2BPUbE7bs98TyGyuCe%2FjjMyQdHgZdskyqKOmw1Q2jbFcMA9nsg2T3hpEroW9ZYAHQGZzwMW6LU6dRhnAV84RnAc3ypZJHkMfzETA%2Bz5gXSY6gfcTMLoTa3YT9i%2FNIb1WP70AJVZr4nvsSHcKhivAN0CeTH7nmcd3100MQuG4LYrgoVi%2FJHHvltQYqeXE5JedsnBJKezV%2Ftaj7OAovFah90CL0QwvHoopeLvsTNNpQrr5xJqrg1%2BrrlGxa7Eb9nPYcgsp4rJpuhF%2Bhd8Iv%2FHLnHmgwJk%2Fappf16ydFMrGXsxGDRkDMEZ5IjQVY%2Bx6o1PXbKWL6ffi5CJThRe%2FS9%2BCbV3tWJImx5CUHuSwbhdXvpHAagU%2BsUEr3bG8YdiPu4q9sGmGoRHqmYgwHiS73od%2BMo5hhcIYIRzxjzOBQT6On0dNFk0BgJ%2F4GHXJJLoXskaDsduz870KQd5mo%2BBgkulH60UulglqAsy3CS3e%2Fplf5eflDnLMsC3afFqJ9GZd1UQ2kY1jYN3%2FbTyaAqa%2FesIeipOiRVFUV3Le5jkrMJjLonk2pJhjuXwdjpbLB%2BnnNaZ7OopMDKfolciR4RFopnWB356LNsxMzp%2FozxHQjwUtN2I5Ohgo%3D212FD3x19z9sWBHDJACbC00B75E";

    EXPECT_TRUE(oauth.accept_authentication_code(provided_code));
    EXPECT_STREQ("", oauth.generate_refresh_token().c_str());
}



} // namespace
