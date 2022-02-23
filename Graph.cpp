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
Graph::Graph(const string &filename, bool *executionStatus) {

    //Setting private variables to default values
    this->nbVertices=0;
    this->nbEdges=0;

    // Opening the file
    fstream fileDataGraph;
    fileDataGraph.open("./graphes/"+filename,fstream::in);

    if(!fileDataGraph.is_open()){
        cout<<"[ERROR] Error Occurred while opening the file !"<<endl;
        *executionStatus = false;
    }
    else{

        //We indicate to the main program that the execution is still good, for later purposes
        *executionStatus=true;

        if(DISPLAY_EXECUTION) {
            //Telling the user that everything works
            cout << "[LOADING] Opened the file successfully" << endl;
        }

        // Filling our vertices and edges variables
        fileDataGraph>>nbVertices>>nbEdges;

        // Instantiating the vectors for the adjacency matrix
        for( int i=0; i<nbVertices;i++) {
            vector<double> fillVectorWithEmptyValues;
            this->adjacencyMatrix.push_back(fillVectorWithEmptyValues);

            for( int j=0; j<nbVertices;j++) {
                this->adjacencyMatrix[i].push_back(0.0);
            }

            //Instantiating the ticker's vector
            this->associatedTickers.emplace_back("");
        }

        int firstVertice,nextVertice;
        double weight;

        if(DISPLAY_EXECUTION) {
            //Telling the user more infos that he knows
            cout << "[LOADING] All class vectors successfully initialised ..."<<endl;

            //Telling the user more infos that he knows
            cout << "[LOADING] Loading graph with " << nbVertices << " vertices and " << nbEdges << " edges ..."
                 << endl;
        }

        //We read the file
        fileDataGraph>>firstVertice>>nextVertice>>weight;

        // We loop in order to read all the lines from to till the end of the file
        while(!fileDataGraph.eof()){

            try {
                // We add the edge in our adjacency matrix
                bool success = setWeight(firstVertice, nextVertice, -(log(weight)));

                if (!success){
                    throw 44;
                }
                else{

                    if(DISPLAY_EXECUTION) {
                        //We print a message in the console
                        cout << "[INSERTION] Insertion of an edge from vertice " << firstVertice << " to vertice "<< nextVertice << " with a weight of " << -(log(weight)) << " !" << endl;
                    }
                    //We read the line from the file again
                    fileDataGraph>>firstVertice>>nextVertice>>weight;
                }
            }
            catch (int e){
                cout<<"[Error] Error while adding an edge"<<endl;
            }
        }
    }
}

// Setter that sets the weight of the appropriated edge
bool Graph::setWeight(int indexStart, int indexEnd, double weight) {
    if(weight == 0)
    {
        cout << "[ERROR] Ratio cannot be 0"<< endl;
        return false;
    }
    if(!isIndexValid(indexStart)) {
        cout << "[ERROR] Index of starting vertice is not correct"<< endl;
        return false;
    }
    if (!isIndexValid(indexEnd)) {
        cout << "[ERROR] Index of ending vertice is not correct"<< endl;
        return false;
    }
    if(indexStart==indexEnd){
        cout << "[ERROR] Starting and ending vertices are the same, cannot loop back on itself"<< endl;
        return false;
    }

    //We add the weight between both vertices to memorize the edge
    this->adjacencyMatrix[indexStart][indexEnd] = weight;
    return true;
}

//Setter that sets the ticker at the appropriated index
bool Graph::setTicker(int index, string ticker) {

    //If the index is valid
    if(isIndexValid(index)){

        //We set the ticker's name
        this->associatedTickers[index] = move(ticker);

        if(DISPLAY_EXECUTION) {
            //We print a message in the console
            cout << "[UPDATE] Ticker of index " << index << " set to " << this->associatedTickers[index] << " !"<< endl;
        }

        //Successful, we return true
        return true;
    }
    else{
        cout<<"[ERROR] Error initialising ticker's name !"<<endl;
    }

    return false;
}

//Function to print the connexions of the entire graph
void Graph::printGraph() {
    cout<<endl<<"--- Printing graph ---"<<endl;
    for(int i=0; i<adjacencyMatrix.size();i++){
        for(int j=0;j<adjacencyMatrix[i].size();j++){
            if(adjacencyMatrix[i][j]!=0) {
                cout << "Vertice " << i << " goes to " << j << " for a weight of "<< adjacencyMatrix[i][j] << "\n";
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
    if(index>=0 && index<this->nbVertices)
        return true;
    return false;
}


//Bellman Ford Implementation to detect negative cycles
void Graph::bellmanFord(int sourceIndex) {

    if(isIndexValid(sourceIndex)){

        //Initialisation
        vector<double> newEmptyVector;
        this->weightsFromSource = newEmptyVector;

        vector<vector<int>> newEmptyPreviousVertices;
        this->previousVertices = newEmptyPreviousVertices;

        for(int i=0; i<this->nbVertices;i++){
            this->weightsFromSource.push_back(numeric_limits<double>::infinity());
        }

        this->weightsFromSource[sourceIndex] = 0;

    }
    else{

    }
}




Graph::~Graph() = default;

