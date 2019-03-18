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

    // FIXME this shit
    //std::vector<std::string> get_orders() { return this->orders; }

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

    // Initial Balances
    double initial_accrued_interest();
    double initial_available_funds_non_marginable_trade();
    double initial_bond_value();
    double initial_buying_power();
    double initial_cash_balance();
    double initial_cash_available_for_trading();
    double initial_cash_reciepts();
    double initial_day_trading_buying_power();
    double initial_day_trading_buying_power_call();
    double initial_day_trading_equity_call();
    double initial_equity();
    double initial_equity_percentage();
    double initial_liquidation_value();
    double initial_long_margin_value();
    double initial_long_option_market_value();
    double initial_long_stock_value();
    double initial_maintenance_call();
    double initial_maintenance_requirement();
    double initial_margin();
    double initial_margin_equity();
    double initial_money_market_fund();
    double initial_mutual_fund_value();
    double initial_reg_t_call();
    double initial_short_margin_value();
    double initial_short_option_market_value();
    double initial_short_stock_value();
    double initial_total_cash();
    double initial_is_in_call();
    double initial_unsettled_cash();
    double initial_pending_deposits();
    double initial_margin_balance();
    double initial_short_balance();
    double initial_account_value();

    OAuthStatus get_authorization_status();
    std::shared_ptr<Rest> get_rest_interface();

    // FIXME: This should really be a collection of position classes, with all
    // formatting done in the display class.
    std::vector<std::string> positions();

    // only supports single limit orders at the moment
    // FIXME: This should really be a collection of order classes, with all
    // formatting done in the display class.
    std::vector<std::string> orders();

    // FIXME: This should really be a collection of option chain classes, with all
    // formatting done in the display class.
    std::vector<std::string> option_chain(std::string symbol, double strike);

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


