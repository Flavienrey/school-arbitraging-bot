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
    successStatus = testNegativeCycleDetection();
    if(!successStatus) {
        cout<<"DetectNegativeCycle function tests failed, please check what's wrong"<<endl;
        cout<<endl<<"[TEST] Some tests failed, please check !"<<endl;
        return false;
    }
    else{
        cout<<"---DetectNegativeCycle function tests successful---"<<endl;
    }

    cout<<endl<<"---Testing FindAndReturnWeightOfBestRoute function---"<<endl;
    successStatus = testFindAndReturnWeightOfBestRoute();
    if(!successStatus) {
        cout<<"FindAndReturnWeightOfBestRoute function tests failed, please check what's wrong"<<endl;
        cout<<endl<<"[TEST] Some tests failed, please check !"<<endl;
        return false;
    }
    else{
        cout<<"---FindAndReturnWeightOfBestRoute function tests successful---"<<endl;
    }

    cout<<endl<<"[TEST] FindAndReturnWeightOfBestRoute tests passed successfully, well done master !"<<endl;
    return true;
}

//Tests all different cases for the method bellmanFord of the class Graph
bool testBellmanFordAlgorithm(){
    bool executionStatus = true;

    Graph graph = Graph();

    graph.addTicker("USDT");
    graph.addTicker("BTC");
    graph.addTicker("ETH");
    graph.addTicker("SOL");
    graph.addTicker("BNB");
    graph.addTicker("USDC");

    graph.addEdgeToAdjacencyList(0,1,exp(-4));
    graph.addEdgeToAdjacencyList(0,3,exp(-2));
    graph.addEdgeToAdjacencyList(1,3,exp(6));
    graph.addEdgeToAdjacencyList(3,4,exp(-2));
    graph.addEdgeToAdjacencyList(1,4,exp(-4));
    graph.addEdgeToAdjacencyList(4,5,exp(-17));
    graph.addEdgeToAdjacencyList(1,2,exp(-15));
    graph.addEdgeToAdjacencyList(2,5,exp(-1));

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

    graph = Graph();

    graph.addTicker("USDT");
    graph.addTicker("BTC");
    graph.addTicker("ETH");
    graph.addTicker("BNB");
    graph.addTicker("SOL");

    graph.addEdgeToAdjacencyList(1,2,exp(-4));
    graph.addEdgeToAdjacencyList(1,3,exp(-3));
    graph.addEdgeToAdjacencyList(2,4,exp(-7));
    graph.addEdgeToAdjacencyList(3,4,exp(2));

    graph.bellmanFord(1);

    vector<int> correctPreviousVerticesCodeSpeedy = {-1,0,1,1,3};
    vector<double> correctWeightsCodeSpeedy = {1000000000,0,4,3,1};

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

    graph.bellmanFord(0);

    if (!graph.detectNegativeCycle()) {
        cout << "[TEST] Testing negativeCycleDetection on 3cryptos, should not detect an opportunity | VALID " << endl;
    }
    else{
        cout << "[TEST] Testing negativeCycleDetection on 3cryptos, opportunity detected where it shouldn't | FAILED "<< endl;
        return false;
    }

    Graph graph2 = Graph("arbitrage3Cryptos.txt", &executionStatus);

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

bool testFindAndReturnWeightOfBestRoute(){

    Graph graph = Graph();

    graph.addTicker("USDT");
    graph.addTicker("BTC");
    graph.addTicker("ETH");
    graph.addTicker("BCH");
    graph.addTicker("LTC");
    graph.addTicker("XRP");
    graph.addTicker("XLM");
    graph.addTicker("OMG");

    //Actual cycle = USDT -> BTC -> ETH -> USDT = 1.002691593
    //Best = USDT -> XRP -> BTC -> ETH -> USDT = 1.002828869  log(x) = 1,226827761 *10 ^-3

    //With arbitrage
    graph.addEdgeToAdjacencyList(graph.getIndex("USDT"),graph.getIndex("BTC"),1.0/42732.8); //initial 42740.8
    graph.addEdgeToAdjacencyList(graph.getIndex("ETH"),graph.getIndex("USDT"),3020); //3012.24
    graph.addEdgeToAdjacencyList(graph.getIndex("BTC"),graph.getIndex("ETH"),1.0/0.070482); //0.070486
    graph.addEdgeToAdjacencyList(graph.getIndex("ETH"),graph.getIndex("BTC"),0.070481); //0.070482

    //Pairs with USDT ____________________________________________________________________________________________________________________
    graph.addEdgeToAdjacencyList(graph.getIndex("BTC"),graph.getIndex("USDT"),42732.1);

    graph.addEdgeToAdjacencyList(graph.getIndex("USDT"),graph.getIndex("ETH"),1.0/3012.85);

    graph.addEdgeToAdjacencyList(graph.getIndex("USDT"),graph.getIndex("BCH"),1.0/371.46);
    graph.addEdgeToAdjacencyList(graph.getIndex("BCH"),graph.getIndex("USDT"),371.18);

    graph.addEdgeToAdjacencyList(graph.getIndex("USDT"),graph.getIndex("LTC"),1.0/121.121);
    graph.addEdgeToAdjacencyList(graph.getIndex("LTC"),graph.getIndex("USDT"),121.001);

    graph.addEdgeToAdjacencyList(graph.getIndex("USDT"),graph.getIndex("XRP"),1.0/0.84343);
    graph.addEdgeToAdjacencyList(graph.getIndex("XRP"),graph.getIndex("USDT"),0.84336);

    graph.addEdgeToAdjacencyList(graph.getIndex("USDT"),graph.getIndex("XLM"),1.0/0.2078);
    graph.addEdgeToAdjacencyList(graph.getIndex("XLM"),graph.getIndex("USDT"),0.2077);

    graph.addEdgeToAdjacencyList(graph.getIndex("USDT"),graph.getIndex("OMG"),1.0/4.9002);
    graph.addEdgeToAdjacencyList(graph.getIndex("OMG"),graph.getIndex("USDT"),4.8788);

    //Missing pairs with BTC ____________________________________________________________________________________________________________________
    graph.addEdgeToAdjacencyList(graph.getIndex("BTC"),graph.getIndex("BCH"),1.0/0.008692);
    graph.addEdgeToAdjacencyList(graph.getIndex("BCH"),graph.getIndex("BTC"),0.00867);

    graph.addEdgeToAdjacencyList(graph.getIndex("BTC"),graph.getIndex("LTC"),1.0/0.00283344);
    graph.addEdgeToAdjacencyList(graph.getIndex("LTC"),graph.getIndex("BTC"),0.00283286);

    graph.addEdgeToAdjacencyList(graph.getIndex("BTC"),graph.getIndex("XRP"),1.0/0.00001975);
    graph.addEdgeToAdjacencyList(graph.getIndex("XRP"),graph.getIndex("BTC"),0.00001974);

    graph.addEdgeToAdjacencyList(graph.getIndex("BTC"),graph.getIndex("XLM"),1.0/0.00000488);
    graph.addEdgeToAdjacencyList(graph.getIndex("XLM"),graph.getIndex("BTC"),0.00000485);

    graph.addEdgeToAdjacencyList(graph.getIndex("BTC"),graph.getIndex("OMG"),1.0/0.00011501);
    graph.addEdgeToAdjacencyList(graph.getIndex("OMG"),graph.getIndex("BTC"),0.00011429);

    //BellmanFord - ________________________________________________________________________________________________________________________
    graph.bellmanFord(graph.getIndex("USDT"));

    double weight = graph.findAndReturnWeightOfBestRoute();
    double percentage = graph.displayRouteAndPercentage(weight);

    if(weight == -0.002824875313949704 && percentage == 0.28288690339208777 && graph.detectNegativeCycle()){
        cout << "[TEST] Testing FindAndReturnWeightOfBestRoute, must find an arbitrage | VALID " << endl;
    }
    else{
        cout << "[TEST] Testing FindAndReturnWeightOfBestRoute, didn't find the arbitrage | FAILED " << endl;
        return false;
    }


    graph = Graph();

    graph.addTicker("USDT");
    graph.addTicker("BTC");
    graph.addTicker("ETH");
    graph.addTicker("BCH");
    graph.addTicker("LTC");
    graph.addTicker("XRP");
    graph.addTicker("XLM");
    graph.addTicker("OMG");

    //Actual cycle = USDT -> BTC -> ETH -> USDT = 1.002691593
    //Best = USDT -> XRP -> BTC -> ETH -> USDT = 1.002828869  log(x) = 1,226827761 *10 ^-3

    //Without arbitrage
    graph.addEdgeToAdjacencyList(graph.getIndex("USDT"),graph.getIndex("BTC"),1.0/42740.8);
    graph.addEdgeToAdjacencyList(graph.getIndex("ETH"),graph.getIndex("USDT"),3012.24);
    graph.addEdgeToAdjacencyList(graph.getIndex("BTC"),graph.getIndex("ETH"),1.0/0.070486);
    graph.addEdgeToAdjacencyList(graph.getIndex("ETH"),graph.getIndex("BTC"),0.070482);

    //Pairs with USDT ____________________________________________________________________________________________________________________
    graph.addEdgeToAdjacencyList(graph.getIndex("BTC"),graph.getIndex("USDT"),42732.1);

    graph.addEdgeToAdjacencyList(graph.getIndex("USDT"),graph.getIndex("ETH"),1.0/3012.85);

    graph.addEdgeToAdjacencyList(graph.getIndex("USDT"),graph.getIndex("BCH"),1.0/371.46);
    graph.addEdgeToAdjacencyList(graph.getIndex("BCH"),graph.getIndex("USDT"),371.18);

    graph.addEdgeToAdjacencyList(graph.getIndex("USDT"),graph.getIndex("LTC"),1.0/121.121);
    graph.addEdgeToAdjacencyList(graph.getIndex("LTC"),graph.getIndex("USDT"),121.001);

    graph.addEdgeToAdjacencyList(graph.getIndex("USDT"),graph.getIndex("XRP"),1.0/0.84343);
    graph.addEdgeToAdjacencyList(graph.getIndex("XRP"),graph.getIndex("USDT"),0.84336);

    graph.addEdgeToAdjacencyList(graph.getIndex("USDT"),graph.getIndex("XLM"),1.0/0.2078);
    graph.addEdgeToAdjacencyList(graph.getIndex("XLM"),graph.getIndex("USDT"),0.2077);

    graph.addEdgeToAdjacencyList(graph.getIndex("USDT"),graph.getIndex("OMG"),1.0/4.9002);
    graph.addEdgeToAdjacencyList(graph.getIndex("OMG"),graph.getIndex("USDT"),4.8788);

    //Missing pairs with BTC ____________________________________________________________________________________________________________________
    graph.addEdgeToAdjacencyList(graph.getIndex("BTC"),graph.getIndex("BCH"),1.0/0.008692);
    graph.addEdgeToAdjacencyList(graph.getIndex("BCH"),graph.getIndex("BTC"),0.00867);

    graph.addEdgeToAdjacencyList(graph.getIndex("BTC"),graph.getIndex("LTC"),1.0/0.00283344);
    graph.addEdgeToAdjacencyList(graph.getIndex("LTC"),graph.getIndex("BTC"),0.00283286);

    graph.addEdgeToAdjacencyList(graph.getIndex("BTC"),graph.getIndex("XRP"),1.0/0.00001975);
    graph.addEdgeToAdjacencyList(graph.getIndex("XRP"),graph.getIndex("BTC"),0.00001974);

    graph.addEdgeToAdjacencyList(graph.getIndex("BTC"),graph.getIndex("XLM"),1.0/0.00000488);
    graph.addEdgeToAdjacencyList(graph.getIndex("XLM"),graph.getIndex("BTC"),0.00000485);

    graph.addEdgeToAdjacencyList(graph.getIndex("BTC"),graph.getIndex("OMG"),1.0/0.00011501);
    graph.addEdgeToAdjacencyList(graph.getIndex("OMG"),graph.getIndex("BTC"),0.00011429);

    //BellmanFord - ________________________________________________________________________________________________________________________
    graph.bellmanFord(graph.getIndex("USDT"));

    weight = graph.findAndReturnWeightOfBestRoute();
    percentage = graph.displayRouteAndPercentage(weight);

    if(weight == -0.00019528149712755294 && percentage == 0.019530056580041588 && graph.detectNegativeCycle()){
        cout << "[TEST] Testing FindAndReturnWeightOfBestRoute, must not find the arbitrage | VALID " << endl;
    }
    else{
        cout << "[TEST] Testing FindAndReturnWeightOfBestRoute, found an arbitrage where it shouldn't | FAILED " << endl;
        return false;
    }

    return true;
}
