#ifndef OPTIONAL_ACCOUNT_H
#define OPTIONAL_ACCOUNT_H

#include "oauth.h"
#include "rest.h"

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

private:
    Account() = delete;

    OAuth& authorization;
    Rest& rest_interface;

    std::string account_number;
    std::string account_post_resource_url = "https://api.tdameritrade.com/v1/accounts/";
};

}

#endif // ACCOUNT_H


