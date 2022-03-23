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
    sourceIndex = 0;
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
            addEdgeToAdjacencyList(firstVertice, nextVertice, weight);
        }
    }
}

//Checks if the edge between start and end vertice exists in the adjacencyList, returns its index if so, otherwise a negative value indicating the status
int Graph::doesEdgeExistInAdjacencyList(int indexStart, int indexEnd){

    if(isCombinationOfVerticesValid(indexStart,indexEnd)){

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

// Setter that adds the edge to the adjacencyList, or  sets the weight to the associated edge
bool Graph::addEdgeToAdjacencyList(int indexStart, int indexEnd, double weight) {

    int index = doesEdgeExistInAdjacencyList(indexStart,indexEnd);

    //Error, one or both indexes are not valid
    if(index == -1) {
        return false;
    }

    //We are good, pair needs to be created, so we instantiate it
    if(index == -2 && weight > 0) {

        //Creating the new pair
        pair<int,double> newEdge;

        //Setting up its values
        newEdge.first = indexEnd;
        newEdge.second = -(log(weight)); //LN here

        //Adding it to the adjacencyList
        this->adjacencyList[indexStart].push_back(newEdge);

        //Increasing by 1 the number of edges in the graph
        nbEdges++;

        return true;
    }

    //Pair is already created, we set the weight
    return  setWeightFromIndexes(indexStart, indexEnd, weight);
}

// Setter that sets the weight of the appropriated edge
bool Graph::setWeightFromIndexes(int indexStart, int indexEnd, double weight) {

    //We get the destination index in the adjacencyList of the starting vertice
    int index = doesEdgeExistInAdjacencyList(indexStart,indexEnd);

    //If both are valid
    if(isCombinationOfVerticesValid(indexStart,index)){
        //We set the proper weight to its new value and then return true
        this->adjacencyList[indexStart][index].second = -(log(weight));
        return true;
    }

    //Indexes are not valid, we return false
    return false;
}

//Setter that sets the weight of the appropriated edge using string tickers
bool Graph::setWeightFromTickers(const string& tickerStart, const string& tickerEnd, double ratio) {

    if(ratio <= 0){
        cout << "[ERROR] Ratio = 0" << endl;
        return false;
    }

    //We get both index using their tickers
    int indexStart = getIndex(tickerStart);
    int indexEnd = getIndex(tickerEnd);

    //If they are not valid, return false
    if(!isCombinationOfVerticesValid(indexStart,indexEnd)){
        //cout << "[ERROR] Index of starting/ending vertice is not correct, tickerStart = "<<tickerStart<<" and tickerEnd = "<<tickerEnd << endl;
        return false;
    }

    return setWeightFromIndexes(indexStart,indexEnd,ratio);
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
    int tickerIndex = getIndex(ticker);

    //We verify if the token ticker doesn't exist
    if(tickerIndex == -1){

        //We get the next index
        int nextIndex = (int) associatedTickersList.size();

        //We add the ticker's name at the end of the list
        associatedTickersList.push_back(ticker);

        //We also add the index in the dictionary
        associatedTickersMap[ticker] = nextIndex;

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

    int index = doesEdgeExistInAdjacencyList(tokenIndex,baseIndex);

    if(isCombinationOfVerticesValid(tokenIndex,index)) {
        return convertNegativeLogToOriginal(adjacencyList[tokenIndex][index].second);
    }

    return -1;
}

//Used to get the price in $ of an asset from its ticker only
double Graph::getTokenPriceFromTicker(const string& tokenTicker) {

    //We get the index of the token ticker
    int tokenIndex = getIndex(tokenTicker);

    //We try to get the index of one of the usd cryptocurrencies
    int usdIndex = getIndex("USDT");

    if(usdIndex==-1){
        usdIndex = getIndex("USDC");
    }

    return getTokenPriceFromIndex(tokenIndex,usdIndex);
}

//Used to get the price relative to the reference ticker of an asset from its ticker
double Graph::getTokenPriceFromTickers(const string& tokenTicker, const string& referenceTicker) {

    //We get the index of the token currency
    int tokenIndex = getIndex(tokenTicker);

    //We get the index of the usd currency
    int usdIndex = getIndex(referenceTicker);


    return getTokenPriceFromIndex(tokenIndex,usdIndex);
}

//Bellman Ford Implementation to detect negative cycles
void Graph::bellmanFord(int chosenSourceIndex) {

    this->sourceIndex = chosenSourceIndex;

    if (isIndexValid(chosenSourceIndex)) {

        //Initialisation, two empty vertices
        vector<double> newEmptyVector;
        this->weightsFromSource = newEmptyVector;

        vector<int> newEmptyPreviousVertices;
        this->previousVertices = newEmptyPreviousVertices;

        for (int i = 0; i < this->nbVertices; i++) {
            this->weightsFromSource.push_back(1000000000);
            this->previousVertices.push_back(-1);
        }

        //We set the weight to go to the source to 0 (for the source)
        this->weightsFromSource[chosenSourceIndex] = 0;
        this->previousVertices[chosenSourceIndex] = 0;

        //We loop once for each vertice, called relaxation
        for(int i=0;i<nbVertices;i++) {

            //We check for each vertex
            for (int source = 0; source < nbVertices; source++) {
                for (int destination = 0; destination < adjacencyList[source].size(); destination++) {

                    int indexDestination = adjacencyList[source][destination].first;

                    //If distance[destination] > distance[u] + weight (u,v) ==> We update the infos of the destination vertice
                    if (weightsFromSource[indexDestination] > weightsFromSource[source] + adjacencyList[source][destination].second) {

                        if(adjacencyList[source][destination].second != numeric_limits<double>::infinity() || adjacencyList[source][destination].second != -numeric_limits<double>::infinity()){

                            //New total weight from source updated and previousVertice updated
                            weightsFromSource[indexDestination] = weightsFromSource[source] + adjacencyList[source][destination].second;
                            previousVertices[indexDestination] = source;
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

bool Graph::isCombinationOfVerticesValid(int indexStart, int indexEnd) const {

    if(isIndexValid(indexStart) && isIndexValid(indexEnd)){
        return true;
    }

    return false;
}

//Detects if there is a negative cycle in the previous results of the Bellman Ford Algorithm
bool Graph::detectNegativeCycle() {

    //We check for each vertex
    for (int source = 0; source < nbVertices; source++) {
        for (int destination = 0; destination < adjacencyList[source].size(); destination++) {

            int indexDestination = adjacencyList[source][destination].first;

            //If distance[destination] > distance[u] + weight (u,v) ==> We update the infos of the destination vertice
            if (weightsFromSource[indexDestination] > weightsFromSource[source] + adjacencyList[source][destination].second) {
                return true;
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
                    this->addEdgeToAdjacencyList(getIndex(baseToken),getIndex(quoteToken),numeric_limits<double>::infinity());
                    this->addEdgeToAdjacencyList(getIndex(quoteToken),getIndex(baseToken),numeric_limits<double>::infinity());
                }
            }
        }
    }

    //This one is missing from the tickers list
    this->addTicker("NANO");
    this->addTicker("HPB");

    return true;
}

bool Graph::updateAdjacencyListWithKucoin() {

    //Link to the api that provides the data
    auto ApiLink = "https://api.kucoin.com/api/v1/market/allTickers";

    auto Json_tickersData = getApiData(ApiLink)["data"]["ticker"];

    for(auto & ticker : Json_tickersData) {

        string pairTicker = ticker.value("symbol", "Error");

        string baseToken = pairTicker.substr(0, pairTicker.find('-'));
        string quoteToken = pairTicker.substr(pairTicker.find('-') + 1, pairTicker.size());

        double buyPrice = 1.0/(stod(ticker.value("sell", "Error")));
        double sellPrice = stod(ticker.value("buy", "Error"));

        if (quoteToken == "USDT" || quoteToken == "USDC" || quoteToken == "UST" || quoteToken == "BTC") {
            if (baseToken.size() < 5 && quoteToken.size() < 5 && sellPrice != 0.0 && buyPrice != 0.0) {
                this->setWeightFromTickers(quoteToken, baseToken, buyPrice);
                this->setWeightFromTickers(baseToken, quoteToken, sellPrice);
            }
        }
    }

    return true;
}

//Fill the tickers list and map using kucoin's data fetched
bool Graph::fillTickersWithCexIO(const json& j_filler) {

    //We go through all the symbols
    for (auto & i : j_filler) {

        //We split it in order to get both tokens
        string baseToken = i.value("symbol1", "Error");
        string quoteToken = i.value("symbol2", "Error");

        //We check if the token can be traded against stable coins or BTC
        if (quoteToken == "USDT" || quoteToken == "USD" || quoteToken == "BTC"){
            if( baseToken != "EXFI") {
                if (baseToken.size() < 5 && quoteToken.size() < 5) {
                    this->addTicker(baseToken);
                    this->addTicker(quoteToken);
                    this->addEdgeToAdjacencyList(getIndex(baseToken), getIndex(quoteToken),numeric_limits<double>::infinity());
                    this->addEdgeToAdjacencyList(getIndex(quoteToken), getIndex(baseToken),numeric_limits<double>::infinity());
                }
            }
        }
    }

    return true;
}

bool Graph::updateAdjacencyListWithCexIO() {

    //Link to the api that provides the data
    auto ApiLink = "https://cex.io/api/tickers/USDT/USD/BTC";

    auto Json_tickersData = getApiData(ApiLink)["data"];

    for(auto & ticker : Json_tickersData) {

        string pairTicker = ticker.value("pair", "Error");

        string baseToken = pairTicker.substr(0, pairTicker.find(':'));
        string quoteToken = pairTicker.substr(pairTicker.find(':') + 1, pairTicker.size());

        double sellPrice = ticker.value("bid", 0.0);
        double buyPrice = 1.0/ticker.value("ask", 10000000000000000000000.0);

        if (quoteToken == "USDT" || quoteToken == "USD" || quoteToken == "BTC") {
            if (baseToken.size() < 5 && quoteToken.size() < 5 && sellPrice > 0.0 && buyPrice > 0.0) {
                this->setWeightFromTickers(quoteToken, baseToken, buyPrice); //"USDT"->"BCH" = 1.0/371.46
                this->setWeightFromTickers(baseToken, quoteToken, sellPrice); //"BCH"->"USDT" = 371.18
            }
        }
    }

    return true;
}

//Find and returns the best route to arbitrage in the graph
double Graph::findAndReturnWeightOfBestRoute() {

    //We reset bestRoute
    bestRoute = vector<int>();

    bestRoute.push_back(sourceIndex);

    int nextIndex = sourceIndex;
    int previousIndex = previousVertices[sourceIndex];

    int numberOfIterations = 0;
    double weight = 0.0;

    do{
        //We add the weight of the edge to the variable that 'll be returned
        int nextIndexInAdjacencyList = doesEdgeExistInAdjacencyList(previousIndex,nextIndex);

        weight += adjacencyList[previousIndex][nextIndexInAdjacencyList].second;

        //We add the previousIndex to the bestRoute
        bestRoute.push_back(previousIndex);

        //We go further in the graph, getting the previous vertice
        nextIndex = previousIndex;

        //We get the previous vertice in the best route
        previousIndex = previousVertices[nextIndex];

        numberOfIterations++;
    }
    while(numberOfIterations<=5 && nextIndex!=sourceIndex);

    reverse(bestRoute.begin(), bestRoute.end());

    if(nextIndex==sourceIndex) {
        return weight;
    }
    return -1;
}

//Getter that returns the best route after it has been calculated
vector<int> Graph::getBestRoute() {
    return bestRoute;
}

double Graph::displayRouteAndPercentage(double weight) {
    double percentage = (Graph::convertNegativeLogToOriginal(weight)-1)*100;

    if(detectNegativeCycle() || convertNegativeLogToOriginal(weight)>1){
        int size = (int) bestRoute.size();

        cout<<endl<<"New negative cycle : ";

        for(int i = 0; i<size;i++){
            if(i<size-1) {
                cout<<getTicker(bestRoute[i])<<"->";
            }
            else{
                cout<<getTicker(bestRoute[i])<<endl;
            }
        }

        cout << "Weight of the cycle is "<<weight<<" and is a coefficient of "<<percentage<<"%"<<endl;
    }

    return percentage;
}


