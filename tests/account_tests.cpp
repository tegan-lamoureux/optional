#include "gtest/gtest.h"
#include "account.h"
#include "rest.h"
#include "oauth.h"

#include "rapidjson/document.h"

#include <curl/curl.h>
#include <string>
#include <iostream>

using namespace std;

namespace {

class AccountTests : public testing::Test {
protected:
    virtual void SetUp() {

    }

    virtual void TearDown() {

    }

    Optional::Rest rest;
};


// There's no way to test this without legitimate credentials, so it's an interactive
// test, and may be disabled by prepending DISABLED_ to the test name.
TEST_F(AccountTests, /*DISABLED_*/can_get_account_data) {
    string uid;
    string callback_uri;
    string result;
    string account_number;

    cout << "Enter OAuth UID: ";
    cin >> uid;
    cout << "Enter callback URI: ";
    cin >> callback_uri;
    cout << "Enter account #: ";
    cin >> account_number;


    Optional::OAuth oauth(uid, callback_uri, this->rest);

    cout << "Go to this url, authenticate, and paste resuling address below: " << oauth.generate_authentication_url() << endl;
    cout << ": ";
    cin >> result;

    ASSERT_TRUE(oauth.accept_authentication_code(result));
    ASSERT_EQ(Optional::OAuthStatus::Valid, oauth.generate_tokens());

    Optional::Account account(oauth, this->rest, account_number);

    ASSERT_TRUE(account.refresh_account());
}

}
