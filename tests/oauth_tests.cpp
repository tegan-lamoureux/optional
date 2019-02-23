#include "gtest/gtest.h"
#include "oauth.h"

#include <curl/curl.h>
#include <string>

namespace {

TEST(OAuthTests, curl_exists_and_can_be_used) {
    EXPECT_EQ(0, curl_global_init(CURL_GLOBAL_ALL));
}

TEST(OAuthTests, can_create_oauth_object) {
    Optional::OAuth oauth("user_id", "https://callback_uri.test");
}

TEST(OAuthTests, generate_authentication_url_composes_correct_string) {

}

} // namespace
