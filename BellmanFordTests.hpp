//
// Created by Didier on 25/02/2022.
//

#ifndef BOT_D_ARBITRAGE_BELLMANFORDTESTS_HPP
#define BOT_D_ARBITRAGE_BELLMANFORDTESTS_HPP

//Starts all tests and return true if the execution is successful
bool startAllBellmanFordTests();

//Tests all different cases for the method bellmanFord of the class Graph
bool testBellmanFordAlgorithm();

//Tests all different cases for the method detectNegativeCycle of the class Graph
bool testNegativeCycleDetection();

bool testFindAndReturnWeightOfBestRoute();

#endif //BOT_D_ARBITRAGE_BELLMANFORDTESTS_HPP
