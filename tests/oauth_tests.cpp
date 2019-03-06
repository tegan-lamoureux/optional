#include "gtest/gtest.h"
#include "rapidjson/document.h"

#include "oauth.h"
#include "rest.h"

#include <curl/curl.h>
#include <string>
#include <iostream>

using namespace std;

namespace {

class OAuthTests : public testing::Test {
protected:
    virtual void SetUp() {

    }

    virtual void TearDown() {

    }

    Optional::Rest rest;
};


TEST_F(OAuthTests, rapidjson_exists_and_can_be_used) {
    string test_json = "{\"field1\": \"field one's data\", \"field2\": \"field two's data\"}";

    rapidjson::Document test_document;
    test_document.Parse(test_json.c_str(), test_json.length());

    ASSERT_TRUE(test_document.HasMember("field1"));
    ASSERT_TRUE(test_document.HasMember("field2"));
    EXPECT_STREQ("field one's data", test_document["field1"].GetString());
    EXPECT_STREQ("field two's data", test_document["field2"].GetString());
}

TEST_F(OAuthTests, can_create_oauth_object) {
    Optional::OAuth oauth("user_id", "https://callback_uri.test", this->rest);
}

TEST_F(OAuthTests, generate_authentication_url_composes_correct_string) {
    Optional::OAuth oauth("user_id", "https://callback_uri.test", this->rest);
    const string expected_url = "https://auth.tdameritrade.com/auth?response_type=code&redirect_uri=https://callback_uri.test&client_id=user_id@AMER.OAUTHAP";
    
    EXPECT_STREQ(expected_url.c_str(), oauth.generate_authentication_url().c_str());
}
    
TEST_F(OAuthTests, oauth_handles_bad_uid_and_url) {
    Optional::OAuth oauth("", "", this->rest);
    const string expected_url = "https://auth.tdameritrade.com/auth?response_type=code&redirect_uri=https://null_value&client_id=null_value@AMER.OAUTHAP";

    EXPECT_STREQ(expected_url.c_str(), oauth.generate_authentication_url().c_str());
}
    
TEST_F(OAuthTests, accept_authentication_code_accepts_good_code) {
    Optional::OAuth oauth("user_id", "https://callback_uri.test", this->rest);

    const string provided_code = "http://callback_uri.test/?code=<THIS_IS_THE_RETURNED_AUTH_CODE>";
    const string expected_code = "<THIS_IS_THE_RETURNED_AUTH_CODE>";

    EXPECT_TRUE(oauth.accept_authentication_code(provided_code));
    EXPECT_STREQ(expected_code.c_str(), oauth.get_authentication_code().c_str());
}

TEST_F(OAuthTests, accept_authentication_code_handles_bad_code) {
    Optional::OAuth oauth("user_id", "https://callback_uri.test", this->rest);

    const string BAD_provided_code = "ht:/callbacri.23@#$@^<THIS_IS_THE_RETURNED_AUTH_CODE>";
    const string expected_code = "";

    EXPECT_FALSE(oauth.accept_authentication_code(BAD_provided_code));
    EXPECT_STREQ(expected_code.c_str(), oauth.get_authentication_code().c_str());
}

// There's no way to test this without legitimate credentials, so it's an interactive
// test, and may be disabled by prepending DISABLED_ to the test name.
TEST_F(OAuthTests, DISABLED_refresh_code_is_retrieved_from_server) {
    string uid;
    string callback_uri;
    string result;

    cout << "Enter OAuth UID: ";
    cin >> uid;
    cout << "Enter callback URI: ";
    cin >> callback_uri;

    Optional::OAuth oauth(uid, callback_uri, this->rest);

    cout << "Go to this url, authenticate, and paste resuling address below: " << oauth.generate_authentication_url() << endl;
    cout << ": ";
    cin >> result;

    EXPECT_TRUE(oauth.accept_authentication_code(result));
    EXPECT_EQ(Optional::OAuthStatus::Valid, oauth.generate_tokens());
}

TEST_F(OAuthTests, refresh_token_somethingdadsf) { // FIXME
    Optional::OAuth oauth("user_id", "https://callback_uri.test", this->rest);
    oauth.refresh_exists();
}


} // namespace
