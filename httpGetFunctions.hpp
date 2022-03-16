//
// Created by Didier on 09/03/2022.
//

#ifndef BOT_D_ARBITRAGE_HTTPGETFUNCTIONS_HPP
#define BOT_D_ARBITRAGE_HTTPGETFUNCTIONS_HPP
#include <cpr/cpr.h>
#include "json.hpp"
#include <iostream>
#include <string>

using json = nlohmann::json;
using namespace std;

json getApiData(const char* apilink);

json getAllSymbolsFromKucoin();
json getOrderBookfromkucoin(const string& symbol);

json getAllSymbolsFromCEX();
vector<vector<double>> getOrderBookfromCEX(const string& symbol1, const string& symbol2);



#endif //BOT_D_ARBITRAGE_HTTPGETFUNCTIONS_HPP
