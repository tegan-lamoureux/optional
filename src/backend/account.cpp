#include "account.h"


Optional::Account::Account(OAuth& authorization_in, Rest& rest_interface_in, std::string account_number_in)
    : authorization(authorization_in)
    , rest_interface(rest_interface_in)
    , account_number(account_number_in)
{
    this->account_post_resource_url.append(account_number);
}

bool Optional::Account::refresh_account() {
    bool success = false;

    if (this->authorization.get_status() == Valid) {
        // Can also add 'fields=positions,orders' for more info.
        std::string header = std::string("Authorization: Bearer ") + authorization.get_access_token();
        std::string response = this->rest_interface.get(this->account_post_resource_url, header, success, true);
        this->account_details.Parse(response.c_str(), response.length());
    }

    return success;
}

// FIXME: refactor this out into a "get nested data" method. this is too much duplication.
std::string Optional::Account::account_type() {
    std::string data = "";

    if(this->account_details.HasMember("securitiesAccount")) {
        rapidjson::Value& account = this->account_details["securitiesAccount"];
        if (account.HasMember("type")) {
            data = account["type"].GetString();
        }
    }

    return data;
}

std::string Optional::Account::account_id() {
    std::string data = "";

    if(this->account_details.HasMember("securitiesAccount")) {
        rapidjson::Value& account = this->account_details["securitiesAccount"];
        if (account.HasMember("accountId")) {
            data = account["accountId"].GetString();
        }
    }

    return data;
}

std::string Optional::Account::round_trips() {
    std::string data = "";

    if(this->account_details.HasMember("securitiesAccount")) {
        rapidjson::Value& account = this->account_details["securitiesAccount"];
        if (account.HasMember("roundTrips")) {
            data = account["roundTrips"].GetString();
        }
    }

    return data;
}

std::string Optional::Account::is_day_trader() {
    std::string data = "";

    if(this->account_details.HasMember("securitiesAccount")) {
        rapidjson::Value& account = this->account_details["securitiesAccount"];
        if (account.HasMember("isDayTrader")) {
            data = account["isDayTrader"].GetString();
        }
    }

    return data;
}

std::string Optional::Account::is_closing_only_restricted() {
    std::string data = "";

    if(this->account_details.HasMember("securitiesAccount")) {
        rapidjson::Value& account = this->account_details["securitiesAccount"];
        if (account.HasMember("isClosingOnlyRestricted")) {
            data = account["isClosingOnlyRestricted"].GetString();
        }
    }

    return data;
}

double Optional::Account::available_funds() {
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

