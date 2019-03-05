#ifndef OPTIONAL_ACCOUNT_H
#define OPTIONAL_ACCOUNT_H

#include "oauth.h"
#include "rest.h"

#include "rapidjson/document.h"

namespace Optional {

// FIXME: This can be the top level object, which contains the rest api and the oauth object. The ueer will supply
//        credentials to here and then interact with this object alone.
class Account
{
public:
    // FIXME: Fix this, and the rest + oauth object. I don't need to make three objectgs to access my account. Streamline into one with
    // a better hierarchy.
    Account(OAuth& authorization_in, Rest& rest_interface_in, std::string account_number);

    bool refresh_account();

    // FIXME: populate with rest of available fields. genericize access so that
    //        each only uses the required string and substring data name, and json
    //        parsing is offloaded to one method (as it should be). can make recursive?
    //        pass in a n-length list of subterms and recurse until field found?
    std::string account_type();
    std::string account_id();
    std::string round_trips();
    std::string is_day_trader();
    std::string is_closing_only_restricted();
    double available_funds();

private:
    Account() = delete;

    OAuth& authorization;
    Rest& rest_interface;

    std::string account_number;
    std::string account_post_resource_url = "https://api.tdameritrade.com/v1/accounts/";

    rapidjson::Document account_details;
};

}

#endif // ACCOUNT_H


