#include "httpGetFunctions.hpp"
#include "Graph.hpp"
#include "GraphTests.hpp"
#include "BellmanFordTests.hpp"
#include "Time.hpp"
#include "json.hpp"
#include "Useful Functions.hpp"

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

void runXTimesBotOnKucoin(){

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
        if(weight!=-1) {
            graphKucoin.displayRouteAndPercentage(weight);
        }
        totalTimeForDetectNegativeCycle+=time.elapsed();

        //_________________________________________________________________________
        time.reset();
        graphKucoin.bellmanFord(graphKucoin.getIndex("USDC"));
        totalTimeBellmanFord+=time.elapsed();

        time.reset();
        weight = graphKucoin.findAndReturnWeightOfBestRoute();
        if(weight!=-1) {
            graphKucoin.displayRouteAndPercentage(weight);
        }
        totalTimeForDetectNegativeCycle+=time.elapsed();

        //_________________________________________________________________________
        time.reset();
        graphKucoin.bellmanFord(graphKucoin.getIndex("BTC"));
        totalTimeBellmanFord+=time.elapsed();

        time.reset();
        weight = graphKucoin.findAndReturnWeightOfBestRoute();
        if(weight!=-1) {
            graphKucoin.displayRouteAndPercentage(weight);
        }
        totalTimeForDetectNegativeCycle+=time.elapsed();
    }

    cout<<endl<<"Average time required to update matrix : "<<(totalTimeForUpdateMatrix/numberOfTestsIterations)*pow(10,3)<<"ms"<<endl;
    cout<<"Average time required to run bellmanFord : "<<(totalTimeBellmanFord/3/numberOfTestsIterations)*pow(10,3)<<"ms"<<endl;
    cout<<"Average time required to detect negative cycle : "<<(totalTimeForDetectNegativeCycle/3/numberOfTestsIterations)*pow(10,3)<<"ms"<<endl;
    cout<<"Total time required to execute everything : "<<((totalTimeForDetectNegativeCycle/3+totalTimeBellmanFord/3+totalTimeForUpdateMatrix)/numberOfTestsIterations)*pow(10,3)<<"ms"<<endl;

}

void runXTimesBotOnCex(){

    //We create our graph
    Graph graphCexIO = Graph();

    //We get the attribute data that contains the symbols list
    auto J_data = getAllSymbolsFromCEX();

    graphCexIO.fillTickersWithCexIO(J_data);

    double totalTimeForUpdateMatrix = 0.0;
    double totalTimeBellmanFord = 0.0;
    double totalTimeForDetectNegativeCycle = 0.0;

    Time time = Time();

    int numberOfTestsIterations = 1;
    for(int i=0; i<numberOfTestsIterations; i++) {

        time.reset();
        graphCexIO.updateAdjacencyListWithCexIO();
        totalTimeForUpdateMatrix+=time.elapsed();

        //_________________________________________________________________________
        time.reset();
        graphCexIO.bellmanFord(graphCexIO.getIndex("USD"));
        totalTimeBellmanFord+=time.elapsed();

        time.reset();
        double weight = graphCexIO.findAndReturnWeightOfBestRoute();
        if(weight!=-1) {
            graphCexIO.displayRouteAndPercentage(weight);
        }
        totalTimeForDetectNegativeCycle+=time.elapsed();

        //_________________________________________________________________________
        time.reset();
        graphCexIO.bellmanFord(graphCexIO.getIndex("BTC"));
        totalTimeBellmanFord+=time.elapsed();

        time.reset();
        weight = graphCexIO.findAndReturnWeightOfBestRoute();
        if(weight!=-1) {
            graphCexIO.displayRouteAndPercentage(weight);
        }
        totalTimeForDetectNegativeCycle+=time.elapsed();
    }

    cout<<endl<<"Average time required to update matrix : "<<(totalTimeForUpdateMatrix/numberOfTestsIterations)*pow(10,3)<<"ms"<<endl;
    cout<<"Average time required to run bellmanFord : "<<(totalTimeBellmanFord/2/numberOfTestsIterations)*pow(10,3)<<"ms"<<endl;
    cout<<"Average time required to detect negative cycle : "<<(totalTimeForDetectNegativeCycle/2/numberOfTestsIterations)*pow(10,3)<<"ms"<<endl;
    cout<<"Total time required to detect negative cycle : "<<((totalTimeForDetectNegativeCycle/2+totalTimeBellmanFord/2+totalTimeForUpdateMatrix)/numberOfTestsIterations)*pow(10,3)<<"ms"<<endl;

}

[[noreturn]] void runBotOnKucoin(const string& filename){

    //We create our graph
    Graph graphKucoin = Graph();

    //We get the attribute data that contains the symbols list
    auto J_data = getAllSymbolsFromKucoin();

    graphKucoin.fillTickersWithKucoin(J_data);

    while(true) {

        graphKucoin.updateAdjacencyListWithKucoin();

        //_________________________________________________________________________
        graphKucoin.bellmanFord(graphKucoin.getIndex("USDT"));

        double weight = graphKucoin.findAndReturnWeightOfBestRoute();
        double percentage = 0;
        if(weight!=-1) {
            percentage = graphKucoin.displayRouteAndPercentage(weight);
            writeOpportunitiesInCSV(filename,"Kucoin",graphKucoin.convertIntRouteToStringRoute(),0,percentage);
        }

        //_________________________________________________________________________
        graphKucoin.bellmanFord(graphKucoin.getIndex("USDC"));

        weight = graphKucoin.findAndReturnWeightOfBestRoute();
        if(weight!=-1) {
            percentage = graphKucoin.displayRouteAndPercentage(weight);
            writeOpportunitiesInCSV(filename,"Kucoin",graphKucoin.convertIntRouteToStringRoute(),0,percentage);
        }

        //_________________________________________________________________________
        graphKucoin.bellmanFord(graphKucoin.getIndex("BTC"));

        weight = graphKucoin.findAndReturnWeightOfBestRoute();
        if(weight!=-1) {
            percentage = graphKucoin.displayRouteAndPercentage(weight);
            writeOpportunitiesInCSV(filename,"Kucoin",graphKucoin.convertIntRouteToStringRoute(),0,percentage);
        }

    }
}

[[noreturn]] void runBotOnCex(const string& filename){

    //We create our graph
    Graph graphCexIO = Graph();

    //We get the attribute data that contains the symbols list
    auto J_data = getAllSymbolsFromCEX();

    graphCexIO.fillTickersWithCexIO(J_data);

    while(true) {

        graphCexIO.updateAdjacencyListWithCexIO();

        //_________________________________________________________________________
        graphCexIO.bellmanFord(graphCexIO.getIndex("USD"));

        double weight = graphCexIO.findAndReturnWeightOfBestRoute();
        double percentage = 0;
        if(weight!=-1) {
            percentage = graphCexIO.displayRouteAndPercentage(weight);
            writeOpportunitiesInCSV(filename,"Cex.io",graphCexIO.convertIntRouteToStringRoute(),0,percentage);
        }


        //_________________________________________________________________________
        graphCexIO.bellmanFord(graphCexIO.getIndex("BTC"));

        weight = graphCexIO.findAndReturnWeightOfBestRoute();

        if(weight!=-1) {
            percentage = graphCexIO.displayRouteAndPercentage(weight);
            writeOpportunitiesInCSV(filename,"Cex.io",graphCexIO.convertIntRouteToStringRoute(),0,percentage);
        }

    }
}

[[noreturn]] void runBotOnAllPlatforms(const string& filename){

    //We create our graph
    Graph graphKucoin = Graph();
    //We get the attribute data that contains the symbols list
    auto J_data_kucoin = getAllSymbolsFromKucoin();
    graphKucoin.fillTickersWithKucoin(J_data_kucoin);

    //We create our graph
    Graph graphCexIO = Graph();
    //We get the attribute data that contains the symbols list
    auto J_data_cex = getAllSymbolsFromCEX();
    graphCexIO.fillTickersWithCexIO(J_data_cex);


    while(true) {

        graphKucoin.updateAdjacencyListWithKucoin();

        //_________________________________________________________________________
        graphKucoin.bellmanFord(graphKucoin.getIndex("USDT"));

        double weight = graphKucoin.findAndReturnWeightOfBestRoute();
        double percentage = 0;
        if(weight!=-1) {
            percentage = graphKucoin.displayRouteAndPercentage(weight);
            writeOpportunitiesInCSV(filename,"Kucoin",graphKucoin.convertIntRouteToStringRoute(),0,percentage);
        }

        //_________________________________________________________________________
        graphKucoin.bellmanFord(graphKucoin.getIndex("USDC"));

        weight = graphKucoin.findAndReturnWeightOfBestRoute();
        if(weight!=-1) {
            percentage = graphKucoin.displayRouteAndPercentage(weight);
            writeOpportunitiesInCSV(filename,"Kucoin",graphKucoin.convertIntRouteToStringRoute(),0,percentage);
        }

        //_________________________________________________________________________
        graphKucoin.bellmanFord(graphKucoin.getIndex("BTC"));

        weight = graphKucoin.findAndReturnWeightOfBestRoute();
        if(weight!=-1) {
            percentage = graphKucoin.displayRouteAndPercentage(weight);
            writeOpportunitiesInCSV(filename,"Kucoin",graphKucoin.convertIntRouteToStringRoute(),0,percentage);
        }


        graphCexIO.updateAdjacencyListWithCexIO();

        //_________________________________________________________________________
        graphCexIO.bellmanFord(graphCexIO.getIndex("USD"));

        weight = graphCexIO.findAndReturnWeightOfBestRoute();
        percentage=0;
        if(weight!=-1) {
            percentage = graphCexIO.displayRouteAndPercentage(weight);
            writeOpportunitiesInCSV(filename,"Cex.io",graphCexIO.convertIntRouteToStringRoute(),0,percentage);
        }

        //_________________________________________________________________________
        graphCexIO.bellmanFord(graphCexIO.getIndex("BTC"));

        weight = graphCexIO.findAndReturnWeightOfBestRoute();

        if(weight!=-1) {
            percentage = graphCexIO.displayRouteAndPercentage(weight);
            writeOpportunitiesInCSV(filename,"Cex.io",graphCexIO.convertIntRouteToStringRoute(),0,percentage);
        }

    }
}

int main(int argc, char** argv) {

    bool implementationValid = startTestFunctions();

    string filename = "FirstBatch.csv";

    cout << endl << "Program started at : " << Time::getCurrentDateAndTime() << endl;

    if(implementationValid && argc>1){
        if(strcmp(argv[1],"instantiateFile") == 0 || strcmp(argv[1],"initializeFile") == 0){
            createColumnTitlesInCSV(filename);
        }
        else if(strcmp(argv[1],"kucoin") == 0){
            runBotOnKucoin(filename);
        }
        else if(strcmp(argv[1],"cex") == 0){
            runBotOnCex(filename);
        }
        else if(strcmp(argv[1],"all") == 0){
            runBotOnAllPlatforms(filename);
        }
        else {
            runXTimesBotOnKucoin();
            runXTimesBotOnCex();
        }
    }



    return EXIT_SUCCESS;
}