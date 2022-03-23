#include "httpGetFunctions.hpp"
#include "Graph.hpp"
#include "GraphTests.hpp"
#include "BellmanFordTests.hpp"
#include "Time.hpp"
#include "json.hpp"

using json = nlohmann::json;

bool startTestFunctions(){
    bool graphTestsSuccess = startAllGraphTests();
    bool bellmanFordTestsSuccess = startAllBellmanFordTests();

    if(graphTestsSuccess && bellmanFordTestsSuccess){
        cout<<endl<<"[TESTS RESULTS] All tests passed successfully !!!"<<endl;
        return true;
    }
    else if(!graphTestsSuccess && bellmanFordTestsSuccess){
        cout<<endl<<"[TESTS RESULTS] BellmanFord tests VALID but Graph tests FAILED !!!"<<endl;
        return false;
    }
    else if(graphTestsSuccess){
        cout<<endl<<"[TESTS RESULTS] Graph tests VALID but BellmanFord tests FAILED !!!"<<endl;
        return false;
    }

    cout<<endl<<"[TESTS RESULTS] Both tests FAILED !!!"<<endl;
    return false;
}

void startBotOnKucoin(){

    //We create our graph
    Graph graphKucoin = Graph();

    //We get the attribute data that contains the symbols list
    auto J_data = getAllSymbolsFromKucoin();

    graphKucoin.fillTickersWithKucoin(J_data);

    double totalTimeForUpdateMatrix = 0.0;
    double totalTimeBellmanFord = 0.0;
    double totalTimeForDetectNegativeCycle = 0.0;

    Time time = Time();

    int numberOfTestsIterations = 100;
    for(int i=0; i<numberOfTestsIterations; i++) {

        time.reset();
        graphKucoin.updateAdjacencyListWithKucoin();
        totalTimeForUpdateMatrix+=time.elapsed();

        //_________________________________________________________________________
        time.reset();
        graphKucoin.bellmanFord(graphKucoin.getIndex("USDT"));
        totalTimeBellmanFord+=time.elapsed();

        time.reset();
        double weight = graphKucoin.findAndReturnWeightOfBestRoute();
        if(weight>0 && graphKucoin.detectNegativeCycle()){
            cout << "[USDT] Weight of the cycle is "<<weight<<endl;
        }
        totalTimeForDetectNegativeCycle+=time.elapsed();

        //_________________________________________________________________________
        time.reset();
        graphKucoin.bellmanFord(graphKucoin.getIndex("USDC"));
        totalTimeBellmanFord+=time.elapsed();

        time.reset();
        weight = graphKucoin.findAndReturnWeightOfBestRoute();
        if(weight>0 && graphKucoin.detectNegativeCycle()){
            cout << "[USDC] Weight of the cycle is "<<weight<<endl;
        }
        totalTimeForDetectNegativeCycle+=time.elapsed();

        //_________________________________________________________________________
        time.reset();
        graphKucoin.bellmanFord(graphKucoin.getIndex("BTC"));
        totalTimeBellmanFord+=time.elapsed();

        time.reset();
        weight = graphKucoin.findAndReturnWeightOfBestRoute();
        if(weight>0 && graphKucoin.detectNegativeCycle()){
            cout << "[BTC] Weight of the cycle is "<<weight<<"and is a coefficient of "<<Graph::convertNegativeLogToOriginal(weight)<<endl;
        }
        totalTimeForDetectNegativeCycle+=time.elapsed();
    }

    cout<<"Average time required to update matrix : "<<(totalTimeForUpdateMatrix/numberOfTestsIterations)*pow(10,3)<<"ms"<<endl;
    cout<<"Average time required to run bellmanFord : "<<(totalTimeBellmanFord*3/numberOfTestsIterations)*pow(10,3)<<"ms"<<endl;
    cout<<"Average time required to detect negative cycle : "<<(totalTimeForDetectNegativeCycle*3/numberOfTestsIterations)*pow(10,3)<<"ms"<<endl;
    cout<<"Total time required to execute everything : "<<((totalTimeForDetectNegativeCycle+totalTimeBellmanFord+totalTimeForUpdateMatrix)*3/numberOfTestsIterations)*pow(10,3)<<"ms"<<endl;

}

void startBotOnCexIO(){

    //We create our graph
    Graph graphCexIO = Graph();

    //We get the attribute data that contains the symbols list
    auto J_data = getAllSymbolsFromCEX();

    graphCexIO.fillTickersWithCexIO(J_data);

    double totalTimeForUpdateMatrix = 0.0;
    double totalTimeBellmanFord = 0.0;
    double totalTimeForDetectNegativeCycle = 0.0;

    Time time = Time();

    int numberOfTestsIterations = 10000;
    for(int i=0; i<numberOfTestsIterations; i++) {

        time.reset();
        graphCexIO.updateAdjacencyListWithCexIO();
        totalTimeForUpdateMatrix+=time.elapsed();

        //_________________________________________________________________________
        time.reset();
        graphCexIO.bellmanFord(graphCexIO.getIndex("USDT"));
        totalTimeBellmanFord+=time.elapsed();

        time.reset();
        double weight = graphCexIO.findAndReturnWeightOfBestRoute();
        if(weight>0 && graphCexIO.detectNegativeCycle()){
            cout << "[USDT] Weight of the cycle is "<<weight<<"and is a coefficient of "<<Graph::convertNegativeLogToOriginal(weight)<<endl;
        }
        totalTimeForDetectNegativeCycle+=time.elapsed();

        //_________________________________________________________________________
        time.reset();
        graphCexIO.bellmanFord(graphCexIO.getIndex("USDC"));
        totalTimeBellmanFord+=time.elapsed();

        time.reset();
        weight = graphCexIO.findAndReturnWeightOfBestRoute();
        if(weight>0 && graphCexIO.detectNegativeCycle()){
            cout << "[USDC] Weight of the cycle is "<<weight<<"and is a coefficient of "<<Graph::convertNegativeLogToOriginal(weight)<<endl;
        }
        totalTimeForDetectNegativeCycle+=time.elapsed();

        //_________________________________________________________________________
        time.reset();
        graphCexIO.bellmanFord(graphCexIO.getIndex("BTC"));
        totalTimeBellmanFord+=time.elapsed();

        time.reset();
        weight = graphCexIO.findAndReturnWeightOfBestRoute();
        if(weight>0 && graphCexIO.detectNegativeCycle()){
            cout << "[BTC] Weight of the cycle is "<<weight<<"and is a coefficient of "<<Graph::convertNegativeLogToOriginal(weight)<<endl;
        }
        totalTimeForDetectNegativeCycle+=time.elapsed();

    }

    cout<<"Average time required to update matrix : "<<(totalTimeForUpdateMatrix/numberOfTestsIterations)*pow(10,3)<<"ms"<<endl;
    cout<<"Average time required to run bellmanFord : "<<(totalTimeBellmanFord/numberOfTestsIterations)*pow(10,3)<<"ms"<<endl;
    cout<<"Average time required to detect negative cycle : "<<(totalTimeForDetectNegativeCycle/numberOfTestsIterations)*pow(10,3)<<"ms"<<endl;
    cout<<"Total time required to detect negative cycle : "<<((totalTimeForDetectNegativeCycle+totalTimeBellmanFord+totalTimeForUpdateMatrix)*3/numberOfTestsIterations)*pow(10,3)<<"ms"<<endl;

}

void testFindRouteInGraph(){

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

    //Pairs with USDT ____________________________________________________________________________________________________________________

    graph.addEdgeToAdjacencyList(graph.getIndex("USDT"),graph.getIndex("BTC"),1.0/42732.8); //initial 42740.8
    graph.addEdgeToAdjacencyList(graph.getIndex("BTC"),graph.getIndex("USDT"),42732.1);

    graph.addEdgeToAdjacencyList(graph.getIndex("USDT"),graph.getIndex("ETH"),1.0/3012.85);
    graph.addEdgeToAdjacencyList(graph.getIndex("ETH"),graph.getIndex("USDT"),3020); //3012.24

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

    graph.addEdgeToAdjacencyList(graph.getIndex("BTC"),graph.getIndex("ETH"),1.0/0.070482); //0.070486
    graph.addEdgeToAdjacencyList(graph.getIndex("ETH"),graph.getIndex("BTC"),0.070481); //0.070482

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
    if(weight>0 && graph.detectNegativeCycle()){
        cout << "[USDT] with negative cycle : Weight of the cycle is "<<weight<<"and is a coefficient of "<<Graph::convertNegativeLogToOriginal(weight)<<endl;
    }
    else if(weight>0){
        cout << "[USDT] without negative cycle : Weight of the cycle is "<<weight<<"and is a coefficient of "<<Graph::convertNegativeLogToOriginal(weight)<<endl;
    }

    //BellmanFord - ________________________________________________________________________________________________________________________
    graph.bellmanFord(graph.getIndex("BTC"));

    weight = graph.findAndReturnWeightOfBestRoute();
    if(weight>0 && graph.detectNegativeCycle()){
        cout << "[USDT] with negative cycle : Weight of the cycle is "<<weight<<"and is a coefficient of "<<Graph::convertNegativeLogToOriginal(weight)<<endl;
    }
    else if(weight>0){
        cout << "[USDT] without negative cycle : Weight of the cycle is "<<weight<<"and is a coefficient of "<<Graph::convertNegativeLogToOriginal(weight)<<endl;
    }

}

int main() {

    bool implementationValid = true;
    //startTestFunctions();

    testFindRouteInGraph();

    if(implementationValid) {
        //startBotOnKucoin();
        //startBotOnCexIO();
    }

    return EXIT_SUCCESS;
}