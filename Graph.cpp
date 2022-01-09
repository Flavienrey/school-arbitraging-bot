//
// Created by Didier on 05/01/2022.
//

#include "Graph.hpp"

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

        // Instanciating the vectors for the adjacency list
        for( int i=0; i<nbVertices;i++) {
            vector<pair<int, double>> fillVectorWithEmptyValues;
            adjacencyList.push_back(fillVectorWithEmptyValues);
        }

        int firstVertice,nextVertice;
        double weight;

        //We read the file
        fileDataGraph>>firstVertice>>nextVertice>>weight;
        // We loop in order to read all the lines from to till the end of the file
        while(!fileDataGraph.eof()){
            addEdge(firstVertice,nextVertice,-(log(weight)));
            //On lit la ligne du fichier
            fileDataGraph>>firstVertice>>nextVertice>>weight;
        }
    }
}

bool Graph::addEdge(int first_vertice, int next_vertice, double weight) {
    if(first_vertice!=next_vertice && first_vertice<nbVertices && next_vertice<nbVertices) {
        adjacencyList[first_vertice].push_back(make_pair(next_vertice, weight));
        return true;
    }
    return false;
}

void Graph::printGraph() {
    for(int i=0; i<adjacencyList.size();i++){
        for(int j=0;j<adjacencyList[i].size();j++){
            cout<<"Vertice "<<i<<" va vers "<<adjacencyList[i][j].first<<" pour un poids de "<<adjacencyList[i][j].second<<"\n";
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

vector<vector<pair<int, double>>> Graph::getAdjacencyList() {
    return adjacencyList;
}



