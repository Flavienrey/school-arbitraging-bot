//
// Created by Didier on 22/02/2022.
//

#include "GraphTests.hpp"
#include "Graph.hpp"
#include <limits>

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

    cout<<endl<<"---Testing setWeight function---"<<endl;
    successStatus = testSetWeightFromIndexes();
    if(!successStatus) {
        cout<<"setWeightFromIndexes function tests failed, please check what's wrong"<<endl;
        cout<<endl<<"[TEST] Some tests failed, please check !"<<endl;
        return false;
    }
    else{
        cout<<"---setWeightFromIndexes function tests successful---"<<endl;
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

    cout<<endl<<"[TEST] All tests passed successfully, well done master !"<<endl;
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

    //Creating an empty graph with 3 vertices and 0 edges, should return true
    Graph newGraph2("emptyGraph.txt", &executionStatus);

    if(executionStatus){
        cout<<"[TEST] Instantiating test with an empty graph (0 edges) | VALID "<<endl;
    }
    else{
        cout<<"[TEST] Instantiating test with an empty graph (0 edges) | FAILED "<<endl;
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

//Tests all different cases for the method setWeightFromIndexes of the class Graph
bool testSetWeightFromIndexes(){
    bool executionStatus;

    //Creates an empty graph with 3 vertices and 0 edges
    Graph newGraph =  Graph("emptyGraph.txt",&executionStatus);

    //Adding an edge to the graph, should be a success
    executionStatus = newGraph.setWeightFromIndexes(0,1,10,NEGATIVE_LOG);

    if(executionStatus){

        //We check here after the execution successfully changed the ratio
        if(newGraph.getAdjacencyMatrix()[0][1]==(-log(10))){
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
    executionStatus = newGraph.setWeightFromIndexes(1,1,10,NEGATIVE_LOG);
    if(!executionStatus){

        //We check if the edge is still uninitialized
        if(newGraph.getAdjacencyMatrix()[1][1]==numeric_limits<double>::infinity()){
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
    executionStatus = newGraph.setWeightFromIndexes(0,2,0,NEGATIVE_LOG);

    if(!executionStatus){

        //We check if the weight of the edge is still not null
        if(newGraph.getAdjacencyMatrix()[0][1]!=numeric_limits<double>::infinity()){
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
    executionStatus = newGraph.setWeightFromIndexes(0,1,-2,NEGATIVE_LOG);

    if(!executionStatus){

        //We check if the weight of the edge didn't change
        if(newGraph.getAdjacencyMatrix()[0][1]==-(log(10))){
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
    executionStatus = newGraph.setWeightFromIndexes(-1,1,5,NEGATIVE_LOG);

    if(!executionStatus){
        cout<<"[TEST] Adding an edge with a negative index on first vertice, should drop an error | VALID "<<endl;
    }
    else{
        cout<<"[TEST] Adding an edge with a negative index on first vertice, should drop an error | FAILED "<<endl;
        return false;
    }

    //We test if the second vertice refuses a negative index
    executionStatus = newGraph.setWeightFromIndexes(1,-1,5,NEGATIVE_LOG);

    if(!executionStatus){
        cout<<"[TEST] Adding an edge with a negative index on second vertice, should drop an error | VALID "<<endl;
    }
    else{
        cout<<"[TEST] Adding an edge with a negative index on second vertice, should drop an error | FAILED "<<endl;
        return false;
    }

    //We test if the first vertice refuses an out-of-range index
    executionStatus = newGraph.setWeightFromIndexes(66,1,5,NEGATIVE_LOG);

    if(!executionStatus){
        cout<<"[TEST] Adding an edge with an out-of-range index on the first vertice, should drop an error | VALID "<<endl;
    }
    else{
        cout<<"[TEST] Adding an edge with a negative index on the first vertice, should drop an error | FAILED "<<endl;
        return false;
    }

    //We test if the second vertice refuses an out-of-range index
    executionStatus = newGraph.setWeightFromIndexes(1,66,5,NEGATIVE_LOG);

    if(!executionStatus){
        cout<<"[TEST] Adding an edge with an out-of-range index on the second vertice, should drop an error | VALID "<<endl;
    }
    else{
        cout<<"[TEST] Adding an edge with a negative index on the second vertice, should drop an error | FAILED "<<endl;
        return false;
    }

    return true;
}

//Tests all different cases for the method setTicker of the class Graph
bool testSetTicker() {

    bool executionStatus;

    Graph newGraph = Graph("3cryptos.txt", &executionStatus);
    executionStatus = newGraph.addTicker("");

    if (executionStatus) {
        //We check for a valid index, should work
        executionStatus = newGraph.setTicker(0, "BTC");
    }

    if(executionStatus && newGraph.getTicker(0)=="BTC"){
        cout<<"[TEST] Setting the ticker's name of index 0 | VALID "<<endl;
    }
    else{
        cout<<"[TEST] Setting the ticker's name of index 0 | FAILED "<<endl;
        return false;
    }

    //We check for a negative index, should not work
    executionStatus = newGraph.setTicker(-1,"BTC");

    if(!executionStatus){
        cout<<"[TEST] Setting the ticker's name of negative index, should drop an error | VALID "<<endl;
    }
    else{
        cout<<"[TEST] Setting the ticker's name of negative index, should drop an error | FAILED "<<endl;
        return false;
    }

    //We check if it refuses as well out-of-range indexes
    executionStatus = newGraph.setTicker(66,"BTC");

    if(!executionStatus){
        cout<<"[TEST] Setting the ticker's name of out-of-range index, should drop an error | VALID "<<endl;
    }
    else{
        cout<<"[TEST] Setting the ticker's name of out-of-range index, should drop an error | FAILED "<<endl;
        return false;
    }

    return true;
}

//Tests all different cases for the method getTokenPriceFromIndex of the class Graph
bool testGetTokenPriceFromIndex(){
    bool executionStatus;

    Graph graph = Graph("3cryptos.txt", &executionStatus);
    double price = graph.getTokenPriceFromIndex(1,0);

    if(executionStatus && price==47050){
        cout<<"[TEST] Getting the price of the token 0, should return 47500 | VALID "<<endl;
    }
    else if(executionStatus && price==-1){
        cout<<"[TEST] Getting the price of the token 0, returned -1 (error) | FAILED "<<endl;
        return false;
    }
    else{
        cout<<"[TEST] Getting the price of the token 0, returned an incorrect price | FAILED "<<endl;
        return false;
    }

    return true;
}

//Tests all different cases for the method convertNegativeLogToOriginal of the class Graph
bool testConvertNegativeToLogOriginal(){
    bool executionStatus;

    Graph graph = Graph("3cryptos.txt", &executionStatus);
    if(executionStatus && Graph::convertNegativeLogToOriginal(graph.getAdjacencyMatrix()[1][0])==47050){
        cout<<"[TEST] Convert function valid, correct price returned  | VALID "<<endl;
    }
    else{
        cout<<"[TEST] Convert function not valid, price returned should be 47050 | FAILED "<<endl;
        return false;
    }


    return true;
}


//Tests all different cases for the method getTokenPriceFromTickers of the class Graph
bool testGetTokenPriceFromTickers(){

    bool executionStatus;

    Graph graph = Graph("3cryptos.txt", &executionStatus);
    executionStatus = graph.addTicker("USDT");
    executionStatus = graph.addTicker("BTC");
    executionStatus = graph.addTicker("ETH");

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


//Tests all different cases for the method getTokenPriceFromTicker of the class Graph
bool testGetTokenPriceFromTicker(){

    bool executionStatus;

    Graph graph = Graph("3cryptos.txt", &executionStatus);
    executionStatus = graph.addTicker("USDT");
    executionStatus = graph.addTicker( "BTC");
    executionStatus = graph.addTicker( "ETH");

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

    //Getting the price of the asset bitcoin relative to the USDT one
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

    //Getting the price of the asset bitcoin relative to the UST one, should fail
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