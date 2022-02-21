//
// Created by Didier on 05/01/2022.
//

#include "Graph.hpp"
#include <iostream>
#include <vector>
using namespace std;

Graph::Graph(const string &filename, bool *errorOccured) {
    this->nbVertices=0;
    this->nbEdges=0;
    this->filename=filename;

    // Opening the file
    fstream fileDataGraph;
    fileDataGraph.open("./graphes/"+filename,fstream::in);

    if(!fileDataGraph.is_open()){
        cout<<"\nError Occurred in opening the file !";
    }
    else{
        // Filling our vertices and edges variables
        fileDataGraph>>nbVertices>>nbEdges;

        // Instanciating the vectors for the adjacency matrix
        for( int i=0; i<nbVertices;i++) {
            vector<double> fillVectorWithEmptyValues;
            adjacencyMatrix.push_back(fillVectorWithEmptyValues);
            for( int j=0; j<nbVertices;j++) {
                adjacencyMatrix[i].push_back(0.0);
            }
            //Instanciating the ticker's vector
            this->associatedTickers.push_back("");
        }

        int firstVertice,nextVertice;
        double weight;

        //We read the file
        fileDataGraph>>firstVertice>>nextVertice>>weight;

        // We loop in order to read all the lines from to till the end of the file
        while(!fileDataGraph.eof()){
            addEdge(firstVertice,nextVertice,-(log(weight)));

            //We read the line from the file
            fileDataGraph>>firstVertice>>nextVertice>>weight;
        }
    }
}

bool Graph::addEdge(int first_vertice, int next_vertice, double weight) {
    if(first_vertice!=next_vertice && first_vertice<nbVertices && next_vertice<nbVertices) {
        adjacencyMatrix[first_vertice][next_vertice] = weight;
        return true;
    }
    return false;
}

void Graph::printGraph() {
    for(int i=0; i<adjacencyMatrix.size();i++){
        for(int j=0;j<adjacencyMatrix[i].size();j++){
            if(adjacencyMatrix[i][j]!=0) {
                cout << "Vertice " << i << " va vers " << j << " pour un poids de "<< adjacencyMatrix[i][j] << "\n";
            }
        }
    }
}

Graph::~Graph() {

}

string Graph::getGraphFilename() {
    return filename;
}

int Graph::getNbVertices() {
    return nbVertices;
}

vector<vector<double>> Graph::getAdjacencyMatrix() {
    return adjacencyMatrix;
}



