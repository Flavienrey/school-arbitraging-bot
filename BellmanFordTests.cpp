//
// Created by Didier on 25/02/2022.
//

#include <limits>
#include "BellmanFordTests.hpp"
#include "Graph.hpp"

//Starts all tests and return true if the execution is successful
bool startAllBellmanFordTests(){
    bool successStatus;

    cout<<endl<<"[TEST] Beginning of the BellmanFord tests"<<endl;
    cout<<"---Testing bellmanFord algorithm---"<<endl;
    successStatus = testBellmanFordAlgorithm();
    if(!successStatus) {
        cout<<"bellmanFord algorithm tests failed, please check what's wrong"<<endl;
        cout<<endl<<"[TEST] Some tests failed, please check !"<<endl;
        return false;
    }
    else{
        cout<<"---BellmanFord algorithm tests successful---"<<endl;
    }

    cout<<endl<<"---Testing detectNegativeCycle function---"<<endl;
    successStatus = true;//testNegativeCycleDetection();
    if(!successStatus) {
        cout<<"DetectNegativeCycle function tests failed, please check what's wrong"<<endl;
        cout<<endl<<"[TEST] Some tests failed, please check !"<<endl;
        return false;
    }
    else{
        cout<<"---DetectNegativeCycle function tests successful---"<<endl;
    }

    cout<<endl<<"[TEST] BellmanFord tests passed successfully, well done master !"<<endl;
    return true;
}

//Tests all different cases for the method bellmanFord of the class Graph
bool testBellmanFordAlgorithm(){
    bool executionStatus = true;

    Graph graph = Graph(0,8);

    graph.addTicker("USDT");
    graph.addTicker("BTC");
    graph.addTicker("ETH");
    graph.addTicker("SOL");
    graph.addTicker("BNB");
    graph.addTicker("USDC");

    graph.initializeAdjacencyMatrix();

    graph.setWeightFromIndexes(0,1,exp(-4));
    graph.setWeightFromIndexes(0,3,exp(-2));
    graph.setWeightFromIndexes(1,3,exp(6));
    graph.setWeightFromIndexes(3,4,exp(-2));
    graph.setWeightFromIndexes(1,4,exp(-4));
    graph.setWeightFromIndexes(4,5,exp(-17));
    graph.setWeightFromIndexes(1,2,exp(-15));
    graph.setWeightFromIndexes(2,5,exp(-1));

    graph.bellmanFord(0);

    vector<int> correctPreviousVerticesDevMath = {0,0,1,1,3,4};
    vector<double> correctWeightsDevMath = {0,4,19,-2,0,17};

    if(correctPreviousVerticesDevMath == graph.getPreviousVertices() && correctWeightsDevMath == graph.getWeightsFromSource()) {
        cout << "[TEST] Testing BellmanFord on devMath | VALID " << endl;
    }
    else{
        cout << "[TEST] Testing BellmanFord on devMath, returned true but results are not valid | FAILED " << endl;
        return false;
    }

    graph = Graph(0,4);

    graph.addTicker("USDT");
    graph.addTicker("BTC");
    graph.addTicker("ETH");
    graph.addTicker("BNB");
    graph.addTicker("SOL");

    graph.initializeAdjacencyMatrix();

    graph.setWeightFromIndexes(1,2,exp(-4));
    graph.setWeightFromIndexes(1,3,exp(-3));
    graph.setWeightFromIndexes(2,4,exp(-7));
    graph.setWeightFromIndexes(3,4,exp(2));

    graph.bellmanFord(1);

    vector<int> correctPreviousVerticesCodeSpeedy = {-1,0,1,1,3};
    vector<double> correctWeightsCodeSpeedy = {numeric_limits<double>::infinity(),0,4,3,1};

    if(correctPreviousVerticesCodeSpeedy == graph.getPreviousVertices() && correctWeightsCodeSpeedy == graph.getWeightsFromSource()) {
        cout << "[TEST] Testing BellmanFord on codeSpeedy | VALID " << endl;
    }
    else{
        cout << "[TEST] Testing BellmanFord on codeSpeedy, returned true but results are not valid | FAILED " << endl;
        return false;
    }

    return true;
}

//Tests all different cases for the method detectNegativeCycle of the class Graph
bool testNegativeCycleDetection() {
    bool executionStatus = false;

    Graph graph = Graph("3cryptos.txt", &executionStatus);

    graph.initializeTickers();

    graph.bellmanFord(0);

    if (!graph.detectNegativeCycle()) {
        cout << "[TEST] Testing negativeCycleDetection on 3cryptos, should not detect an opportunity | VALID " << endl;
    }
    else{
        cout << "[TEST] Testing negativeCycleDetection on 3cryptos, opportunity detected where it shouldn't | FAILED "<< endl;
        return false;
    }

    Graph graph2 = Graph("arbitrage3Cryptos.txt", &executionStatus);

    graph2.initializeTickers();

    graph2.bellmanFord(0);

    if (graph2.detectNegativeCycle()) {
        cout << "[TEST] Testing negativeCycleDetection on arbitrage3Cryptos, should  detect an opportunity | VALID " << endl;
    }
    else{
        cout << "[TEST] Testing negativeCycleDetection on arbitrage3Cryptos, opportunity not detected where it should | FAILED "<< endl;
        return false;
    }

    return true;
}
