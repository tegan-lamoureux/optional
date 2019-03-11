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
    std::string account_id();
    std::string account_type();

    unsigned int round_trips();

    bool is_day_trader();
    bool is_closing_only_restricted();

    // Current Balances
    double current_accrued_interest();
    double current_available_funds_non_marginable_trade();
    double current_bond_value();
    double current_buying_power();
    double current_cash_balance();
    double current_cash_available_for_trading();
    double current_cash_reciepts();
    double current_day_trading_buying_power();
    double current_day_trading_buying_power_call();
    double current_day_trading_equity_call();
    double current_equity();
    double current_equity_percentage();
    double current_liquidation_value();
    double current_long_margin_value();
    double current_long_option_market_value();
    double current_long_stock_value();
    double current_maintenance_call();
    double current_maintenance_requirement();
    double current_margin();
    double current_margin_equity();
    double current_money_market_fund();
    double current_mutual_fund_value();
    double current_reg_t_call();
    double current_short_margin_value();
    double current_short_option_market_value();
    double current_short_stock_value();
    double current_total_cash();
    double current_is_in_call();
    double current_unsettled_cash();
    double current_pending_deposits();
    double current_margin_balance();
    double current_short_balance();
    double current_account_value();



    OAuthStatus get_authorization_status();

private:
    Account() = delete;

    std::shared_ptr<Rest> rest_interface;
    std::shared_ptr<OAuth> authorization;

    std::string account_number;
    std::string account_post_resource_url = "https://api.tdameritrade.com/v1/accounts/";

    rapidjson::Document account_details;

    rapidjson::Value& parse_json_field(std::string name, rapidjson::Document& to_parse);
    rapidjson::Value& parse_json_field(std::string name, rapidjson::Value& to_parse);
};

}

#endif // ACCOUNT_H


