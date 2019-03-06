#include "account.h"

#include "rapidjson/document.h"

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

        rapidjson::Document account_details;
        account_details.Parse(response.c_str(), response.length());

        // it works!!
    }

    return success;
}

