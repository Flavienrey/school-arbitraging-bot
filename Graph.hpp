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

public:

    /**
    Constructor of the class, takes a filename to load the graph from and a bool to return errors if so
    @param filename the file that contains the graph to instantiate
    @param executionStatus a bool to set to false if the instantiation fails
    @return the instanced class
    */
    Graph(const string &filename, bool *executionStatus);


    /**
    Function that adds the edge
     from one vertice to another in the adjacency matrix
    @param firstVertice the first vertice of the edge
    @param nextVertice the one it goes to
    @param weight the weight of the edge
    @return true if it's a success, false otherwise
    */
    bool addEdge(int firstVertice, int nextVertice, double weight);


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
    Function to print the connexions of the entire graph
    */
    void printGraph();


    //Destructor
    ~Graph();
};

#endif //BOT_D_ARBITRAGE_GRAPH_HPP
