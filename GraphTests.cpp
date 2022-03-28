//
// Created by Didier on 22/02/2022.
//

#include "Graph.hpp"
#include "GraphTests.hpp"

//Starts all tests and return true if the execution is successful
bool startAllGraphTests(){
    bool successStatus;

    cout<<endl<<"[TEST] Beginning of the graph tests"<<endl<<endl;
    cout<<"---Testing graph constructor---"<<endl;
    successStatus = testGraphConstructor();
    if(!successStatus) {
        cout<<"Graph constructor tests failed, please check what's wrong"<<endl;
        cout<<endl<<"[TEST] Some tests failed, please check !"<<endl;
        return false;
    }
    else{
        cout<<"---Graph constructor tests successful---"<<endl;
    }


    cout<<endl<<"---Testing setWeightFromTickers function---"<<endl;
    successStatus = testSetWeightFromTickers();
    if(!successStatus) {
        cout<<"SetWeightFromTickers function tests failed, please check what's wrong"<<endl;
        cout<<endl<<"[TEST] Some tests failed, please check !"<<endl;
        return false;
    }
    else{
        cout<<"---SetWeightFromTickers function tests successful---"<<endl;
    }


    cout<<endl<<"---Testing getTicker function---"<<endl;
    successStatus = testGetTicker();
    if(!successStatus) {
        cout<<"GetTicker function tests failed, please check what's wrong"<<endl;
        cout<<endl<<"[TEST] Some tests failed, please check !"<<endl;
        return false;
    }
    else{
        cout<<"---GetTicker function tests successful---"<<endl;
    }


    cout<<endl<<"---Testing setTicker setter---"<<endl;
    successStatus = testSetTicker();
    if(!successStatus) {
        cout<<"setTicker setter tests failed, please check what's wrong"<<endl;
        cout<<endl<<"[TEST] Some tests failed, please check !"<<endl;
        return false;
    }
    else{
        cout<<"---SetTicker setter tests successful---"<<endl;
    }


    cout<<endl<<"---Testing addTicker setter---"<<endl;
    successStatus = testAddTicker();
    if(!successStatus) {
        cout<<"AddTicker setter tests failed, please check what's wrong"<<endl;
        cout<<endl<<"[TEST] Some tests failed, please check !"<<endl;
        return false;
    }
    else{
        cout<<"---AddTicker setter tests successful---"<<endl;
    }


    cout<<endl<<"---Testing isIndexValid setter---"<<endl;
    successStatus = testIsIndexValid();
    if(!successStatus) {
        cout<<"IsIndexValid setter tests failed, please check what's wrong"<<endl;
        cout<<endl<<"[TEST] Some tests failed, please check !"<<endl;
        return false;
    }
    else{
        cout<<"---IsIndexValid setter tests successful---"<<endl;
    }


    cout<<endl<<"---Testing ConvertNegativeToLogOriginal setter---"<<endl;
    successStatus = testConvertNegativeToLogOriginal();
    if(!successStatus) {
        cout<<"ConvertNegativeToLogOriginal setter tests failed, please check what's wrong"<<endl;
        cout<<endl<<"[TEST] Some tests failed, please check !"<<endl;
        return false;
    }
    else{
        cout<<"---ConvertNegativeToLogOriginal setter tests successful---"<<endl;
    }


    cout<<endl<<"---Testing getIndex getter---"<<endl;
    successStatus = testGetIndex();
    if(!successStatus) {
        cout<<"GetIndex setter tests failed, please check what's wrong"<<endl;
        cout<<endl<<"[TEST] Some tests failed, please check !"<<endl;
        return false;
    }
    else{
        cout<<"---GetIndex setter tests successful---"<<endl;
    }


    cout<<endl<<"---Testing GetTokenPriceFromIndex getter---"<<endl;
    successStatus = testGetTokenPriceFromIndex();
    if(!successStatus) {
        cout<<"GetTokenPriceFromIndex setter tests failed, please check what's wrong"<<endl;
        cout<<endl<<"[TEST] Some tests failed, please check !"<<endl;
        return false;
    }
    else{
        cout<<"---GetTokenPriceFromIndex setter tests successful---"<<endl;
    }


    cout<<endl<<"---Testing getTokenPriceFromTicker getter---"<<endl;
    successStatus = testGetTokenPriceFromTicker();
    if(!successStatus) {
        cout<<"GetTokenPriceFromTicker getter tests failed, please check what's wrong"<<endl;
        cout<<endl<<"[TEST] Some tests failed, please check !"<<endl;
        return false;
    }
    else{
        cout<<"---GetTokenPriceFromTicker getter tests successful---"<<endl;
    }


    cout<<endl<<"---Testing getTokenPriceFromTickers getter---"<<endl;
    successStatus = testGetTokenPriceFromTickers();
    if(!successStatus) {
        cout<<"GetTokenPriceFromTickers getter tests failed, please check what's wrong"<<endl;
        cout<<endl<<"[TEST] Some tests failed, please check !"<<endl;
        return false;
    }
    else{
        cout<<"---GetTokenPriceFromTickers getter tests successful---"<<endl;
    }


    cout<<endl<<"[TEST] Graphs tests passed successfully, well done master !"<<endl;
    return true;
}


//Tests all different cases for the constructor of the class Graph
bool testGraphConstructor(){
    bool executionStatus;

    //Creating a graph from the file 3cryptos, should return true
    Graph newGraph =  Graph("arbitrage3Cryptos.txt",&executionStatus);

    if(executionStatus){
        cout<<"[TEST] Instantiating test with 3 cryptos | VALID "<<endl;
    }
    else{
        cout<<"[TEST] Instantiating test with 3 cryptos | FAILED "<<endl;
        return false;
    }

    //Trying to create a graph from a non-existing file, should fail to be a valid test
    Graph testGraph("bob.txt", &executionStatus);

    if(!executionStatus){
        cout<<"[TEST] Instantiating test with a wrong filename, should get an error message | VALID "<<endl;
    }
    else{
        cout<<"[TEST] Instantiating test with a wrong filename, should get an error message | FAILED "<<endl;
        return false;
    }

    return true;
}

//Tests all different cases for the method testSetWeightFromTickers of the class Graph
bool testSetWeightFromTickers(){
    bool executionStatus;

    //Creates an empty graph with 3 vertices and 0 edges
    Graph newGraph =  Graph();

    executionStatus = newGraph.addTicker("USDT");
    executionStatus = newGraph.addTicker("BTC");
    executionStatus = newGraph.addTicker("ETH");

    newGraph.addEdgeToAdjacencyList(0,1,1);
    newGraph.addEdgeToAdjacencyList(0,2,60);

    //Adding an edge to the graph, should be a success
    executionStatus = newGraph.setWeightFromTickers("USDT","BTC",60);

    if(executionStatus){

        //We check here after the execution successfully changed the ratio
        if(newGraph.getAdjacencyList()[0][0].second==(-log(60))){
            cout<<"[TEST] Adding a valid edge to the graph, weight changed | VALID "<<endl;
        }
        else{
            cout<<"[TEST] Adding a valid edge to the graph, weight not changed | FAILED "<<endl;
            return false;
        }
    }
    else{
        cout<<"[TEST] Adding a valid edge to the graph | FAILED "<<endl;
        return false;
    }

    //Adding a new edge looping on a vertice, should not work
    executionStatus = newGraph.setWeightFromTickers("BTC","BTC",10);
    if(!executionStatus){

        //We check if the edge is still uninitialized
        if(newGraph.getIndexInAdjacencyList(1, 1) == -2){
        cout<<"[TEST] Adding an edge looping on a vertice, should drop an error | VALID "<<endl;
        }
        else{
            cout<<"[TEST] Adding an edge looping on a vertice, edge value changed where it shouldn't | FAILED "<<endl;
            return false;
        }
    }
    else{
        cout<<"[TEST] Adding an edge looping on a vertice, should drop an error | FAILED "<<endl;
        return false;
    }

    //We add an edge with a null ratio between its two vertices, should not work
    executionStatus = newGraph.setWeightFromTickers("USDT","ETH",0);

    if(!executionStatus){

        //We check if the weight of the edge is still not null
        if(newGraph.getAdjacencyList()[0][1].second==-(log(60))){
            cout<<"[TEST] Adding a weight of 0 on an edge, should drop an error, edge value unchanged | VALID "<<endl;
        }
        else{
            cout<<"[TEST] Adding a weight of 0, should drop an error, edge value changed | FAILED "<<endl;
            return false;
        }
    }
    else{
        cout<<"[TEST] Adding a weight of 0 on an edge, should drop an error | FAILED "<<endl;
        return false;
    }

    //We add an edge with a negative ratio between its two vertices, should not work
    executionStatus = newGraph.setWeightFromTickers("USDT","BTC",-2);

    if(!executionStatus){

        //We check if the weight of the edge didn't change
        if(newGraph.getAdjacencyList()[0][0].second==-(log(60))){
            cout<<"[TEST] Adding a negative weight on an edge, should drop an error, edge value unchanged | VALID "<<endl;
        }
        else{
            cout<<"[TEST] Adding a negative weight on an edge, should drop an error, edge value changed | FAILED "<<endl;
            return false;
        }
    }
    else{
        cout<<"[TEST] Adding a negative weight on an edge, should drop an error | FAILED "<<endl;
        return false;
    }

    //We test if the first vertice refuses a negative index
    executionStatus = newGraph.setWeightFromTickers("SOL","BTC",5);

    if(!executionStatus){
        cout<<"[TEST] Adding an edge with a negative index on first vertice, should drop an error | VALID "<<endl;
    }
    else{
        cout<<"[TEST] Adding an edge with a negative index on first vertice, should drop an error | FAILED "<<endl;
        return false;
    }

    //We test if the second vertice refuses a negative index
    executionStatus = newGraph.setWeightFromTickers("BTC","SOL",5);

    if(!executionStatus){
        cout<<"[TEST] Adding an edge with a negative index on second vertice, should drop an error | VALID "<<endl;
    }
    else{
        cout<<"[TEST] Adding an edge with a negative index on second vertice, should drop an error | FAILED "<<endl;
        return false;
    }

    //We test if the first vertice refuses an out-of-range index
    executionStatus = newGraph.setWeightFromTickers("BNB","BTC",5);

    if(!executionStatus){
        cout<<"[TEST] Adding an edge with an out-of-range index on the first vertice, should drop an error | VALID "<<endl;
    }
    else{
        cout<<"[TEST] Adding an edge with a negative index on the first vertice, should drop an error | FAILED "<<endl;
        return false;
    }

    //We test if the second vertice refuses an out-of-range index
    executionStatus = newGraph.setWeightFromTickers("BTC","SOL",5);

    if(!executionStatus){
        cout<<"[TEST] Adding an edge with an out-of-range index on the second vertice, should drop an error | VALID "<<endl;
    }
    else{
        cout<<"[TEST] Adding an edge with a negative index on the second vertice, should drop an error | FAILED "<<endl;
        return false;
    }

    return true;
}

//Tests all different cases for the method getTicker of the class Graph
bool testGetTicker(){
    bool executionStatus;

    //Creates an empty graph with 3 vertices and 0 edges
    Graph newGraph =  Graph();

    executionStatus = newGraph.addTicker("USDT");
    executionStatus = newGraph.addTicker("BTC");
    executionStatus = newGraph.addTicker("ETH");

    string tickerReturned = newGraph.getTicker(0);

    if(tickerReturned=="ERROR"){
        cout<<"[TEST] Getting the ticker of a know index, should work, returned ERROR | FAILED "<<endl;
        return false;
    }
    if(tickerReturned!="USDT"){
        cout<<"[TEST] Getting the ticker of a know index, should return USDT, returned something else | FAILED "<<endl;
        return false;
    }
    else{
        cout<<"[TEST] Getting the ticker of a know index, should return USDT, returned USDT | VALID "<<endl;
    }

    return true;
}

//Tests all different cases for the method setTicker of the class Graph
bool testSetTicker() {

    bool executionStatus;

    Graph newGraph = Graph();
    executionStatus = newGraph.addTicker("QI");
    executionStatus = newGraph.setTicker(0, "BTC");

    if(executionStatus && newGraph.getTicker(0)=="BTC" && newGraph.getIndex("BTC")==0){
        cout<<"[TEST] Setting the ticker's name of index 0 to BTC | VALID "<<endl;
    }
    else{
        cout<<"[TEST] Setting the ticker's name of index 0, still QI, didn't change it's value | FAILED "<<endl;
        return false;
    }

    //We check for a negative index, should not work
    executionStatus = newGraph.setTicker(-1,"BTC");

    if(!executionStatus && newGraph.getTicker(0)=="BTC" && newGraph.getIndex("BTC")==0){
        cout<<"[TEST] Setting the ticker's name of negative index, should drop an error | VALID "<<endl;
    }
    else{
        cout<<"[TEST] Setting the ticker's name of negative index, should drop an error | FAILED "<<endl;
        return false;
    }

    //We check if it refuses as well out-of-range indexes
    executionStatus = newGraph.setTicker(66,"BTC");

    if(!executionStatus && newGraph.getTicker(0)=="BTC" && newGraph.getIndex("BTC")==0){
        cout<<"[TEST] Setting the ticker's name of out-of-range index, should drop an error | VALID "<<endl;
    }
    else{
        cout<<"[TEST] Setting the ticker's name of out-of-range index, should drop an error | FAILED "<<endl;
        return false;
    }

    return true;
}

//Tests all different cases for the method addTicker of the class Graph
bool testAddTicker(){
    bool executionStatus;

    Graph newGraph = Graph();

    //Adding a new valid ticker to the lists
    executionStatus = newGraph.addTicker("QI");

    if(executionStatus && newGraph.getTicker(0)=="QI" && newGraph.getIndex("QI")==0){
        cout<<"[TEST] Setting the ticker's name of index 0 to QI | VALID "<<endl;
    }
    else if(executionStatus){
        cout<<"[TEST] Setting the ticker's name of index 0, not QI, didn't set it's value | FAILED "<<endl;
        return false;
    }

    //Adding an already existing ticker to the list, should not work neither change something
    executionStatus = newGraph.addTicker("QI");

    if(!executionStatus && newGraph.getTicker(0)=="QI" && newGraph.getIndex("QI")==0){
        cout<<"[TEST] Trying to add again the same ticker, didn't change something | VALID "<<endl;
    }
    else if(executionStatus){
        cout<<"[TEST] Trying to add again the same ticker, changed something | FAILED "<<endl;
        return false;
    }

    return true;
}

//Tests all different cases for the method isIndexValid of the class Graph
bool testIsIndexValid(){
    bool executionStatus;

    Graph newGraph = Graph();
    executionStatus = newGraph.addTicker("QI");

    //Checking if 0 is a valid index
    executionStatus = newGraph.isIndexValid(0);

    if(executionStatus){
        cout<<"[TEST] Testing if 0 is a valid index, should work | VALID "<<endl;
    }
    else if(!executionStatus){
        cout<<"[TEST] Testing if 0 is a valid index, should work | FAILED "<<endl;
        return false;
    }

    //Checking if 0 is a valid index
    executionStatus = newGraph.isIndexValid(66);

    if(!executionStatus){
        cout<<"[TEST] Testing if 66 is a valid index, should not work | VALID "<<endl;
    }
    else{
        cout<<"[TEST] Testing if 66 is a valid index, should not work | FAILED "<<endl;
        return false;
    }

    return true;
}

//Tests all different cases for the method convertNegativeLogToOriginal of the class Graph
bool testConvertNegativeToLogOriginal(){
    bool executionStatus;

    Graph graph = Graph("3cryptos.txt", &executionStatus);

    if(executionStatus && Graph::convertNegativeLogToOriginal(graph.getAdjacencyList()[1][0].second)==47050){
        cout<<"[TEST] Convert function valid, correct price returned  | VALID "<<endl;
    }
    else{
        cout<<"[TEST] Convert function not valid, price returned should be 47050 | FAILED "<<endl;
        return false;
    }

    return true;
}

//Tests all different cases for the method getIndex of the class Graph
bool testGetIndex(){
    bool executionStatus;

    Graph graph = Graph();
    graph.addTicker("BTC");
    graph.addTicker("SOL");

    //Getting the indexes of two valid tickers
    int index = graph.getIndex("BTC");
    int index2 = graph.getIndex("SOL");

    if(index == 0 && index2 == 1){
        cout<<"[TEST] Getting the index of BTC and SOL, should return 0 and 1 | VALID "<<endl;
    }
    else{
        cout<<"[TEST] Getting the index of BTC and SOL, should return 0 and 1, didn't work | FAILED "<<endl;
        return false;
    }

    //Getting the index of a non-valid ticker, should return -1
    index2 = graph.getIndex("ETH");

    if(index2 == -1){
        cout<<"[TEST] Getting the index of a non valid ticker, should return -1 | VALID "<<endl;
    }
    else{
        cout<<"[TEST] Getting the index of a non valid ticker, didn't return -1 | FAILED "<<endl;
        return false;
    }

    return true;
}

//Tests all different cases for the method getTokenPriceFromIndex of the class Graph
bool testGetTokenPriceFromIndex(){
    bool executionStatus;

    Graph graph = Graph("3cryptos.txt", &executionStatus);

    //Getting the price of index 1 (BTC) relative to index 0 (USDT)
    double price = graph.getTokenPriceFromIndex(1,0);

    if(executionStatus && price==47050){
        cout<<"[TEST] Getting the price of index 1 (BTC) relative to index 0 (USDT), should return 47050 | VALID "<<endl;
    }
    else if(executionStatus && price==-1){
        cout<<"[TEST] Getting the price of index 1 (BTC) relative to index 0 (USDT), returned -1 (error) | FAILED "<<endl;
        return false;
    }
    else{
        cout<<"[TEST] Something is wrong with the graph initialization | FAILED "<<endl;
        return false;
    }

    //Trying to get the price of a non-existing token
    price = graph.getTokenPriceFromIndex(66,0);

    if(executionStatus && price==-1){
        cout<<"[TEST] Trying to get the price of a non existing token, should return -1 | VALID "<<endl;
    }
    else if(executionStatus && price!=-1){
        cout<<"[TEST] Trying to get the price of a non existing token, didn't return an error | FAILED "<<endl;
        return false;
    }
    else{
        cout<<"[TEST] Something is wrong with the graph initialization | FAILED "<<endl;
        return false;
    }

    //Trying to get the price of an exiting token relative to a non-existing token
    price = graph.getTokenPriceFromIndex(1,66);

    if(executionStatus && price==-1){
        cout<<"[TEST] Trying to get the price of a exiting token relative to a non existing token, should return -1 | VALID "<<endl;
    }
    else if(executionStatus && price!=-1){
        cout<<"[TEST] Trying to get the price of a exiting token relative to a non existing token, didn't return an error | FAILED "<<endl;
        return false;
    }
    else{
        cout<<"[TEST] Something is wrong with the graph initialization | FAILED "<<endl;
        return false;
    }

    return true;
}

//Tests all different cases for the method getTokenPriceFromTicker of the class Graph
bool testGetTokenPriceFromTicker(){

    bool executionStatus;

    Graph graph = Graph("3cryptos.txt", &executionStatus);
    executionStatus = graph.setTicker(0,"USDT");
    executionStatus = graph.setTicker( 1,"BTC");
    executionStatus = graph.setTicker(2, "ETH");

    //Getting the price of the asset bitcoin relative to the USDT one
    double price = graph.getTokenPriceFromTicker("BTC");

    if(executionStatus && price==47050){
        cout<<"[TEST] Getting the price of BTC providing both tickers, should return 47500 | VALID "<<endl;
    }
    else if(executionStatus && price==-1){
        cout<<"[TEST] Getting the price of BTC providing both tickers, returned -1 (error) | FAILED "<<endl;
        return false;
    }
    else{
        cout<<"[TEST] Graph / tickers not successfully set, please check what's wrong | FAILED "<<endl;
        return false;
    }

    //Getting the price of the asset eth relative to the USDT one
    price = graph.getTokenPriceFromTicker("ETH");

    if(executionStatus && price==3803.9999999999973){
        cout<<"[TEST] Getting the price of USDT relative to ETH providing both tickers, should return 47500 | VALID "<<endl;
    }
    else if(executionStatus && price==-1){
        cout<<"[TEST] Getting the price of USDT relative to ETH providing both tickers, returned -1 (error) | FAILED "<<endl;
        return false;
    }
    else{
        cout<<"[TEST] Graph / tickers not successfully set, please check what's wrong | FAILED "<<endl;
        return false;
    }

    //Getting the price of SOL which is an invalid ticker
    price = graph.getTokenPriceFromTicker("SOL");

    if(executionStatus && price==-1){
        cout<<"[TEST] Getting the price of SOL which is an invalid ticker, should return -1 | VALID "<<endl;
    }
    else if(executionStatus && price!=-1){
        cout<<"[TEST] Getting the price of SOL which is an invalid ticker, didn't return -1 (error) | FAILED "<<endl;
        return false;
    }
    else{
        cout<<"[TEST] Graph / tickers not successfully set, please check what's wrong | FAILED "<<endl;
        return false;
    }

    return true;
}

//Tests all different cases for the method getTokenPriceFromTickers of the class Graph
bool testGetTokenPriceFromTickers(){

    bool executionStatus;

    Graph graph = Graph("3cryptos.txt", &executionStatus);
    executionStatus = graph.setTicker(0,"USDT");
    executionStatus = graph.setTicker(1,"BTC");
    executionStatus = graph.setTicker(2, "ETH");

    //Getting the price of the asset bitcoin relative to the USDT one
    double price = graph.getTokenPriceFromTickers("BTC","USDT");

    if(executionStatus && price==47050){
        cout<<"[TEST] Getting the price of BTC providing both tickers, should return 47500 | VALID "<<endl;
    }
    else if(executionStatus && price==-1){
        cout<<"[TEST] Getting the price of BTC providing both tickers, returned -1 (error) | FAILED "<<endl;
        return false;
    }
    else{
        cout<<"[TEST] Graph / tickers not successfully set, please check what's wrong | FAILED "<<endl;
        return false;
    }

    //Getting the price of the asset bitcoin relative to the USDT one
    price = graph.getTokenPriceFromTickers("USDT","ETH");

    if(executionStatus && price==0.00026288117770000024){
        cout<<"[TEST] Getting the price of USDT relative to ETH providing both tickers | VALID "<<endl;
    }
    else if(executionStatus && price==-1){
        cout<<"[TEST] Getting the price of USDT relative to ETH providing both tickers, returned -1 (error) | FAILED "<<endl;
        return false;
    }
    else{
        cout<<"[TEST] Graph / tickers not successfully set, please check what's wrong | FAILED "<<endl;
        return false;
    }

    //Getting the price of the asset bitcoin relative to the UST one, should fail
    price = graph.getTokenPriceFromTickers("BTC","UST");

    if(executionStatus && price==-1){
        cout<<"[TEST] Getting the price of BTC with an invalid second ticker, should return -1 | VALID "<<endl;
    }
    else if(executionStatus && price!=-1){
        cout<<"[TEST] Getting the price of BTC with an invalid second ticker, didn't return -1 (error) | FAILED "<<endl;
        return false;
    }
    else{
        cout<<"[TEST] Graph / tickers not successfully set, please check what's wrong | FAILED "<<endl;
        return false;
    }

    //Getting the price of the asset bitcoin relative to the UST one, should fail
    price = graph.getTokenPriceFromTickers("SOL","USDT");

    if(executionStatus && price==-1){
        cout<<"[TEST] Getting the price of an invalid token, should return -1 | VALID "<<endl;
    }
    else if(executionStatus && price!=-1){
        cout<<"[TEST] Getting the price of an invalid token, didn't return -1 (error) | FAILED "<<endl;
        return false;
    }
    else{
        cout<<"[TEST] Graph / tickers not successfully set, please check what's wrong | FAILED "<<endl;
        return false;
    }

    return true;
}