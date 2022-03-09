//
// Created by Didier on 22/02/2022.
//

#ifndef BOT_D_ARBITRAGE_GRAPHTESTS_HPP
#define BOT_D_ARBITRAGE_GRAPHTESTS_HPP

//Starts all tests and return true if the execution is successful
bool startAllGraphTests();

//Tests all different cases for the constructor of the class Graph
bool testGraphConstructor();

//Tests all different cases for the method setWeight of the class Graph
bool testSetWeightFromIndexes();

//Tests all different cases for the method setTicker of the class Graph
bool testSetTicker();

//Tests all different cases for the method getTokenPriceFromIndex of the class Graph
bool testGetTokenPriceFromIndex();

//Tests all different cases for the method convertNegativeLogToOriginal of the class Graph
bool testConvertNegativeToLogOriginal();

//Tests all different cases for the method getTokenPriceFromTicker of the class Graph
bool testGetTokenPriceFromTicker();

//Tests all different cases for the method getTokenPriceFromTickers of the class Graph
bool testGetTokenPriceFromTickers();

#endif //BOT_D_ARBITRAGE_GRAPHTESTS_HPP
