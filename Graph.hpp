//
// Created by Didier on 05/01/2022.
//

#ifndef BOT_D_ARBITRAGE_GRAPH_HPP
#define BOT_D_ARBITRAGE_GRAPH_HPP

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

#include <ctgmath>

#define DISPLAY_EXECUTION false
#define CLASSICAL_WEIGHT 1
#define NEGATIVE_LOG 0

/**
 * Class Graph modeling an oriented graph with custom properties
 * @file Graph.hpp
 * @author Flavien Rey et Damien Gagnaire
 * @version 1.1 21/02/2022
 * @since 05-01-2022
 **/
class Graph {

private:

    //Number of vertices in the graph (Sommets)
    int nbVertices;

    //Number of edges in the graph (Arêtes)
    int nbEdges;

    //Vector associating indexes to their respective tickers (0=>'BTC') as an example
    vector<string> associatedTickers;

    // Matrix indicating oriented connections between vertices with their weights
    vector<vector<double>> adjacencyMatrix;

    //Bellman Ford Variables----------------------------------------------------------

    //2D Array keeping in memory the previous vertice for each vertice
    vector<int> previousVertices;

    //2D Array to keep in mind the sum of weights (ratios) from the source for each vertice
    vector<double> weightsFromSource;

public:


    /**
    Constructor of the class, takes a filename to load the graph from and a bool to return errors if so
    @param filename the file that contains the graph to instantiate
    @param executionStatus a bool to set to false if the instantiation fails
    @return the instanced class
    */
    Graph(const string &filename, bool *executionStatus, int weightMode = NEGATIVE_LOG);


    /**
    Getter that returns the number of vertices
    @return the number of vertices in the graph
    */
    int getNbVertices() const;


    /**
    Getter that returns the adjacency matrix
    @return the adjacency matrix
    */
    vector<vector<double>> getAdjacencyMatrix();


    /**
    Setter that sets the ticker at the appropriated index
    @param index index of the vertice
    @param ticker the string to set it to
    @return true if successful, false otherwise
    */
    bool setTicker(int index, string ticker);

    /**
    Setter that sets the weight of the appropriated edge
    @param indexStart index at the start of the edge
    @param indexEnd index at the end of the edge
    @param ratio change ratio between the two edge
    @return true if successful, false otherwise
    */
    bool setWeight(int indexStart, int indexEnd, double ratio, int weightMode);


    /**
    Function to print the connexions of the entire graph
    */
    void printGraph();


    /**
    Function to check if an index is valid
    @param sourceIndex Index of the vertice to check validity
    @returns true if valid, false if not valid
    */
    bool isIndexValid(int index) const;


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
    Converts the Negative Log weight to the original base10 weight
    @params previousVertices : 2D Array keeping in memory the previous vertice for each vertice
    @returns a double which is the converted Value
    */
    static double convertNegativeLogToOriginal(double weight);

    //Destructor
    ~Graph();
};

#endif //BOT_D_ARBITRAGE_GRAPH_HPP
