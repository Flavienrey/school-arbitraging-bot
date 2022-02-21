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

class Graph {

private:

    //Nombre de sommets / Number of vertices in the graph
    int nbVertices;

    //Nombre d'arêtes / Number of edges in the graph
    int nbEdges;

    //Filename to load the graph from
    string filename;

    //Vector associating indexes to their respective tickers (0=>'BTC') as an example
    vector<string> associatedTickers;

    vector<vector<double>> adjacencyMatrix;  //Liste des sommets vers lequel il pointe et le poids associé

public:

    Graph(const string &filename, bool *errorOccured);

    bool addEdge(int firstVertice, int nextVertice, double weight);

    int getNbVertices() const;

    string getGraphFilename();

    vector<vector<double>> getAdjacencyMatrix();

    void setTicker(int index, string ticker);

    void printGraph();

    ~Graph();
};


#endif //BOT_D_ARBITRAGE_GRAPH_HPP
