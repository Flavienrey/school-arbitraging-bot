#include "httpGetFunctions.hpp"
#include "Graph.hpp"
#include "GraphTests.hpp"
#include "BellmanFordTests.hpp"
#include "Time.hpp"
#include <cpr/cpr.h>
#include "json.hpp"

using json = nlohmann::json;

/*
time = Time();
index = graph.getIndex("50000");
bob = time.elapsed();
cout<<bob*pow(10,3)<<"ms"<<endl;
*/

void startTestFunctions(){
    bool graphTestsSuccess = startAllGraphTests();
    bool bellmanFordTestsSuccess = startAllBellmanFordTests();

    if(graphTestsSuccess && bellmanFordTestsSuccess){
        cout<<endl<<"[TESTS RESULTS] All tests passed successfully !!!"<<endl;
    }
    else if(!graphTestsSuccess && bellmanFordTestsSuccess){
        cout<<endl<<"[TESTS RESULTS] BellmanFord tests VALID but Graph tests FAILED !!!"<<endl;
    }
    else if(graphTestsSuccess){
        cout<<endl<<"[TESTS RESULTS] Graph tests VALID but BellmanFord tests FAILED !!!"<<endl;
    }
    else{
        cout<<endl<<"[TESTS RESULTS] Both tests FAILED !!!"<<endl;
    }
}

void startBotOnKucoin(){

    //We create our graph
    Graph graphKucoin = Graph();

    //Link to the kucoin API
    const char * apiLink = "https://api.kucoin.com/api/v1/symbols";

    //We get the full list of symbols
    json jsonAllSymbols = getApiData(apiLink);

    //We get the attribute data that contains the symbols list
    auto J_data = jsonAllSymbols["data"];

    graphKucoin.fillTickersWithKucoin(J_data);

    //We create the full adjacency matrix for the corresponding vertices
    graphKucoin.initializeAdjacencyMatrix();

    Time time = Time();

    for(int i=0; i<10; i++) {
        graphKucoin.updateMatrixWithKucoin();
        graphKucoin.bellmanFord(graphKucoin.getIndex("USDT"));
        graphKucoin.detectNegativeCycle();
    }

    double timeElapsed = time.elapsed();
    cout<<"Average time required to fetch data and run bellmanFord : "<<timeElapsed*pow(10,3)/10.0<<"ms"<<endl;
}

int main() {

    //startTestFunctions();
    startBotOnKucoin();
    return EXIT_SUCCESS;
}