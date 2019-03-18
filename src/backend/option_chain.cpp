#include "option_chain.h"

#include <iomanip>
#include <sstream>
#include <ctime>

Optional::OptionChain::OptionChain(std::string symbol_name_in)
    : symbol_name(symbol_name_in)
    , authorization(nullptr)
    , rest_interface(nullptr)
    , using_authentication(false)
{
}

Optional::OptionChain::OptionChain(std::string symbol_name_in, std::shared_ptr<OAuth> oauth_in, std::shared_ptr<Rest> rest_in)
    : symbol_name(symbol_name_in)
    , authorization(oauth_in)
    , rest_interface(rest_in)
    , using_authentication(true)
{
}

bool Optional::OptionChain::refresh_chain(double strike_price, unsigned int strike_count) {
    bool success = false;
    this->strikes = strike_count;

    if (this->authorization->get_status() == Valid) {
        std::stringstream strike_count_ss;
        std::stringstream strike_price_ss;
        strike_count_ss << std::fixed << std::setprecision(2) << strike_count;
        strike_price_ss << strike_price;

        std::string fields =
                std::string("?symbol=") +
                this->symbol_name +
                std::string("&contractType=ALL") +
                std::string("&strikeCount=") +
                strike_count_ss.str() +
                std::string("&strategy=SINGLE") +
                std::string("&optionType=S");

        this->option_chain_resource_url.append(fields);

        std::string header = std::string("Authorization: Bearer ") + authorization->get_access_token();
        std::string response = this->rest_interface->get(this->option_chain_resource_url, header, success, false);
        this->symbol_details.Parse(response.c_str(), response.length());
    }
    // FIXME: Need a validate method, can get stuff like: { "error" : "You don't have permission to access this resource." }
    // while success is still true from the post.

    return success;
}

std::vector<std::string> Optional::OptionChain::calls() {
    try {
        std::vector<std::string> chain;

        rapidjson::Value& call_date_map = this->parse_json_field("callExpDateMap", this->symbol_details);
        int parsed_strikes = 0;

        for (rapidjson::Value::ConstMemberIterator date_iterator = call_date_map.MemberBegin(); date_iterator != call_date_map.MemberEnd(); ++date_iterator){
            for (rapidjson::Value::ConstMemberIterator strike_iterator = date_iterator->value.MemberBegin(); strike_iterator != date_iterator->value.MemberEnd(); ++strike_iterator){
                for (auto& strike : strike_iterator->value.GetArray()) {
                    std::string call_line = date_iterator->name.GetString();
                    call_line.append(std::string("\t") + strike_iterator->name.GetString() + std::string("\t"));

                    std::stringstream last_price;
                    std::stringstream bid_price;
                    std::stringstream ask_price;
                    std::stringstream delta;
                    std::stringstream gamma;
                    std::stringstream theta;
                    std::stringstream vega;
                    std::stringstream volume;
                    std::stringstream volatility;

                    last_price << std::fixed << std::setprecision(2) << strike["last"].GetDouble();
                    bid_price << std::fixed << std::setprecision(2) << strike["bid"].GetDouble();
                    ask_price << std::fixed << std::setprecision(2) << strike["ask"].GetDouble();
                    delta << std::fixed << std::setprecision(3) << strike["delta"].GetDouble();
                    gamma << std::fixed << std::setprecision(3) << strike["gamma"].GetDouble();
                    theta << std::fixed << std::setprecision(3) << strike["theta"].GetDouble();
                    vega << std::fixed << std::setprecision(3) << strike["vega"].GetDouble();
                    volume << std::fixed << std::setprecision(3) << strike["totalVolume"].GetDouble();
                    volatility << std::fixed << std::setprecision(3) << strike["volatility"].GetDouble();

                    call_line.append(strike["putCall"].GetString() +
                            std::string("\tLast: ") +
                            last_price.str() +
                            std::string("\tBid: ") +
                            bid_price.str() +
                            std::string("\tAsk: ") +
                            last_price.str() +
                            std::string("\tDelta: ") +
                            delta.str() +
                            std::string("\tGamma: ") +
                            gamma.str() +
                            std::string("\tTheta: ") +
                            theta.str() +
                            std::string("\tVega: ") +
                            vega.str() +
                            std::string("\tVolatility: ") +
                            volatility.str() +
                            std::string("\tVolume: ") +
                            volume.str()
                            );
                    chain.push_back(call_line);
                }
            }
        }

        return chain;
    }
    catch (...) {
        return std::vector<std::string>();
    }

}

std::vector<std::string> Optional::OptionChain::puts() {
    // TODO: this
}

rapidjson::Value& Optional::OptionChain::parse_json_field(std::string name, rapidjson::Document& to_parse) {
    if (to_parse.HasMember(name.c_str())) {
        return to_parse[name.c_str()];
    }
    else {
        throw "Field does not exist!";
    }
}

rapidjson::Value& Optional::OptionChain::parse_json_field(std::string name, rapidjson::Value& to_parse) {
    if (to_parse.HasMember(name.c_str())) {
        return to_parse[name.c_str()];
    }
    else {
        throw "Field does not exist!";
    }
}













