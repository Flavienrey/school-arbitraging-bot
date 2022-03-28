//
// Created by Didier on 28/03/2022.
//

#ifndef BOT_D_ARBITRAGE_USEFUL_FUNCTIONS_HPP
#define BOT_D_ARBITRAGE_USEFUL_FUNCTIONS_HPP

#include <string>
#include <vector>
using namespace std;

bool writeOpportunitiesInCSV(const string& filename, const string& exchange, const string& bestRoute, double opportunitySize, double percentage);

bool createColumnTitlesInCSV(const string& filename);

#endif //BOT_D_ARBITRAGE_USEFUL_FUNCTIONS_HPP
