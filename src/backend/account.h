#ifndef OPTIONAL_ACCOUNT_H
#define OPTIONAL_ACCOUNT_H

#include <memory>
#include <vector>

#include "oauth.h"
#include "rest.h"

#include "rapidjson/document.h"

namespace Optional {

class Account
{
public:
    Account(std::string account_number_in, std::string oauth_uid_in);

    bool refresh_account();

    // FIXME: populate with rest of available fields.
    std::string account_type();
    std::string account_id();

    unsigned int round_trips();

    bool is_day_trader();
    bool is_closing_only_restricted();

    // balances
    double accrued_interest();
    double available_funds_non_marginable_trade();
    double bond_value();
    double buying_power();
    double cash_balance();
    double cash_available_for_trading();
    double cash_reciepts();
    double day_trading_buying_power();
    double day_trading_buying_power_call();
    double day_trading_equity_call();
    double equity();
    double equity_percentage();
    double liquidation_value();
    double long_margin_value();
    double long_option_market_value();
    double long_stock_value();
    double maintenance_call();
    double maintenance_requirement();
    double margin();
    double margin_equity();
    double money_market_fund();
    double mutual_fund_value();
    double reg_t_call();
    double short_margin_value();
    double short_option_market_value();
    double short_stock_value();
    double total_cash();
    double is_in_call();
    double pending_deposits();
    double margin_balance();
    double short_balance();
    double account_value();

    OAuthStatus get_authorization_status();

private:
    Account() = delete;

    std::shared_ptr<Rest> rest_interface;
    std::shared_ptr<OAuth> authorization;

    std::string account_number;
    std::string account_post_resource_url = "https://api.tdameritrade.com/v1/accounts/";

    rapidjson::Document account_details;
};

}

#endif // ACCOUNT_H


