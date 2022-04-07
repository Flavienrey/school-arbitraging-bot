#include "Graph.hpp"
#include "GraphTests.hpp"
#include "BellmanFordTests.hpp"
#include "Time.hpp"
#include "json.hpp"
#include "usefulFunctions.hpp"

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

void runXTimesBotOnKucoin(int numberOfIterations = 1){

    //We create our graph
    Graph graphKucoin = Graph();
    bool tickersGraphKucoinValid = graphKucoin.fillTickersWithKucoin();

    if(!tickersGraphKucoinValid){
        cout <<"[Error] Kucoin's tickers not filled properly"<<endl;
    }



    double totalTimeForUpdateMatrix = 0.0;
    double totalTimeBellmanFord = 0.0;
    double totalTimeForDetectNegativeCycle = 0.0;

    Time time = Time();

    for(int i=0; i<numberOfIterations; i++) {

        time.reset();
        bool executionStatus = graphKucoin.updateAdjacencyListWithKucoin();
        totalTimeForUpdateMatrix+=time.elapsed();

        if(executionStatus) {
            //_________________________________________________________________________
            time.reset();
            graphKucoin.bellmanFord(graphKucoin.getIndex("USDT"));
            totalTimeBellmanFord += time.elapsed();

            time.reset();
            double weight = graphKucoin.findAndReturnWeightOfBestRoute();
            if (weight != -1) {
                graphKucoin.displayRouteAndPercentage(weight, "Kucoin");
            }
            totalTimeForDetectNegativeCycle += time.elapsed();
        }
    }

    cout<<endl<<"Average time required to update matrix : "<<(totalTimeForUpdateMatrix/numberOfIterations)*pow(10,3)<<"ms"<<endl;
    cout<<"Average time required to run bellmanFord : "<<(totalTimeBellmanFord/numberOfIterations)*pow(10,3)<<"ms"<<endl;
    cout<<"Average time required to detect negative cycle : "<<(totalTimeForDetectNegativeCycle/numberOfIterations)*pow(10,3)<<"ms"<<endl;
    cout<<"Total time required to execute everything : "<<((totalTimeForDetectNegativeCycle+totalTimeBellmanFord+totalTimeForUpdateMatrix)/numberOfIterations)*pow(10,3)<<"ms"<<endl;

}

void runXTimesBotOnCex(int numberOfIterations = 1){

    //We create our graph
    Graph graphCexIO = Graph();
    bool tickersGraphCexValid = graphCexIO.fillTickersWithCexIO();

    if(!tickersGraphCexValid){
        cout <<"[Error] Cex.io's tickers not filled properly"<<endl;
    }

    double totalTimeForUpdateMatrix = 0.0;
    double totalTimeBellmanFord = 0.0;
    double totalTimeForDetectNegativeCycle = 0.0;

    Time time = Time();

    for(int i=0; i<numberOfIterations; i++) {

        time.reset();
        bool executionStatus = graphCexIO.updateAdjacencyListWithCexIO();
        totalTimeForUpdateMatrix += time.elapsed();

        if (executionStatus) {
            //_________________________________________________________________________
            time.reset();
            graphCexIO.bellmanFord(graphCexIO.getIndex("USD"));
            totalTimeBellmanFord += time.elapsed();

            time.reset();
            double weight = graphCexIO.findAndReturnWeightOfBestRoute();
            if (weight != -1) {
                graphCexIO.displayRouteAndPercentage(weight, "Cex.io");
            }
            totalTimeForDetectNegativeCycle += time.elapsed();
        }
    }

    cout<<endl<<"Average time required to update matrix : "<<(totalTimeForUpdateMatrix/numberOfIterations)*pow(10,3)<<"ms"<<endl;
    cout<<"Average time required to run bellmanFord : "<<(totalTimeBellmanFord/numberOfIterations)*pow(10,3)<<"ms"<<endl;
    cout<<"Average time required to detect negative cycle : "<<(totalTimeForDetectNegativeCycle/numberOfIterations)*pow(10,3)<<"ms"<<endl;
    cout<<"Total time required to detect negative cycle : "<<((totalTimeForDetectNegativeCycle+totalTimeBellmanFord+totalTimeForUpdateMatrix)/numberOfIterations)*pow(10,3)<<"ms"<<endl;

}


void runXTimesBotOnLaToken(int numberOfIterations = 1){

    //We create our graph
    Graph graphLaToken= Graph();
    bool tickersGraphLaTokenValid = graphLaToken.fillTickersWithLaToken();

    if(!tickersGraphLaTokenValid){
        cout <<"[Error] LaToken's tickers not filled properly"<<endl;
    }

    double totalTimeForUpdateMatrix = 0.0;
    double totalTimeBellmanFord = 0.0;
    double totalTimeForDetectNegativeCycle = 0.0;

    Time time = Time();

    for(int i=0; i<numberOfIterations; i++) {

        time.reset();
        bool executionStatus = graphLaToken.updateAdjacencyListWithLaToken();
        totalTimeForUpdateMatrix+=time.elapsed();

        if(executionStatus) {

            //_________________________________________________________________________
            time.reset();
            graphLaToken.bellmanFord(graphLaToken.getIndex("USDT"));
            totalTimeBellmanFord+=time.elapsed();

            time.reset();
            double weight = graphLaToken.findAndReturnWeightOfBestRoute();
            if(weight!=-1) {
                graphLaToken.displayRouteAndPercentage(weight,"LaToken");
            }
            totalTimeForDetectNegativeCycle+=time.elapsed();
        }

    }

    cout<<endl<<"Average time required to update matrix : "<<(totalTimeForUpdateMatrix/numberOfIterations)*pow(10,3)<<"ms"<<endl;
    cout<<"Average time required to run bellmanFord : "<<(totalTimeBellmanFord/numberOfIterations)*pow(10,3)<<"ms"<<endl;
    cout<<"Average time required to detect negative cycle : "<<(totalTimeForDetectNegativeCycle/numberOfIterations)*pow(10,3)<<"ms"<<endl;
    cout<<"Total time required to detect negative cycle : "<<((totalTimeForDetectNegativeCycle+totalTimeBellmanFord+totalTimeForUpdateMatrix)/numberOfIterations)*pow(10,3)<<"ms"<<endl;

}

[[noreturn]] void runBotOnKucoin(const string& filename){

    //We create our graph
    Graph graphKucoin = Graph();
    bool tickersGraphKucoinValid = graphKucoin.fillTickersWithKucoin();

    if(!tickersGraphKucoinValid){
        cout <<"[Error] Kucoin's tickers not filled properly"<<endl;
    }

    while(true) {

        bool executionStatus = graphKucoin.updateAdjacencyListWithKucoin();

        if(executionStatus) {

            //_________________________________________________________________________
            graphKucoin.bellmanFord(graphKucoin.getIndex("USDT"));

            double weight = graphKucoin.findAndReturnWeightOfBestRoute();
            double percentage = 0;
            if (weight != -1) {
                percentage = graphKucoin.displayRouteAndPercentage(weight,"Kucoin");
                writeOpportunitiesInCSV(filename, "Kucoin", graphKucoin.convertIntRouteToStringRoute(), 0, percentage);
            }
        }

    }
}

[[noreturn]] void runBotOnCex(const string& filename){

    //We create our graph
    Graph graphCexIO = Graph();
    bool tickersGraphCexValid = graphCexIO.fillTickersWithCexIO();

    if(!tickersGraphCexValid){
        cout <<"[Error] Cex.io's tickers not filled properly"<<endl;
    }

    while(true) {

        bool executionStatus = graphCexIO.updateAdjacencyListWithCexIO();

        if(executionStatus) {
            //_________________________________________________________________________
            graphCexIO.bellmanFord(graphCexIO.getIndex("USD"));

            double weight = graphCexIO.findAndReturnWeightOfBestRoute();
            double percentage = 0;
            if (weight != -1) {
                percentage = graphCexIO.displayRouteAndPercentage(weight,"Cex.io");
                writeOpportunitiesInCSV(filename, "Cex.io", graphCexIO.convertIntRouteToStringRoute(), 0, percentage);
            }
        }

    }
}

[[noreturn]] void runBotOnLaToken(const string& filename){

    //We create our graph
    Graph graphLaToken= Graph();
    bool tickersGraphLaTokenValid = graphLaToken.fillTickersWithLaToken();

    if(!tickersGraphLaTokenValid){
        cout <<"[Error] LaToken's tickers not filled properly"<<endl;
    }

    while(true) {

        bool executionStatus = graphLaToken.updateAdjacencyListWithLaToken();

        if(executionStatus) {

            //_________________________________________________________________________
            graphLaToken.bellmanFord(graphLaToken.getIndex("USDT"));

            double weight = graphLaToken.findAndReturnWeightOfBestRoute();
            double percentage = 0;
            if (weight != -1) {
                percentage = graphLaToken.displayRouteAndPercentage(weight,"LaToken");
                writeOpportunitiesInCSV(filename, "Cex.io", graphLaToken.convertIntRouteToStringRoute(), 0, percentage);
            }
        }

    }
}

[[noreturn]] void runBotOnAllPlatforms(const string& filename){

    //We create our graph
    Graph graphKucoin = Graph();
    bool tickersGraphKucoinValid = graphKucoin.fillTickersWithKucoin();

    if(!tickersGraphKucoinValid){
        cout <<"[Error] Kucoin's tickers not filled properly"<<endl;
    }

    //We create our graph
    Graph graphCexIO = Graph();
    bool tickersGraphCexValid = graphCexIO.fillTickersWithCexIO();

    if(!tickersGraphCexValid){
        cout <<"[Error] Cex.io's tickers not filled properly"<<endl;
    }

    //We create our graph
    Graph graphLaToken= Graph();
    bool tickersGraphLaTokenValid = graphLaToken.fillTickersWithLaToken();

    if(!tickersGraphLaTokenValid){
        cout <<"[Error] LaToken's tickers not filled properly"<<endl;
    }

    while(true) {

        bool executionStatus = graphKucoin.updateAdjacencyListWithKucoin();

        if(executionStatus) {
            //_________________________________________________________________________
            graphKucoin.bellmanFord(graphKucoin.getIndex("USDT"));

            double weight = graphKucoin.findAndReturnWeightOfBestRoute();
            double percentage = 0;
            if (weight != -1) {
                percentage = graphKucoin.displayRouteAndPercentage(weight,"Kucoin");
                writeOpportunitiesInCSV(filename, "Kucoin", graphKucoin.convertIntRouteToStringRoute(), 0, percentage);
            }
        }

        executionStatus = graphCexIO.updateAdjacencyListWithCexIO();

        if(executionStatus) {
            //_________________________________________________________________________
            graphCexIO.bellmanFord(graphCexIO.getIndex("USD"));

            double weight = graphCexIO.findAndReturnWeightOfBestRoute();
            double percentage = 0;
            if (weight != -1) {
                percentage = graphCexIO.displayRouteAndPercentage(weight,"Cex.io");
                writeOpportunitiesInCSV(filename, "Cex.io", graphCexIO.convertIntRouteToStringRoute(), 0, percentage);
            }
        }


        executionStatus = graphLaToken.updateAdjacencyListWithLaToken();

        if(executionStatus) {
            //_________________________________________________________________________
            graphLaToken.bellmanFord(graphLaToken.getIndex("USDT"));

            double weight = graphLaToken.findAndReturnWeightOfBestRoute();
            double percentage = 0;
            if(weight!=-1) {
                percentage = graphLaToken.displayRouteAndPercentage(weight,"LaToken");
                writeOpportunitiesInCSV(filename,"Cex.io",graphLaToken.convertIntRouteToStringRoute(),0,percentage);
            }
        }
    }

}

int main(int argc, char** argv) {

    string filename = "FirstBatch.csv";

    cout << endl << "Program started at : " << Time::getCurrentDateAndTime() << endl;

    bool implementationValid = startTestFunctions();

    if(implementationValid){
        if(argc>1){
            if(strcmp(argv[1],"instantiateFile") == 0 || strcmp(argv[1],"initializeFile") == 0 || strcmp(argv[1],"createFile") == 0){
                createColumnTitlesInCSV(filename);
            }
            else if(strcmp(argv[1],"kucoin") == 0 || strcmp(argv[1],"Kucoin") == 0 || strcmp(argv[1],"KuCoin") == 0){
                runBotOnKucoin(filename);
            }
            else if(strcmp(argv[1],"cex") == 0 || strcmp(argv[1],"Cex") == 0){
                runBotOnCex(filename);
            }
            else if(strcmp(argv[1],"laToken") == 0 || strcmp(argv[1],"LaToken") == 0){
                runBotOnLaToken(filename);
            }
            else if(strcmp(argv[1],"all") == 0){
                runBotOnAllPlatforms(filename);
            }
            else if  (strcmp(argv[1],"getAverageTime") == 0 && argc == 3) {
                runXTimesBotOnKucoin(atoi(argv[2]));
                runXTimesBotOnCex(atoi(argv[2]));
                runXTimesBotOnLaToken(atoi(argv[2]));
            }
        }
        else{
            //We run it once on each exchange
            runXTimesBotOnKucoin();
            runXTimesBotOnCex();
            runXTimesBotOnLaToken();
        }
    }

    return EXIT_SUCCESS;
}