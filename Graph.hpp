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

using json = nlohmann::json;
using namespace std;

#include <ctgmath>

#define DISPLAY_EXECUTION false

/**
 * Class Graph modeling an oriented graph with custom properties
 * @file Graph.hpp
 * @author Flavien Rey et Damien Gagnaire
 * @version 1.1 21/02/2022
 * @since 05-01-2022
 **/
class Graph {

public:

    //Number of vertices in the graph (Sommets)
    int nbVertices;

    //Number of edges in the graph (Arêtes)
    int nbEdges;

    //Vector associating indexes to their respective tickers (0=>'BTC') as an example
    vector<string> associatedTickersList;

    //Dictionary associating indexes to their respective tickers (0=>'BTC') as an example
    map<string, int> associatedTickersMap;

    // Matrix indicating oriented connections between vertices with their weights
    vector<vector<double>> adjacencyMatrix;

    //Bellman Ford Variables----------------------------------------------------------

    //2D Array keeping in memory the previous vertice for each vertice
    vector<int> previousVertices;

    //2D Array to keep in mind the sum of weights (ratios) from the source for each vertice
    vector<double> weightsFromSource;

public:

    /**
    Constructor of the class, initialises the basic attributes only
    @return the instanced class
    */
    Graph(int nbVertices = 0, int nbEdges = 0);


    /**
    Constructor of the class, takes a filename to load the graph from and a bool to return errors if so
    @param filename the file that contains the graph to instantiate
    @param executionStatus a bool to set to false if the instantiation fails
    @return the instanced class
    */
    Graph(const string &filename, bool *executionStatus);


    /**
    Function that initiliazes the adjacency matrix, based on the number of vertices
    */
    void initializeAdjacencyMatrix();


    /**
    Getter that returns the number of vertices
    @return the number of vertices in the graph
    */
    int getNbVertices() const;


    /**
    Getter that returns the adjacency matrix
    @return the adjacency matrix
    */
    vector<vector<double>> getAdjacencyMatrix() const;


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
    Setter that sets the ticker at the appropriated index
    @param index index of the vertice
    @param ticker the string to set it to
    @return true if successful, false otherwise
    */
    bool setTicker(int index, const string& ticker);


    /**
    Add a new ticker to the map and list of tickets
    @param ticker the string to set it to
    @CAREFUL doesn't increase the size of the adjacencyMatrix
    @return true if successful, false otherwise
    */
    bool addTicker(const string& ticker);


    /**
    Setter that sets the weight of the appropriated edge using indexes
    @param indexStart index at the start of the edge
    @param indexEnd index at the end of the edge
    @param ratio change ratio between the two edge
    */
    void setWeightFromIndexes(int indexStart, int indexEnd, double ratio);


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
    @params usdIndex :  Index of the usd token (reference)
    @returns -1 if there is an error, the token price otherwise
    */
    double getTokenPriceFromIndex(int tokenIndex, int usdIndex);


    /**
    Used to get the price in $ of an asset from its ticker and the usd ticker
    @params tokenTicker : Ticker of the token we want the price
    @params usdTicker :  Ticker of the usd token
    @returns -1 if there is an error, the token price otherwise
    */
    double getTokenPriceFromTickers(const string& tokenTicker, const string& usdTicker);


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
    Fill the tickers list and map using kucoin's data fetched
    @uses j_filler : JSON market data with all the symbols of pairs from tickers
    @returns Boolean : true if there is execution successful, false otherwise
    */
    bool fillTickersWithKucoin(const json& j_filler);

    /**
    Fill the matrive using kucoin's data fetched
    @uses have the URL of the kucoin's data inside, call it after fillTickersWithKucoin
    @returns Boolean : true if there is execution successful, false otherwise
    */
    bool updateMatrixWithKucoin();

    //Destructor
    ~Graph();
};

#endif //BOT_D_ARBITRAGE_GRAPH_HPP
