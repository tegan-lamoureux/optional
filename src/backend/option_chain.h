#ifndef OPTIONAL_OPTION_CHAIN_H
#define OPTIONAL_OPTION_CHAIN_H

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
class OptionChain
{
public:
    OptionChain(std::string symbol_name_in);
    OptionChain(std::string symbol_name_in, std::shared_ptr<OAuth> oauth_in, std::shared_ptr<Rest> rest_in);

    bool refresh_chain(double strike_price, unsigned int strike_count);

    std::vector<std::string> calls();
    std::vector<std::string> puts();

private:
    OptionChain() = delete;

    const bool using_authentication;

    std::shared_ptr<Rest> rest_interface;
    std::shared_ptr<OAuth> authorization;

    std::string symbol_name;
    std::string option_chain_resource_url = "https://api.tdameritrade.com/v1/marketdata/chains";

    rapidjson::Document symbol_details;

    rapidjson::Value& parse_json_field(std::string name, rapidjson::Document& to_parse);
    rapidjson::Value& parse_json_field(std::string name, rapidjson::Value& to_parse);
};

}

#endif // symbol_H


