#include "account.h"

#include <iomanip>
#include <sstream>

#include <fstream> // FIXME: Debug code, **Remove.


Optional::Account::Account(std::string account_number_in, std::string oauth_uid_in)
    : account_number(account_number_in)
{
    this->rest_interface = std::shared_ptr<Rest>(new Rest());
    this->authorization = std::shared_ptr<OAuth>(new OAuth(oauth_uid_in, "https://localhost", this->rest_interface));

    this->account_post_resource_url.append(account_number);
    this->account_post_resource_url.append("?fields=positions,orders");
}

bool Optional::Account::refresh_account() {
    bool success = false;

    if (this->authorization->get_status() == Valid) {
        // Can also add 'fields=positions,orders' for more info.
        std::string header = std::string("Authorization: Bearer ") + authorization->get_access_token();
        std::string response = this->rest_interface->get(this->account_post_resource_url, header, success, false);
        this->account_details.Parse(response.c_str(), response.length());

        // FIXME: Debug code, **Remove.
        static bool written_log = false;
        if (!written_log) {
            written_log = true;
            std::ofstream outfile("account_details.log");
            if (outfile) {
                outfile << response;
                outfile.close();
            }
        }
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



/**
 * Initial Balance section.
 */

double Optional::Account::initial_accrued_interest() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("initialBalances", account);
        rapidjson::Value& balance = this->parse_json_field("accruedInterest", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::initial_available_funds_non_marginable_trade() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("initialBalances", account);
        rapidjson::Value& balance = this->parse_json_field("availableFundsNonMarginableTrade", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::initial_bond_value() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("initialBalances", account);
        rapidjson::Value& balance = this->parse_json_field("bondValue", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::initial_buying_power() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("initialBalances", account);
        rapidjson::Value& balance = this->parse_json_field("buyingPower", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::initial_cash_balance() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("initialBalances", account);
        rapidjson::Value& balance = this->parse_json_field("cashBalance", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::initial_cash_available_for_trading() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("initialBalances", account);
        rapidjson::Value& balance = this->parse_json_field("cashAvailableForTrading", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::initial_cash_reciepts() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("initialBalances", account);
        rapidjson::Value& balance = this->parse_json_field("cashReceipts", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::initial_day_trading_buying_power() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("initialBalances", account);
        rapidjson::Value& balance = this->parse_json_field("dayTradingBuyingPower", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::initial_day_trading_buying_power_call() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("initialBalances", account);
        rapidjson::Value& balance = this->parse_json_field("dayTradingBuyingPowerCall", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::initial_day_trading_equity_call() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("initialBalances", account);
        rapidjson::Value& balance = this->parse_json_field("dayTradingEquityCall", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::initial_equity() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("initialBalances", account);
        rapidjson::Value& balance = this->parse_json_field("equity", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::initial_equity_percentage() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("initialBalances", account);
        rapidjson::Value& balance = this->parse_json_field("equityPercentage", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::initial_liquidation_value() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("initialBalances", account);
        rapidjson::Value& balance = this->parse_json_field("liquidationValue", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::initial_long_margin_value() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("initialBalances", account);
        rapidjson::Value& balance = this->parse_json_field("longMarginValue", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::initial_long_option_market_value() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("initialBalances", account);
        rapidjson::Value& balance = this->parse_json_field("longOptionMarketValue", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::initial_long_stock_value() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("initialBalances", account);
        rapidjson::Value& balance = this->parse_json_field("longStockValue", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::initial_maintenance_call() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("initialBalances", account);
        rapidjson::Value& balance = this->parse_json_field("maintenanceCall", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::initial_maintenance_requirement() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("initialBalances", account);
        rapidjson::Value& balance = this->parse_json_field("maintenanceRequirement", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::initial_margin() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("initialBalances", account);
        rapidjson::Value& balance = this->parse_json_field("margin", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::initial_margin_equity() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("initialBalances", account);
        rapidjson::Value& balance = this->parse_json_field("marginEquity", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::initial_money_market_fund() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("initialBalances", account);
        rapidjson::Value& balance = this->parse_json_field("moneyMarketFund", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::initial_mutual_fund_value() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("initialBalances", account);
        rapidjson::Value& balance = this->parse_json_field("mutualFundValue", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::initial_reg_t_call() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("initialBalances", account);
        rapidjson::Value& balance = this->parse_json_field("regTCall", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::initial_short_margin_value() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("initialBalances", account);
        rapidjson::Value& balance = this->parse_json_field("shortMarginValue", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::initial_short_option_market_value() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("initialBalances", account);
        rapidjson::Value& balance = this->parse_json_field("shortOptionMarketValue", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::initial_short_stock_value() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("initialBalances", account);
        rapidjson::Value& balance = this->parse_json_field("shortStockValue", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::initial_total_cash() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("initialBalances", account);
        rapidjson::Value& balance = this->parse_json_field("totalCash", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::initial_is_in_call() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("initialBalances", account);
        rapidjson::Value& balance = this->parse_json_field("isInCall", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::initial_unsettled_cash() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("initialBalances", account);
        rapidjson::Value& balance = this->parse_json_field("unsettledCash", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::initial_pending_deposits() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("initialBalances", account);
        rapidjson::Value& balance = this->parse_json_field("pendingDeposits", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::initial_margin_balance() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("initialBalances", account);
        rapidjson::Value& balance = this->parse_json_field("marginBalance", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::initial_short_balance() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("initialBalances", account);
        rapidjson::Value& balance = this->parse_json_field("shortBalance", data);

        return balance.GetDouble();
    }
    catch (...) {
        return 0.0;
    }
}

double Optional::Account::initial_account_value() {
    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("initialBalances", account);
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

std::shared_ptr<Optional::Rest> Optional::Account::get_rest_interface() {
    return this->rest_interface;
}

std::vector<std::string> Optional::Account::positions() {
    std::vector<std::string> display_data;

    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("positions", account);

        for (auto& position : data.GetArray()) {
            rapidjson::Value& instrument = this->parse_json_field("instrument", position);
            std::string header;

            std::stringstream longqty;
            std::stringstream shortqty;
            std::stringstream day_pl_percent;
            std::stringstream day_pl;
            std::stringstream market_value;
            std::stringstream purchase_price;

            bool is_option = instrument["assetType"].GetString() == std::string("OPTION");
            bool is_equity = instrument["assetType"].GetString() == std::string("EQUITY");

            longqty << std::fixed << std::setprecision(2) << position["longQuantity"].GetDouble();
            shortqty << std::fixed << std::setprecision(2) << position["shortQuantity"].GetDouble();
            day_pl_percent << std::fixed << std::setprecision(2) << position["currentDayProfitLossPercentage"].GetDouble();
            day_pl << std::fixed << std::setprecision(2) << position["currentDayProfitLoss"].GetDouble();
            market_value << std::fixed << std::setprecision(2) << position["marketValue"].GetDouble();
            purchase_price << std::fixed << std::setprecision(4) << position["averagePrice"].GetDouble();

            if (is_equity) {
                // We have a stock position.
                header = instrument["symbol"].GetString() + std::string(" [Equity]");
            }
            else if (is_option) {
                // We have an option position
                header = instrument["underlyingSymbol"].GetString() + std::string(" [Option]");
            }

            // Line 1 - Symbol name, quantity short/long, market value.
            display_data.push_back(
                    header +
                    std::string(" [+") +
                    longqty.str() +
                    std::string(" -") +
                    shortqty.str() +
                    std::string("] [$") +
                    market_value.str() +
                    std::string("]")
            );

            // Line 2 (Options only) - Call/Put Description
            if (is_option) {
                display_data.push_back(
                            std::string("\t") +
                            instrument["description"].GetString()
                        );
            }

            // Line 3, balance and P/L
            display_data.push_back(
                    std::string("\tP/L: ") +
                    day_pl_percent.str() +
                    std::string("% ($") +
                    day_pl.str() +
                    std::string(")  Purchased @ $") +
                    purchase_price.str()
            );

            display_data.push_back("");
        }

        return display_data;
    }
    catch (...) {
        return std::vector<std::string>();
    }
}

std::vector<std::string> Optional::Account::orders() {
    std::vector<std::string> display_data;

    try {
        rapidjson::Value& account = this->parse_json_field("securitiesAccount", this->account_details);
        rapidjson::Value& data = this->parse_json_field("orderStrategies", account);

        for (auto& order : data.GetArray()) {
            // Enforce only single limit orders for now.
            std::string d1 = order["orderStrategyType"].GetString();
            std::string d2 = order["orderType"].GetString();
            if (order["orderStrategyType"].GetString() != std::string("SINGLE") || order["orderType"].GetString() != std::string("LIMIT")) {
                continue;
            }

            std::stringstream placed_qty;
            std::stringstream filled_qty;
            std::stringstream price;
            std::stringstream order_id;

            placed_qty << std::fixed << std::setprecision(1) << order["quantity"].GetDouble();
            filled_qty << std::fixed << std::setprecision(1) << order["filledQuantity"].GetDouble();
            price << std::fixed << std::setprecision(2) << order["price"].GetDouble();
            order_id << order["orderId"].GetInt();

            // Line 1 - Order ID, price, status.
            display_data.push_back(
                        order_id.str() +
                        std::string(" [$") +
                        price.str() +
                        std::string("] [") +
                        order["status"].GetString() +
                        std::string("]")
                        );

            // Line 3, leg info
            for (auto& leg : order["orderLegCollection"].GetArray()) {
                rapidjson::Value& instrument = leg["instrument"];
                display_data.push_back(
                            std::string("\t") +
                            leg["instruction"].GetString() +
                            std::string(" ") +
                            instrument["symbol"].GetString() +
                            std::string(" [") +
                            instrument["assetType"].GetString() +
                            std::string("] ")
                            );
            }

            display_data.push_back(
                        std::string("\tQty Placed: ") +
                        placed_qty.str() +
                        std::string("  Qty Filled: ") +
                        filled_qty.str()
                        );

            display_data.push_back("");
        }

        return display_data;
    }
    catch (...) {
        return std::vector<std::string>();
    }
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













