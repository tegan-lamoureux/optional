#include "option_chain.h"

#include <iomanip>
#include <sstream>

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
                std::string("&strategy=CALENDAR") +
                std::string("&strike=") +
                strike_price_ss.str() +
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
        rapidjson::Value& call_date_map = this->parse_json_field("callExpDateMap", this->symbol_details);
        rapidjson::Value& put_date_map = this->parse_json_field("putExpDateMap", this->symbol_details);

        for (auto date = call_date_map.Begin(); date != call_date_map.End(); date++) {

            //********************************
            // Left off here.  <<<<<<<<<<<<<<<
            //********************************
            // Look at json options chain to left, pull second item (closest day), display chain from that,
            // and keep going until have enough.
            std::string actual = (*date).GetString();
            actual = (*date).GetString();
//            // Enforce only single limit orders for now.
//            std::string d1 = order["orderStrategyType"].GetString();
//            std::string d2 = order["orderType"].GetString();
//            if (order["orderStrategyType"].GetString() != std::string("SINGLE") || order["orderType"].GetString() != std::string("LIMIT")) {
//                continue;
//            }

//            std::stringstream placed_qty;
//            std::stringstream filled_qty;
//            std::stringstream price;
//            std::stringstream order_id;

//            placed_qty << std::fixed << std::setprecision(1) << order["quantity"].GetDouble();
//            filled_qty << std::fixed << std::setprecision(1) << order["filledQuantity"].GetDouble();
//            price << std::fixed << std::setprecision(2) << order["price"].GetDouble();
//            order_id << order["orderId"].GetInt();

//            // Line 1 - Order ID, price, status.
//            display_data.push_back(
//                        order_id.str() +
//                        std::string(" [$") +
//                        price.str() +
//                        std::string("] [") +
//                        order["status"].GetString() +
//                    std::string("]")
//                    );

//            // Line 3, leg info
//            for (auto& leg : order["orderLegCollection"].GetArray()) {
//                rapidjson::Value& instrument = leg["instrument"];
//                display_data.push_back(
//                            std::string("\t") +
//                            leg["instruction"].GetString() +
//                        std::string(" ") +
//                        instrument["symbol"].GetString() +
//                        std::string(" [") +
//                        instrument["assetType"].GetString() +
//                        std::string("] ")
//                        );
//            }

//            display_data.push_back(
//                        std::string("\tQty Placed: ") +
//                        placed_qty.str() +
//                        std::string("  Qty Filled: ") +
//                        filled_qty.str()
//                        );

//            display_data.push_back("");
        }

    }
    catch (...) {
        return std::vector<std::string>();
    }

}

std::vector<std::string> Optional::OptionChain::puts() {

}

//double Optional::OptionChain::initial_short_balance() {
//    try {
//        rapidjson::Value& Symbol = this->parse_json_field("securitiesSymbol", this->Symbol_details);
//        rapidjson::Value& data = this->parse_json_field("initialBalances", Symbol);
//        rapidjson::Value& balance = this->parse_json_field("shortBalance", data);

//        return balance.GetDouble();
//    }
//    catch (...) {
//        return 0.0;
//    }
//}

//std::vector<std::string> Optional::OptionChain::positions() {
//    std::vector<std::string> display_data;

//    try {
//        rapidjson::Value& Symbol = this->parse_json_field("securitiesSymbol", this->Symbol_details);
//        rapidjson::Value& data = this->parse_json_field("positions", Symbol);

//        for (auto& position : data.GetArray()) {
//            rapidjson::Value& instrument = this->parse_json_field("instrument", position);
//            std::string header;

//            std::stringstream longqty;
//            std::stringstream shortqty;
//            std::stringstream day_pl_percent;
//            std::stringstream day_pl;
//            std::stringstream market_value;
//            std::stringstream purchase_price;

//            bool is_option = instrument["assetType"].GetString() == std::string("OPTION");
//            bool is_equity = instrument["assetType"].GetString() == std::string("EQUITY");

//            longqty << std::fixed << std::setprecision(2) << position["longQuantity"].GetDouble();
//            shortqty << std::fixed << std::setprecision(2) << position["shortQuantity"].GetDouble();
//            day_pl_percent << std::fixed << std::setprecision(2) << position["currentDayProfitLossPercentage"].GetDouble();
//            day_pl << std::fixed << std::setprecision(2) << position["currentDayProfitLoss"].GetDouble();
//            market_value << std::fixed << std::setprecision(2) << position["marketValue"].GetDouble();
//            purchase_price << std::fixed << std::setprecision(4) << position["averagePrice"].GetDouble();

//            if (is_equity) {
//                // We have a stock position.
//                header = instrument["symbol"].GetString() + std::string(" [Equity]");
//            }
//            else if (is_option) {
//                // We have an option position
//                header = instrument["underlyingSymbol"].GetString() + std::string(" [Option]");
//            }

//            // Line 1 - Symbol name, quantity short/long, market value.
//            display_data.push_back(
//                    header +
//                    std::string(" [+") +
//                    longqty.str() +
//                    std::string(" -") +
//                    shortqty.str() +
//                    std::string("] [$") +
//                    market_value.str() +
//                    std::string("]")
//            );

//            // Line 2 (Options only) - Call/Put Description
//            if (is_option) {
//                display_data.push_back(
//                            std::string("\t") +
//                            instrument["description"].GetString()
//                        );
//            }

//            // Line 3, balance and P/L
//            display_data.push_back(
//                    std::string("\tP/L: ") +
//                    day_pl_percent.str() +
//                    std::string("% ($") +
//                    day_pl.str() +
//                    std::string(")  Purchased @ $") +
//                    purchase_price.str()
//            );

//            display_data.push_back("");
//        }

//        return display_data;
//    }
//    catch (...) {
//        return std::vector<std::string>();
//    }
//}

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













