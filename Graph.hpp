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
    int nbVertices; //Nombre de sommets
    int nbEdges; //Nombre d'arêtes
    string filename;
    vector<string> associatedTickers;
    vector<vector<pair<int, double>>> adjacencyList;  //Liste des sommets vers lequel il pointe et le poids associé

public:

    Graph(const string &filename, bool *errorOccured);

    bool addEdge(int firstVertice, int nextVertice, double weight);

    int getNbVertices();

    string getGraphFilename();

    vector<vector<pair<int, double>>> getAdjacencyList();

    void printGraph();

    ~Graph();
};


#endif //BOT_D_ARBITRAGE_GRAPH_HPP
