#include "account.h"

#include <iostream> // FIXME: remove


Optional::Account::Account(std::string account_number_in, std::string oauth_uid_in)
    : account_number(account_number_in)
{
    this->rest_interface = std::shared_ptr<Rest>(new Rest());
    this->authorization = std::shared_ptr<OAuth>(new OAuth(oauth_uid_in, "https://localhost", this->rest_interface));

    this->account_post_resource_url.append(account_number);
}

bool Optional::Account::refresh_account() {
    bool success = false;

    if (this->authorization->get_status() == Valid) {
        // Can also add 'fields=positions,orders' for more info.
        std::string header = std::string("Authorization: Bearer ") + authorization->get_access_token();
        std::string response = this->rest_interface->get(this->account_post_resource_url, header, success, false);
        this->account_details.Parse(response.c_str(), response.length());

        std::cout << response << std::endl;
    }

    // FIXME: Need a validate method, can get stuff like: { "error" : "You don't have permission to access this resource." }
    // while success is still true from the post.

    return success;
}

std::string Optional::Account::account_type() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("type", account);

        return data.GetString();
    }
    catch (...) {
        return "";
    }
}

std::string Optional::Account::account_id() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("accountId", account);

        return data.GetString();
    }
    catch (...) {
        return "";
    }
}

unsigned int Optional::Account::round_trips() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("roundTrips", account);

        return data.GetUint();
    }
    catch (...) {
        return 0;
    }
}

bool Optional::Account::is_day_trader() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("isDayTrader", account);

        return data.GetBool();
    }
    catch (...) {
        return false;
    }
}

bool Optional::Account::is_closing_only_restricted() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("isDayTrader", account);

        return data.GetBool();
    }
    catch (...) {
        return false;
    }
}

double Optional::Account::current_accrued_interest() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("currentBalances", account);
        rapidjson::Value& balance = this->parse_json_field("accruedInterest", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::current_available_funds_non_marginable_trade() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("currentBalances", account);
        rapidjson::Value& balance = this->parse_json_field("availableFundsNonMarginableTrade", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::current_bond_value() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("currentBalances", account);
        rapidjson::Value& balance = this->parse_json_field("bondValue", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::current_buying_power() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("currentBalances", account);
        rapidjson::Value& balance = this->parse_json_field("buyingPower", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::current_cash_balance() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("currentBalances", account);
        rapidjson::Value& balance = this->parse_json_field("cashBalance", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::current_cash_available_for_trading() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("currentBalances", account);
        rapidjson::Value& balance = this->parse_json_field("cashAvailableForTrading", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::current_cash_reciepts() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("currentBalances", account);
        rapidjson::Value& balance = this->parse_json_field("cashReceipts", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::current_day_trading_buying_power() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("currentBalances", account);
        rapidjson::Value& balance = this->parse_json_field("dayTradingBuyingPower", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::current_day_trading_buying_power_call() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("currentBalances", account);
        rapidjson::Value& balance = this->parse_json_field("dayTradingBuyingPowerCall", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::current_day_trading_equity_call() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("currentBalances", account);
        rapidjson::Value& balance = this->parse_json_field("dayTradingEquityCall", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::current_equity() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("currentBalances", account);
        rapidjson::Value& balance = this->parse_json_field("equity", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::current_equity_percentage() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("currentBalances", account);
        rapidjson::Value& balance = this->parse_json_field("equityPercentage", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::current_liquidation_value() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("currentBalances", account);
        rapidjson::Value& balance = this->parse_json_field("liquidationValue", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::current_long_margin_value() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("currentBalances", account);
        rapidjson::Value& balance = this->parse_json_field("longMarginValue", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::current_long_option_market_value() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("currentBalances", account);
        rapidjson::Value& balance = this->parse_json_field("longOptionMarketValue", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::current_long_stock_value() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("currentBalances", account);
        rapidjson::Value& balance = this->parse_json_field("longStockValue", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::current_maintenance_call() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("currentBalances", account);
        rapidjson::Value& balance = this->parse_json_field("maintenanceCall", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::current_maintenance_requirement() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("currentBalances", account);
        rapidjson::Value& balance = this->parse_json_field("maintenanceRequirement", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::current_margin() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("currentBalances", account);
        rapidjson::Value& balance = this->parse_json_field("margin", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::current_margin_equity() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("currentBalances", account);
        rapidjson::Value& balance = this->parse_json_field("marginEquity", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::current_money_market_fund() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("currentBalances", account);
        rapidjson::Value& balance = this->parse_json_field("moneyMarketFund", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::current_mutual_fund_value() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("currentBalances", account);
        rapidjson::Value& balance = this->parse_json_field("mutualFundValue", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::current_reg_t_call() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("currentBalances", account);
        rapidjson::Value& balance = this->parse_json_field("regTCall", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::current_short_margin_value() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("currentBalances", account);
        rapidjson::Value& balance = this->parse_json_field("shortMarginValue", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::current_short_option_market_value() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("currentBalances", account);
        rapidjson::Value& balance = this->parse_json_field("shortOptionMarketValue", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::current_short_stock_value() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("currentBalances", account);
        rapidjson::Value& balance = this->parse_json_field("shortStockValue", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::current_total_cash() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("currentBalances", account);
        rapidjson::Value& balance = this->parse_json_field("totalCash", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::current_is_in_call() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("currentBalances", account);
        rapidjson::Value& balance = this->parse_json_field("isInCall", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::current_unsettled_cash() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("currentBalances", account);
        rapidjson::Value& balance = this->parse_json_field("unsettledCash", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::current_pending_deposits() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("currentBalances", account);
        rapidjson::Value& balance = this->parse_json_field("pendingDeposits", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::current_margin_balance() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("currentBalances", account);
        rapidjson::Value& balance = this->parse_json_field("marginBalance", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::current_short_balance() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("currentBalances", account);
        rapidjson::Value& balance = this->parse_json_field("shortBalance", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::current_account_value() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("currentBalances", account);
        rapidjson::Value& balance = this->parse_json_field("accountValue", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

Optional::OAuthStatus Optional::Account::get_authorization_status() {
    return this->authorization->get_status();
}

rapidjson::Value& Optional::Account::parse_json_field(std::string name, rapidjson::Document& to_parse) {
    if (to_parse.HasMember(name.c_str())) {
        return to_parse[name.c_str()];
    }
    else {
        throw "Field does not exist!";
    }
}

rapidjson::Value& Optional::Account::parse_json_field(std::string name, rapidjson::Value& to_parse) {
    if (to_parse.HasMember(name.c_str())) {
        return to_parse[name.c_str()];
    }
    else {
        throw "Field does not exist!";
    }
}













