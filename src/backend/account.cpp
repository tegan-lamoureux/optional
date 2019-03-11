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

// FIXME: refactor this out into a "get nested data" method. this is too much duplication.
std::string Optional::Account::account_type() {
    auto data_it = this->account_details.FindMember("securitiesAccount");

    if (data_it != account_details.MemberEnd()) {
        data_it = data_it->value.FindMember("type");
        if (data_it != account_details.MemberEnd()) {
            return data_it->value.GetString();
        }
    }

    return "null";
}

std::string Optional::Account::account_id() {
    auto data_it = this->account_details.FindMember("securitiesAccount");

    if (data_it != account_details.MemberEnd()) {
        data_it = data_it->value.FindMember("accountId");
        if (data_it != account_details.MemberEnd()) {
            return data_it->value.GetString();
        }
    }

    return "null";
}

unsigned int Optional::Account::round_trips() {
    auto data_it = this->account_details.FindMember("securitiesAccount");

    if (data_it != account_details.MemberEnd()) {
        data_it = data_it->value.FindMember("roundTrips");
        if (data_it != account_details.MemberEnd()) {
            return data_it->value.GetUint();
        }
    }

    return 0;
}

bool Optional::Account::is_day_trader() {
    auto data_it = this->account_details.FindMember("securitiesAccount");

    if (data_it != account_details.MemberEnd()) {
        data_it = data_it->value.FindMember("isDayTrader");
        if (data_it != account_details.MemberEnd()) {
            return data_it->value.GetBool();
        }
    }

    return false;
}

bool Optional::Account::is_closing_only_restricted() {
    auto data_it = this->account_details.FindMember("securitiesAccount");

    if (data_it != account_details.MemberEnd()) {
        data_it = data_it->value.FindMember("isClosingOnlyRestricted");
        if (data_it != account_details.MemberEnd()) {
            return data_it->value.GetBool();
        }
    }

    return false;
}

double Optional::Account::accrued_interest() {
    double data = 0.0;

    if(this->account_details.HasMember("securitiesAccount")) {
        rapidjson::Value& account = this->account_details["securitiesAccount"];
        if (account.HasMember("initialBalances")) {
            rapidjson::Value& balances = account["initialBalances"];
            if (account.HasMember("availableFundsNonMarginableTrade")) {
                data = account["availableFundsNonMarginableTrade"].GetDouble();
            }
        }
    }

    return data;
}

double Optional::Account::available_funds_non_marginable_trade()
{

}

double Optional::Account::bond_value()
{

}

double Optional::Account::buying_power()
{

}

double Optional::Account::cash_balance()
{

}

double Optional::Account::cash_available_for_trading()
{

}

double Optional::Account::cash_reciepts()
{

}

double Optional::Account::day_trading_buying_power()
{

}

double Optional::Account::day_trading_buying_power_call()
{

}

double Optional::Account::day_trading_equity_call()
{

}

double Optional::Account::equity()
{

}

double Optional::Account::equity_percentage()
{

}

double Optional::Account::liquidation_value()
{

}

double Optional::Account::long_margin_value()
{

}

double Optional::Account::long_option_market_value()
{

}

double Optional::Account::long_stock_value()
{

}

double Optional::Account::maintenance_call()
{

}

double Optional::Account::maintenance_requirement()
{

}

double Optional::Account::margin()
{

}

double Optional::Account::margin_equity()
{

}

double Optional::Account::money_market_fund()
{

}

double Optional::Account::mutual_fund_value()
{

}

double Optional::Account::reg_t_call()
{

}

double Optional::Account::short_margin_value()
{

}

double Optional::Account::short_option_market_value()
{

}

double Optional::Account::short_stock_value()
{

}

double Optional::Account::total_cash()
{

}

double Optional::Account::is_in_call()
{

}

double Optional::Account::pending_deposits()
{

}

double Optional::Account::margin_balance()
{

}

double Optional::Account::short_balance()
{

}

double Optional::Account::account_value()
{

}

Optional::OAuthStatus Optional::Account::get_authorization_status() {
    return this->authorization->get_status();
}













