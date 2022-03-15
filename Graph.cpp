//
// Created by Didier on 05/01/2022.
//
#include "httpGetFunctions.hpp"
#include "Graph.hpp"
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

//Constructor of the class
Graph::Graph() {
    nbVertices = 0;
    nbEdges = 0;
}

//Constructor of the class, takes a filename to load the graph from and a bool to return errors if so
Graph::Graph(const string &filename, bool *executionStatus) : Graph(){

    // Opening the file
    fstream fileDataGraph;
    fileDataGraph.open("./Graphs/" + filename, fstream::in);

    if (!fileDataGraph.is_open()) {
        cout << "[ERROR] Error Occurred while opening the file !" << endl;
        *executionStatus = false;
    }

    else {

        //We indicate to the main program that the execution is still good, for later purposes
        *executionStatus = true;

        int firstVertice, nextVertice; double weight;

        // We loop in order to read all the lines from to till the end of the file
        while (!fileDataGraph.eof()) {

            //We read the line from the file again
            fileDataGraph >> firstVertice >> nextVertice >> weight;

            addTicker(to_string(firstVertice));
            addTicker(to_string(nextVertice));

            // We add the edge in our adjacency matrix
            addWeightFromIndexes(firstVertice, nextVertice, weight);
        }
    }
}


int Graph::doesEdgeExistInAdjacencyList(int indexStart, int indexEnd){

    if(isIndexValid(indexStart) && isIndexValid(indexEnd)){

        int startingVerticeListSize = (int) adjacencyList[indexStart].size();

        for(int i=0;i<startingVerticeListSize;i++) {
            if (adjacencyList[indexStart][i].first == indexEnd){
                return i;
            }
        }

        //Need to create it
        return -2;
    }

    //Non-valid, add the vertices first
    return -1;
}

// Setter that adds the weight of the appropriated edge in the list
bool Graph::addWeightFromIndexes(int indexStart, int indexEnd, double weight) {

    int index = doesEdgeExistInAdjacencyList(indexStart,indexEnd);

    //Error
    if(index == -1) {
        return false;
    }

    //Need to create it
    if(index == -2 && weight > 0) {
        pair<int,double> newEdge;
        newEdge.first = indexEnd;
        newEdge.second = -(log(weight));
        this->adjacencyList[indexStart].push_back(newEdge);
        nbEdges++;
        return true;
    }

    return  setWeightFromIndexes(indexStart, indexEnd, weight);
}

// Setter that sets the weight of the appropriated edge
bool Graph::setWeightFromIndexes(int indexStart, int indexEnd, double weight) {

    int index = doesEdgeExistInAdjacencyList(indexStart,indexEnd);
    if(index>=0){
        this->adjacencyList[indexStart][index].second = -(log(weight));
        return true;
    }

    return false;
}

//Setter that sets the weight of the appropriated edge using string tickers
bool Graph::setWeightFromTickers(const string& tickerStart, const string& tickerEnd, double ratio) {

    if(tickerEnd==tickerStart || ratio <= 0){
        cout << "[ERROR] Starting and ending vertices are the same || ratio = 0" << endl;
        return false;
    }

    //We get both index using their tickers
    int indexStart = getIndex(tickerStart);
    int indexEnd = getIndex(tickerEnd);

    //If they are not valid, return false
    if(indexStart==-1 || indexEnd==-1){
        cout << "[ERROR] Index of starting/ending vertice is not correct, tickerStart = "<<tickerStart<<" and tickerEnd = "<<tickerEnd << endl;
        return false;
    }

    setWeightFromIndexes(indexStart,indexEnd,ratio);

    return true;
}

//Getter that returns the ticker of the appropriated index
string Graph::getTicker(int index) {
    if(isIndexValid(index)){
        return associatedTickersList[index];
    }
    return "ERROR";
}

//Setter that sets the ticker at the appropriated index
bool Graph::setTicker(int index, const string& ticker) {

    //If the index is valid
    if (isIndexValid(index)) {

        //We set the ticker's name
        this->associatedTickersList[index] = ticker;
        this->associatedTickersMap[ticker] = index;

        //Successful, we return true
        return true;
    }

    cout << "[ERROR] Error initialising ticker's name !" << endl;

    return false;
}

//Add a new ticker to the map and list of tickets
bool Graph::addTicker(const string& ticker){

    //We get the index of the token ticker
    int exist = getIndex(ticker);

    //We verify if the token ticker exists
    if(exist == -1){

        //We get the next index
        int index = (int) associatedTickersList.size();

        //We add the ticker's name at the end of the list
        this->associatedTickersList.push_back(ticker);

        //We also add the index in the dictionary
        this->associatedTickersMap[ticker] = index;

        vector<pair<int,double>> listOfEdgesStartingFromThisVertice;

        adjacencyList.push_back(listOfEdgesStartingFromThisVertice);

        //We increase the attribute number of Vertices
        nbVertices++;

        return true;
    }

    return false;
}

//Getter that returns the number of vertices
int Graph::getNbVertices() const {
    return nbVertices;
}

// Getter that returns the adjacency matrix
vector<vector<pair<int,double>>> Graph::getAdjacencyList() const {
    return this->adjacencyList;
}

//Getter that returns the previous vertices vector
vector<int> Graph::getPreviousVertices() const {
    return previousVertices;
}

//Getter that returns the weights from source vector
vector<double> Graph::getWeightsFromSource() const {
    return weightsFromSource;
}

//Function to check if an index is valid
bool Graph::isIndexValid(int index) const {
    if (index >= 0 && index < this->nbVertices) {
        return true;
    }
    return false;
}

//Converts the Negative Log weight to the original base10 weight
double Graph::convertNegativeLogToOriginal(double weight) {
    return exp(-weight);
}

//Getter that returns the index of the associated ticker
int Graph::getIndex(const string& ticker) {

    //We use the method find to check if the ticker exists and to get its index
    auto index = associatedTickersMap.find(ticker);
    if (index != associatedTickersMap.end()) {
        //It exists, returns its index
        return index->second;
    }
    //Error return -1
    return -1;
}

//Used to get the price in $ of an asset
double Graph::getTokenPriceFromIndex(int tokenIndex, int baseIndex) {
    if(!isIndexValid(tokenIndex) || !isIndexValid(baseIndex) && baseIndex!=tokenIndex){
        return -1;
    }

    int index = doesEdgeExistInAdjacencyList(tokenIndex,baseIndex);
    if(index!=-1) {
        return convertNegativeLogToOriginal(adjacencyList[tokenIndex][index].second);
    }
    return -1;
}

//Used to get the price in $ of an asset from its ticker only
double Graph::getTokenPriceFromTicker(const string& tokenTicker) {

    //We get the index of the token ticker
    int tokenIndex = getIndex(tokenTicker);
    int usdIndex = -1;

    //We verify if the token ticker exists
    if(tokenIndex!=-1){

        //We try to get the index of one of the usd cryptocurrencies
        usdIndex = getIndex("USDT");
        if(usdIndex==-1){
            usdIndex = getIndex("USDC");
        }

        //If we found one, we try to get its price
        if(usdIndex!=-1){
            return getTokenPriceFromIndex(tokenIndex,usdIndex);
        }
    }
    //Error, token index not found
    return -1;
}

//Used to get the price relative to the reference ticker of an asset from its ticker
double Graph::getTokenPriceFromTickers(const string& tokenTicker, const string& referenceTicker) {

    //We get the index of the token currency
    int tokenIndex = getIndex(tokenTicker);

    //We verify if the token ticker exists
    if(tokenIndex!=-1){

        //We get the index of the usd currency
        int usdIndex = getIndex(referenceTicker);

        //If we found it, we use the marvellous function to get price from indexes
        if(usdIndex!=-1){
            return getTokenPriceFromIndex(tokenIndex,usdIndex);
        }
    }

    //Error, token index not found
    return -1;
}

//Bellman Ford Implementation to detect negative cycles
void Graph::bellmanFord(int sourceIndex) {

    if (isIndexValid(sourceIndex)) {

        //Initialisation, two empty vertices
        vector<double> newEmptyVector;
        this->weightsFromSource = newEmptyVector;

        vector<int> newEmptyPreviousVertices;
        this->previousVertices = newEmptyPreviousVertices;

        for (int i = 0; i < this->nbVertices; i++) {
            this->weightsFromSource.push_back(numeric_limits<double>::infinity());
            this->previousVertices.push_back(-1);
        }

        //We set the weight to go to the source to 0 (for the source)
        this->weightsFromSource[sourceIndex] = 0;
        this->previousVertices[sourceIndex] = 0;

        //We loop once for each vertice, called relaxation
        for(int i=0;i<nbVertices;i++) {

            //We check for each vertex
            for (int source = 0; source < nbVertices; source++) {
                for (int destination = 0; destination < adjacencyList[source].size(); destination++) {

                    int indexDestination = adjacencyList[source][destination].first;

                    //If distance[destination] > distance[u] + weight (u,v) ==> We update the infos of the destination vertice
                    if (weightsFromSource[indexDestination] > weightsFromSource[source] + adjacencyList[source][destination].second) {

                        //New total weight from source updated and previousVertice updated
                        weightsFromSource[indexDestination] = weightsFromSource[source] + adjacencyList[source][destination].second;
                        previousVertices[indexDestination] = source;
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

    //We check for each vertex
    for (int source = 0; source < nbVertices; source++) {
        for (int destination = 0; destination < adjacencyList[source].size(); destination++) {

            int indexDestination = adjacencyList[source][destination].first;

            //If distance[destination] > distance[u] + weight (u,v) ==> We update the infos of the destination vertice
            if (weightsFromSource[indexDestination] > weightsFromSource[source] + adjacencyList[source][destination].second) {

                //cout << "[CYCLE] We have an absorbent cycle !" << endl;
                //cout<<"Cycle : "<<getTicker(source)<<"->"<<getTicker(destination)<<endl;
            }
        }
    }

    //No negative cycle
    return false;
}

//Fill the tickers list and map using kucoin's data fetched
bool Graph::fillTickersWithKucoin(const json& j_filler) {

    //We go through all the symbols
    for (auto & i : j_filler) {

        //We get the pair
        string pairTicker = i.value("symbol", "Error");

        //We split it in order to get both tokens
        string baseToken = pairTicker.substr(0, pairTicker.find('-'));
        string quoteToken = pairTicker.substr(pairTicker.find('-') + 1, pairTicker.size());

        //We check if the trading is enabled
        bool tradingEnabled = i.value("enableTrading", false);

        //If trading is enabled, we check if the token can be traded against stable coins or BTC
        if(tradingEnabled) {
            if (quoteToken == "USDT" || quoteToken == "USDC" || quoteToken == "UST" || quoteToken == "BTC") {
                if (baseToken.size() < 5 && quoteToken.size() < 5) {
                    this->addTicker(baseToken);
                    this->addTicker(quoteToken);
                    this->addWeightFromIndexes(getIndex(baseToken),getIndex(quoteToken),numeric_limits<double>::infinity());
                    this->addWeightFromIndexes(getIndex(quoteToken),getIndex(baseToken),numeric_limits<double>::infinity());
                }
            }
        }
    }

    //This one is missing from the tickers list
    this->addTicker("NANO");
    this->addTicker("HPB");

    return true;
}

bool Graph::updateMatrixWithKucoin() {

    //Link to the api that provides the data
    auto ApiLink = "https://api.kucoin.com/api/v1/market/allTickers";

    auto Json_tickersData = getApiData(ApiLink)["data"]["ticker"];

    for(auto & ticker : Json_tickersData) {

        string pairTicker = ticker.value("symbol", "Error");

        string baseToken = pairTicker.substr(0, pairTicker.find('-'));
        string quoteToken = pairTicker.substr(pairTicker.find('-') + 1, pairTicker.size());

        double sellPrice = stod(ticker.value("sell", "Error"));
        double buyPrice = stod(ticker.value("buy", "Error"));

        if (quoteToken == "USDT" || quoteToken == "USDC" || quoteToken == "UST" || quoteToken == "BTC") {
            if (baseToken.size() < 5 && quoteToken.size() < 5 && sellPrice != 0 && buyPrice != 0) {
                this->setWeightFromTickers(quoteToken, baseToken, sellPrice);
                this->setWeightFromTickers(baseToken, quoteToken, buyPrice);
            }
        }
    }

    return true;
}