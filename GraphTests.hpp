//
// Created by Didier on 22/02/2022.
//

#ifndef BOT_D_ARBITRAGE_GRAPHTESTS_HPP
#define BOT_D_ARBITRAGE_GRAPHTESTS_HPP

//Starts all tests and return true if the execution is successful
bool startAllGraphTests();

//Tests all different cases for the constructor of the class Graph
bool testGraph();

//Tests all different cases for the method setWeight of the class Graph
bool testSetWeight();

//Tests all different cases for the method setTicker of the class Graph
bool testSetTicker();

//Tests all different cases for the method convertNegativeLogToOriginal of the class Graph
bool testConvertNegativeToLogOriginal();

#endif //BOT_D_ARBITRAGE_GRAPHTESTS_HPP
