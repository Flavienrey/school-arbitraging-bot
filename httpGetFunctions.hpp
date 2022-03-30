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
vector<vector<double>> getOrderBookfromKucoin(const string& symbol1, const string& symbol2);

json getAllSymbolsFromCEX();
vector<vector<double>> getOrderBookfromCexIO(const string& symbol1, const string& symbol2);
vector<vector<double>> getOrderBookfromLatoken(const string& symbol1, const string& symbol2);


#endif //BOT_D_ARBITRAGE_HTTPGETFUNCTIONS_HPP
