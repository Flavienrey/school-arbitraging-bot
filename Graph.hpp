//
// Created by Didier on 05/01/2022.
//

#ifndef BOT_D_ARBITRAGE_GRAPH_HPP
#define BOT_D_ARBITRAGE_GRAPH_HPP

#include "json.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <ctgmath>

using json = nlohmann::json;
using namespace std;

/**
 * Class Graph modeling an oriented graph with custom properties
 * @file Graph.hpp
 * @author Flavien Rey et Damien Gagnaire
 * @version 1.1 21/02/2022
 * @since 05-01-2022
 **/
class Graph {

private:

    //Number of vertices in the graph
    int nbVertices;

    //Number of edges in the graph
    int nbEdges;

    //Vector associating indexes to their respective tickers (0=>'BTC') as an example
    vector<string> associatedTickersList;

    //Dictionary associating indexes to their respective tickers (0=>'BTC') as an example
    map<string, int> associatedTickersMap;

    // 2D Array indicating oriented connections between vertices with their weights
    vector<vector<pair<int,double>>> adjacencyList;

    //Bellman Ford Variables----------------------------------------------------------

    //Source index for the bellmanFord execution
    int sourceIndex;

    //2D Array keeping in memory the previous vertice for each vertice
    vector<int> previousVertices;

    //2D Array to keep in mind the sum of weights (ratios) from the source for each vertice
    vector<double> weightsFromSource;

    //A vector keeping in memory the best route in the graph
    vector<int> bestRoute;

public:

    //Basic functions : Constructor, Getters ______________________________________________________________________________________________
    /**
    Constructor of the class, initialises the basic attributes only
    @return the instanced class
    */
    Graph();


    /**
    Constructor of the class, takes a filename to load the graph from and a bool to return errors if so
    @param filename the file that contains the graph to instantiate
    @param executionStatus a bool to set to false if the instantiation fails
    @return the instanced class
    */
    Graph(const string &filename, bool *executionStatus);


    /**
    Getter that returns the number of vertices
    @return the number of vertices in the graph
    */
    int getNbVertices() const;


    /**
    Getter that returns the adjacency list
    @return the adjacency list
    */
    vector<vector<pair<int,double>>> getAdjacencyList() const;


    /**
    Getter that returns the previous vertices vector
    @return previousVertices
    */
    vector<int> getPreviousVertices() const;


    /**
    Getter that returns the weights from source vector
    @return weightsFromSource
    */
    vector<double> getWeightsFromSource() const;


    /**
    Getter that returns the ticker of the appropriated index
    @param index index of the vertice
    @return ticker if successful, "ERROR" otherwise
    */
    string getTicker(int index);


    /**
    Getter that returns the best route after it has been calculated
    @return the best route
    */
    vector<int> getBestRoute();


    //Setters ______________________________________________________________________________________________
    /**
    Setter that sets the ticker at the appropriated existing index
    @param index index of the vertice
    @param ticker the string to set it to
    @return true if successful, false otherwise
    */
    bool setTicker(int index, const string& ticker);


    /**
    Add a new ticker to the map and list of tickers
    @param ticker the string to set it to
    @CAREFUL doesn't increase the size of the adjacencyList
    @return true if successful, false otherwise
    */
    bool addTicker(const string& ticker);


    /**
    Setter that sets the weight of the appropriated edge using indexes
    @param indexStart index at the start of the edge
    @param indexEnd index at the end of the edge
    @param ratio change ratio between the two edge
    */
    bool setWeightFromIndexes(int indexStart, int indexEnd, double ratio);


    /**
    Setter that adds the weight of the appropriated edge using indexes in the list
    Both vertices should exist before calling this function
    @param indexStart index at the start of the edge
    @param indexEnd index at the end of the edge
    @param ratio change ratio between the two edge
    @returns a bool indicating if the execution is successful
    */
    bool addEdgeToAdjacencyList(int indexStart, int indexEnd, double weight);


    /**
    Setter that sets the weight of the appropriated edge using string tickers
    @param tickerStart index at the start of the edge
    @param tickerEnd index at the end of the edge
    @param ratio change ratio between the two edge
    @return true if successful, false otherwise
    */
    bool setWeightFromTickers(const string& tickerStart, const string& tickerEnd, double ratio);


    /**
    Function to check if an index is valid
    @param sourceIndex Index of the vertice to check validity
    @returns true if valid, false if not valid
    */
    bool isIndexValid(int index) const;


    /**
    Getter that returns the index of the associated ticker
    @params tokenTicker : Ticker of the token we want the price
    @returns -1 if there is an error, the token price otherwise
    */
    int getIndex(const string& ticker);


    /**
    Used to get the price in $ of an asset from its index
    @params tokenIndex : Index of the token we want the price
    @params baseIndex :  Index of the reference token
    @returns -1 if there is an error, the token price otherwise
    */
    double getTokenPriceFromIndex(int tokenIndex, int baseIndex);


    /**
    Used to get the price in $ of an asset from its ticker and the usd ticker
    @params tokenTicker : Ticker of the token we want the price
    @params referenceTicker :  Ticker of the reference token
    @returns -1 if there is an error, the token price otherwise
    */
    double getTokenPriceFromTickers(const string& tokenTicker, const string& referenceTicker);


    /**
    Used to get the price in $ of an asset from its ticker
    @params tokenTicker : Ticker of the token we want the price
    @returns -1 if there is an error, the token price otherwise
    */
    double getTokenPriceFromTicker(const string& tokenTicker);


    /**
    Converts the Negative Log weight to the original base10 weight
    @params previousVertices : 2D Array keeping in memory the previous vertice for each vertice
    @returns a double which is the converted Value
    */
    static double convertNegativeLogToOriginal(double weight);


    /**
    Checks if the edge between start and end vertice exists in the adjacencyList
    @params indexStart : index of the starting vertice of the edge
    @params indexEnd : index of the ending vertice of the edge
    @returns index in the adjacencyList of the indexEnc
    */
    int getIndexInAdjacencyList(int indexStart, int indexEnd);


    /**
    Checks if the two vertices given are not equals and if they are valid
    @params indexStart : index of the starting vertice of the edge
    @params indexEnd : index of the ending vertice of the edge
    @returns boolean : true if valid, false otherwise
    */
    bool isCombinationOfVerticesValid(int indexStart, int indexEnd) const;


    //BellmanFord Functions ______________________________________________________________________________________________
    /**
   Bellman Ford Implementation to detect negative cycles
   @param sourceIndex Index of the vertice source
   @uses previousVertices : 2D Array keeping in memory the previous vertice for each vertice
   @uses weightsFromSource : 2D Array to keep in mind the sum of weights (ratios) to the source for each vertice
   */
    void bellmanFord(int sourceIndex);


    /**
    Detects if there is a negative cycle in the previous results of the Bellman Ford Algorithm
    @uses previousVertices : 2D Array keeping in memory the previous vertice for each vertice
    @uses weightsFromSource : 2D Array to keep in mind the sum of weights (ratios) to the source for each vertice
    @returns Boolean : true if there is a negative cycle, false otherwise
    */
    bool detectNegativeCycle();


    /**
    Find and returns the weight best route to arbitrage in the graph
    @uses previousVertices : 2D Array keeping in memory the previous vertice for each vertice
    @uses weightsFromSource : 2D Array to keep in mind the sum of weights (ratios) to the source for each vertice
    @uses bestRoute : fills the bestRoute
    @returns a double which is the weight of the best route from the sourceIndex in the graph
    */
    double findAndReturnWeightOfBestRoute();


    /**
    Displays the route and the percentage that can be earned if
    @param weight : the weight (still in negative log thought)
    @uses bestRoute
    @returns percentage : the amount winnable if the arbitrage is executed
    */
    double displayRouteAndPercentage(double weight);


    //API functions to fetch the data into the graph ______________________________________________________________________________________________

    //API functions for Kucoin ______________________________________________________________________________________________
    /**
    Fill the tickers list and map using kucoin's data fetched
    @uses j_filler : JSON market data with all the symbols of pairs from tickers
    @returns Boolean : true if there is execution successful, false otherwise
    */
    bool fillTickersWithKucoin(const json& j_filler);


    /**
    Fill the adjacencyList using kucoin's data fetched
    @uses have the URL of the kucoin's data inside, call it after fillTickersWithKucoin
    @returns Boolean : true if there is execution successful, false otherwise
    */
    bool updateAdjacencyListWithKucoin();


    //API functions for Cex.io ______________________________________________________________________________________________
    /**
    Fill the tickers list and map using CexIO's data fetched
    @uses j_filler : JSON market data with all the symbols of pairs from tickers
    @returns Boolean : true if there is execution successful, false otherwise
    */
    bool fillTickersWithCexIO(const json& j_filler);

    /**
    Fill the adjacencyList using kucoin's data fetched
    @uses have the URL of the kucoin's data inside, call it after fillTickersWithKucoin
    @returns Boolean : true if there is execution successful, false otherwise
    */
    bool updateAdjacencyListWithCexIO();


    //API functions for LaToken ______________________________________________________________________________________________
    /**
     *
     * @param quoteToken
     * @param baseToken
     * @param sellPrice
     * @param buyPrice
     * @return
     */
    bool updateAdjacencyListWithLaToken(const string &quoteToken, const string &baseToken, double sellPrice, double buyPrice);


    /**
     *
     * @return
     */
    bool fillTickersFromLaToken();
};

#endif //BOT_D_ARBITRAGE_GRAPH_HPP
