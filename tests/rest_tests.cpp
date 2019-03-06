#include "gtest/gtest.h"
#include "rest.h"

#include "rapidjson/document.h"

#include <curl/curl.h>
#include <string>
#include <iostream>

using namespace std;

namespace {

TEST(RestTests, curl_exists_and_can_be_used) {
    EXPECT_EQ(0, curl_global_init(CURL_GLOBAL_ALL));
}

TEST(RestTests, can_create_rest_object) {
    Optional::Rest rest();
}

}
