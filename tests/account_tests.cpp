#include "gtest/gtest.h"
#include "account.h"
#include "rest.h"
#include "oauth.h"

#include "rapidjson/document.h"

#include <curl/curl.h>
#include <string>
#include <iostream>
#include <memory>

using namespace std;

namespace {

shared_ptr<Optional::Account> account;

class AccountTests : public testing::Test {
protected:
    AccountTests() {

    }

    virtual void SetUp() {

    }

    virtual void TearDown() {

    }
};


// There's no way to test this without legitimate credentials, so it's an interactive
// test, and may be disabled by prepending DISABLED_ to the test name.
TEST_F(AccountTests, can_create_account_and_get_details) {
    string uid;
    string account_number;

    cout << "Enter OAuth UID: ";
    cin >> uid;
    cout << "Enter account #: ";
    cin >> account_number;

    account = shared_ptr<Optional::Account>(new Optional::Account(account_number, uid));

    // Check if can get account and refresh value.
    ASSERT_EQ(Optional::OAuthStatus::Valid, account->get_authorization_status());
    ASSERT_TRUE(account->refresh_account());
}

// NOTE: This test requires legitimate credentials to pass.
TEST_F(AccountTests, can_get_account_id) {
    char* expected_account_number = "<asd>";

    ASSERT_EQ(Optional::OAuthStatus::Valid, account->get_authorization_status());
    ASSERT_STREQ(expected_account_number, account->account_id().c_str());
}

// NOTE: This test requires legitimate credentials to pass.
TEST_F(AccountTests, can_get_account_type) {
    char* expected_account_type = "<asd>";

    ASSERT_EQ(Optional::OAuthStatus::Valid, account->get_authorization_status());
    ASSERT_STREQ(expected_account_type, account->account_type().c_str());
}

// FIXME: Add rest of account tests here.



}






















