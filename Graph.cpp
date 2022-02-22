//
// Created by Didier on 05/01/2022.
//

#include "Graph.hpp"
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

//Constructor of the class, takes a filename to load the graph from and a bool to return errors if so
Graph::Graph(const string &filename, bool *errorOccurred) {

    //Setting private variables to default values
    this->nbVertices=0;
    this->nbEdges=0;

    // Opening the file
    fstream fileDataGraph;
    fileDataGraph.open("./graphes/"+filename,fstream::in);

    if(!fileDataGraph.is_open()){
        cout<<"\n[ERROR] Error Occurred while opening the file !"<<endl;
        *errorOccurred = false;
    }
    else{

        //We indicate to the main program that the execution is still good, for later purposes
        *errorOccurred=true;

        //Telling the user that everything works
        cout << "[LOADING] Opened the file successfully"<<endl;

        // Filling our vertices and edges variables
        fileDataGraph>>nbVertices>>nbEdges;

        // Instantiating the vectors for the adjacency matrix
        for( int i=0; i<nbVertices;i++) {
            vector<double> fillVectorWithEmptyValues;
            adjacencyMatrix.push_back(fillVectorWithEmptyValues);

            for( int j=0; j<nbVertices;j++) {
                adjacencyMatrix[i].push_back(0.0);
            }

            //Instantiating the ticker's vector
            this->associatedTickers.emplace_back("");
        }

        //Telling the user more informations that he knows
        cout << "[LOADING] All class vectors successfully initialised ..."<<endl;

        int firstVertice,nextVertice;
        double weight;

        //Telling the user more informations that he knows
        cout << "[LOADING] Loading graph with "<<nbVertices<<" vertices and "<<nbEdges<<" edges ..."<<endl;

        //We read the file
        fileDataGraph>>firstVertice>>nextVertice>>weight;

        // We loop in order to read all the lines from to till the end of the file
        while(!fileDataGraph.eof()){

            try {
                // We add the edge in our adjacency matrix
                bool success = addEdge(firstVertice, nextVertice, -(log(weight)));

                if (!success){
                    throw 44;
                }
                else{
                    //We print a message in the console
                    cout<<"[INSERTION] Insertion of an edge from vertice "<<firstVertice<<" to vertice "<< nextVertice<<" with a weight of "<< -(log(weight))<<" !"<<endl;

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

// Function that adds the edge from one vertice to another in the adjacency matrix
bool Graph::addEdge(int first_vertice, int next_vertice, double weight) {

    //If the first is not the next one and the vertices index are valid
    if(first_vertice!=next_vertice && first_vertice<nbVertices && next_vertice<nbVertices && first_vertice>=0 && next_vertice>=0) {

        //We add the weight between both vertices to memorize the edge
        adjacencyMatrix[first_vertice][next_vertice] = weight;

        //Successful, we return true
        return true;
    }

    //An error occurred, conditions were not valid, return false for the program to handle this
    return false;
}

//Setter that sets the ticker at the appropriated index
bool Graph::setTicker(int index, string ticker) {

    //If the index is valid
    if(index>=0 && index < getNbVertices()){

        //We set the ticker's name
        this->associatedTickers[index] = move(ticker);

        //We print a message in the console
        cout<<"[UPDATE] Ticker of index "<<index<<" set to "<< this->associatedTickers[index]<<" !"<<endl;

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
    return adjacencyMatrix;
}

Graph::~Graph() = default;

