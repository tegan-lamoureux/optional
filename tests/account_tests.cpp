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

    const double allowable_error = 0.01;
};


// There's no way to test this without legitimate credentials, so it's an interactive
// test, and may be disabled by prepending DISABLED_ to the test name.
TEST_F(AccountTests, DISABLED_can_create_account_and_get_details) {
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
TEST_F(AccountTests, DISABLED_can_get_account_details) {

    ASSERT_EQ(Optional::OAuthStatus::Valid, account->get_authorization_status());
    ASSERT_TRUE(account->refresh_account());

    //***************************************************************************************
    //** You'll need to comment/uncomment desired tests and fill in expected values to check.

    // Basic account info.
    EXPECT_STREQ("expected value", account->account_id().c_str());
    EXPECT_STREQ("expected value", account->account_type().c_str());

    // Day trading metrics.
    EXPECT_EQ(0, account->round_trips());
    EXPECT_EQ(false, account->is_day_trader());
    EXPECT_EQ(false, account->is_closing_only_restricted());

    // Current Balances.
    EXPECT_NEAR(0.0, account->current_accrued_interest(), this->allowable_error);
    EXPECT_NEAR(0.0, account->current_available_funds_non_marginable_trade(), this->allowable_error);
    EXPECT_NEAR(0.0, account->current_bond_value(), this->allowable_error);
    EXPECT_NEAR(0.0, account->current_buying_power(), this->allowable_error);
    EXPECT_NEAR(0.0, account->current_cash_balance(), this->allowable_error);
    EXPECT_NEAR(0.0, account->current_cash_available_for_trading(), this->allowable_error);
    EXPECT_NEAR(0.0, account->current_cash_reciepts(), this->allowable_error);
    EXPECT_NEAR(0.0, account->current_day_trading_buying_power(), this->allowable_error);
    EXPECT_NEAR(0.0, account->current_day_trading_buying_power_call(), this->allowable_error);
    EXPECT_NEAR(0.0, account->current_day_trading_equity_call(), this->allowable_error);
    EXPECT_NEAR(0.0, account->current_equity(), this->allowable_error);
    EXPECT_NEAR(0.0, account->current_equity_percentage(), this->allowable_error);
    EXPECT_NEAR(0.0, account->current_liquidation_value(), this->allowable_error);
    EXPECT_NEAR(0.0, account->current_long_margin_value(), this->allowable_error);
    EXPECT_NEAR(0.0, account->current_long_option_market_value(), this->allowable_error);
    EXPECT_NEAR(0.0, account->current_long_stock_value(), this->allowable_error);
    EXPECT_NEAR(0.0, account->current_maintenance_call(), this->allowable_error);
    EXPECT_NEAR(0.0, account->current_maintenance_requirement(), this->allowable_error);
    EXPECT_NEAR(0.0, account->current_margin(), this->allowable_error);
    EXPECT_NEAR(0.0, account->current_margin_equity(), this->allowable_error);
    EXPECT_NEAR(0.0, account->current_money_market_fund(), this->allowable_error);
    EXPECT_NEAR(0.0, account->current_mutual_fund_value(), this->allowable_error);
    EXPECT_NEAR(0.0, account->current_reg_t_call(), this->allowable_error);
    EXPECT_NEAR(0.0, account->current_short_margin_value(), this->allowable_error);
    EXPECT_NEAR(0.0, account->current_short_option_market_value(), this->allowable_error);
    EXPECT_NEAR(0.0, account->current_short_stock_value(), this->allowable_error);
    EXPECT_NEAR(0.0, account->current_total_cash(), this->allowable_error);
    EXPECT_NEAR(0.0, account->current_is_in_call(), this->allowable_error);
    EXPECT_NEAR(0.0, account->current_unsettled_cash(), this->allowable_error);
    EXPECT_NEAR(0.0, account->current_pending_deposits(), this->allowable_error);
    EXPECT_NEAR(0.0, account->current_margin_balance(), this->allowable_error);
    EXPECT_NEAR(0.0, account->current_short_balance(), this->allowable_error);
    EXPECT_NEAR(0.0, account->current_account_value(), this->allowable_error);
}


}






















