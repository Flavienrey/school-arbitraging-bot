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

/**
 * Class Graph modeling an oriented graph with custom properties
 * @file Graph.hpp
 * @author Flavien Rey et Damien Gagnaire
 * @version 1.1 21/02/2022
 * @since 05-01-2022
 **/
class Graph {

private:

    //Nombre de sommets / Number of vertices in the graph
    int nbVertices;

    //Nombre d'arêtes / Number of edges in the graph
    int nbEdges;

    //Vector associating indexes to their respective tickers (0=>'BTC') as an example
    vector<string> associatedTickers;

    // Matrice listant les poids des connexions orientées entre les sommets (lignes vers colonnes)
    // Matrix indicating oriented connections between vertices with their weights
    vector<vector<double>> adjacencyMatrix;

public:

    //Constructor of the class, takes a filename to load the graph from and a bool to return errors if so
    Graph(const string &filename, bool *errorOccured);

    //Fonction qui ajoute un lien entre deux vertices dans la matrice d'adjacence
    bool addEdge(int firstVertice, int nextVertice, double weight);

    //Getter that returns the number of vertices
    int getNbVertices() const;

    //Getter that returns the adjacency matrix
    vector<vector<double>> getAdjacencyMatrix();

    //Setter that sets the ticker at the appropriated index
    bool setTicker(int index, string ticker);

    //Function to print the connexions of the entire graph
    void printGraph();

    //Destructor
    ~Graph();
};


#endif //BOT_D_ARBITRAGE_GRAPH_HPP
