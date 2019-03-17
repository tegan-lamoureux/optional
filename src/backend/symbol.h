#ifndef OPTIONAL_SYMBOL_H
#define OPTIONAL_SYMBOL_H

#include <memory>
#include <vector>

#include "oauth.h"
#include "rest.h"

#include "rapidjson/document.h"

namespace Optional {

// This shouold be able to take oauth credntials and token, but also get
// unauthenticated data. Two modes, delayed strikes or instant with auth.
//
// Determine whether this will be options chain or symbol data. (Or both.)
class Symbol
{
public:
    Symbol(std::string symbol_name_in, std::string oauth_uid_in);

    bool refresh_symbol();

    OAuthStatus get_authorization_status();
    std::shared_ptr<Rest> get_rest_interface();

private:
    Symbol() = delete;

    std::shared_ptr<Rest> rest_interface;
    std::shared_ptr<OAuth> authorization;

    std::string symbol_name;
    std::string symbol_post_resource_url = "https://api.tdameritrade.com/v1/instruments";

    rapidjson::Document symbol_details;

    rapidjson::Value& parse_json_field(std::string name, rapidjson::Document& to_parse);
    rapidjson::Value& parse_json_field(std::string name, rapidjson::Value& to_parse);
};

}

#endif // symbol_H


