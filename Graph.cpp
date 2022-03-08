//
// Created by Didier on 05/01/2022.
//

#include "Graph.hpp"
#include <iostream>
#include <utility>
#include <vector>
#include <limits>

using namespace std;

//Constructor of the class, takes a filename to load the graph from and a bool to return errors if so
Graph::Graph(const string &filename, bool *executionStatus, int weightMode) {

    //Setting private variables to default values
    this->nbVertices = 0;
    this->nbEdges = 0;

    // Opening the file
    fstream fileDataGraph;
    fileDataGraph.open("./Graphs/" + filename, fstream::in);

    if (!fileDataGraph.is_open()) {
        cout << "[ERROR] Error Occurred while opening the file !" << endl;
        *executionStatus = false;
    } else {

        //We indicate to the main program that the execution is still good, for later purposes
        *executionStatus = true;

        if (DISPLAY_EXECUTION) {
            //Telling the user that everything works
            cout << "[LOADING] Opened the file successfully" << endl;
        }

        // Filling our vertices and edges variables
        fileDataGraph >> nbVertices >> nbEdges;

        // Instantiating the vectors for the adjacency matrix
        for (int i = 0; i < nbVertices; i++) {
            vector<double> fillVectorWithEmptyValues;
            this->adjacencyMatrix.push_back(fillVectorWithEmptyValues);

            for (int j = 0; j < nbVertices; j++) {
                this->adjacencyMatrix[i].push_back(numeric_limits<double>::infinity());
            }
        }

        int firstVertice, nextVertice;
        double weight;

        if (DISPLAY_EXECUTION) {
            //Telling the user more infos that he knows
            cout << "[LOADING] All class vectors successfully initialised ..." << endl;

            //Telling the user more infos that he knows
            cout << "[LOADING] Loading graph with " << nbVertices << " vertices and " << nbEdges << " edges ..."
                 << endl;
        }

        // We loop in order to read all the lines from to till the end of the file
        while (!fileDataGraph.eof()) {

            try {
                //We read the line from the file again
                fileDataGraph >> firstVertice >> nextVertice >> weight;

                bool success = false;

                // We add the edge in our adjacency matrix
                success = setWeight(firstVertice, nextVertice, weight,weightMode);

                if(success){
                    if (DISPLAY_EXECUTION) {
                        if(weightMode==NEGATIVE_LOG) {
                            //We print a message in the console
                            cout << "[INSERTION] Insertion of an edge from vertice " << firstVertice << " to vertice "<< nextVertice << " with a weight of " << -(log(weight)) << " !" << endl;
                        }
                        else if(weightMode==CLASSICAL_WEIGHT){
                            //We print a message in the console
                            cout << "[INSERTION] Insertion of an edge from vertice " << firstVertice << " to vertice "<< nextVertice << " with a weight of " << weight << " !" << endl;
                        }
                    }
                }

                if (!success) {
                    throw invalid_argument( "[REASON] Received negative value for edge weight" );;
                }
            }
            catch (...) {
                cout << "[ERROR] Error while adding an edge" << endl;
            }
        }
    }
}

// Setter that sets the weight of the appropriated edge
bool Graph::setWeight(int indexStart, int indexEnd, double weight, int weightMode) {

    if (!isIndexValid(indexStart)) {
        cout << "[ERROR] Index of starting vertice is not correct" << endl;
        return false;
    }
    if (!isIndexValid(indexEnd)) {
        cout << "[ERROR] Index of ending vertice is not correct" << endl;
        return false;
    }
    if (indexStart == indexEnd) {
        cout << "[ERROR] Starting and ending vertices are the same, cannot loop back on itself" << endl;
        return false;
    }

    if(weightMode==NEGATIVE_LOG) {
        if (weight <= 0) {
            cout << "[ERROR] Ratio cannot be negative or null" << endl;
            return false;
        }

        //We add the weight between both vertices to memorize the edge
        this->adjacencyMatrix[indexStart][indexEnd] = -(log(weight));
    }
    else if(weightMode==CLASSICAL_WEIGHT){
        //We add the weight between both vertices to memorize the edge
        this->adjacencyMatrix[indexStart][indexEnd] = weight;
    }

    return true;
}

//Setter that sets the ticker at the appropriated index
bool Graph::setTicker(int index, const string& ticker) {

    //If the index is valid
    if (isIndexValid(index)) {

        //We set the ticker's name
        this->associatedTickersList[index] = ticker;
        this->associatedTickersMap[ticker] = index;

        if (DISPLAY_EXECUTION) {
            //We print a message in the console
            cout << "[UPDATE] Ticker of index " << index << " set to " << this->associatedTickersList[index] << " !"
                 << endl;
        }

        //Successful, we return true
        return true;
    }
    else {
        cout << "[ERROR] Error initialising ticker's name !" << endl;
    }

    return false;
}

//Add a new ticker to the map and list of tickets
bool Graph::addTicker(const string& ticker){

    int index = (int) associatedTickersList.size();

    //We set the ticker's name
    this->associatedTickersList.emplace_back(ticker);
    this->associatedTickersMap[ticker] = index;

    return true;
}

//Function to print the connexions of the entire graph
void Graph::printGraph() {
    cout << endl << "--- Printing graph ---" << endl;
    for (int i = 0; i < adjacencyMatrix.size(); i++) {
        for (int j = 0; j < adjacencyMatrix[i].size(); j++) {
            if (adjacencyMatrix[i][j] != numeric_limits<double>::infinity()) {
                cout << "Vertice " << i << " goes to " << j << " for a weight of " << adjacencyMatrix[i][j] << "\n";
            }
        }
    }
}

//Getter that returns the number of vertices
int Graph::getNbVertices() const {
    return nbVertices;
}

// Getter that returns the adjacency matrix
vector<vector<double>> Graph::getAdjacencyMatrix() {
    return this->adjacencyMatrix;
}

//Function to check if an index is valid
bool Graph::isIndexValid(int index) const {
    if (index >= 0 && index < this->nbVertices)
        return true;
    return false;
}


//Converts the Negative Log weight to the original base10 weight
double Graph::convertNegativeLogToOriginal(double weight) {
    return exp(-weight);
}


//Bellman Ford Implementation to detect negative cycles
void Graph::bellmanFord(int sourceIndex) {

    if (isIndexValid(sourceIndex)) {

        //Initialisation
        vector<double> newEmptyVector;
        this->weightsFromSource = newEmptyVector;

        vector<int> newEmptyPreviousVertices;
        this->previousVertices = newEmptyPreviousVertices;

        for (int i = 0; i < this->nbVertices; i++) {
            this->weightsFromSource.push_back(numeric_limits<double>::infinity());
            this->previousVertices.push_back(-1);
        }

        this->weightsFromSource[sourceIndex] = 0;

        //We loop once for each vertice, called relaxation
        for (int i = 0; i < nbVertices; i++) {

            //For each edge (u,v)
            for (int source = 0; source < nbVertices; source++) {
                for (int destination = 0; destination < nbVertices; destination++) {

                    //If the edge exists
                    if (adjacencyMatrix[source][destination] != numeric_limits<double>::infinity()) {
                        //If distance[destination] > distance[u] + weigth (u,v) ==> We update the infos of the destination vertice
                        if (weightsFromSource[destination] > weightsFromSource[source] + adjacencyMatrix[source][destination]) {

                            //New total weight from source updated and previousVertice updated
                            weightsFromSource[destination] = weightsFromSource[source] + adjacencyMatrix[source][destination];
                            previousVertices[destination] = source;
                        }
                    }
                }
            }

        }
    }
    else {
        cout << endl << "[ERROR] Source index given to BellmanFord Algorithm not valid !" <<endl;
    }
}


//Detects if there is a negative cycle in the previous results of the Bellman Ford Algorithm
bool Graph::detectNegativeCycle() {

    //For each edge (u,v)
    for (int source = 0; source < nbVertices; source++) {
        for (int destination = 0; destination < nbVertices; destination++) {

            //If the edge exists
            if (adjacencyMatrix[source][destination] != 0) {
                //If distance[destination] > distance[u] + weigth (u,v) ==> There is a negative cycle
                if (weightsFromSource[destination] > weightsFromSource[source] + adjacencyMatrix[source][destination]) {
                    cout << "[CYCLE] We have an absorbent cycle !" << endl;
                    return true;
                }
            }

        }
    }

    //No negative cycle
    return false;
}

//Getter that returns the previous vertices vector
vector<int> Graph::getPreviousVertices() {
    return previousVertices;
}

//Getter that returns the weights from source vector
vector<double> Graph::getWeightsFromSource() {
    return weightsFromSource;
}


//Used to get the price in $ of an asset
double Graph::getTokenPriceFromIndex(int tokenIndex, int usdIndex) {
    if(!isIndexValid(tokenIndex) || !isIndexValid(usdIndex) && usdIndex!=tokenIndex){
        return -1;
    }
    return convertNegativeLogToOriginal(adjacencyMatrix[tokenIndex][usdIndex]);
}

//Used to get the price in $ of an asset from its ticker
double Graph::getTokenPriceFromTickers(const string& tokenTicker, const string& usdTicker) {

    int tokenIndex = getIndexFromTicker(tokenTicker);

    if(tokenIndex!=-1){

        int usdIndex = getIndexFromTicker(usdTicker);

        if(usdIndex!=-1){
            return getTokenPriceFromIndex(tokenIndex,usdIndex);
        }
    }

    //Error, token index not found
    return -1;
}

//Used to get the price in $ of an asset from its ticker only
double Graph::getTokenPriceFromTicker(const string& tokenTicker) {

    int tokenIndex = getIndexFromTicker(tokenTicker);
    int usdIndex = -1;

    if(tokenIndex!=-1){
        usdIndex = getIndexFromTicker("USDT");
        if(usdIndex==-1){
            usdIndex = getIndexFromTicker("USDC");
        }
        if(usdIndex==-1){
            usdIndex = getIndexFromTicker("BUSD");
        }
        if(usdIndex==-1){
            usdIndex = getIndexFromTicker("UST");
        }
        if(usdIndex!=-1){
            return getTokenPriceFromIndex(tokenIndex,usdIndex);
        }
    }
    //Error, token index not found
    return -1;
}

//Getter that returns the index of the associated ticker
int Graph::getIndexFromTicker(const string& ticker) {

    auto index = associatedTickersMap.find(ticker);
    if (index != associatedTickersMap.end()) {
        return index->second;
    }
    //Error return -1
    return -1;
}

string Graph::getTicker(int index) {
    if(isIndexValid(index)){
        return associatedTickersList[index];
    }
    return "ERROR";
}

Graph::~Graph() = default;

