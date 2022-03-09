#include "httpGetFunctions.hpp"
#include <exception>
#include "Graph.hpp"
#include "GraphTests.hpp"
#include "BellmanFordTests.hpp"
#include "Time.hpp"
#include <cpr/cpr.h>
#include "json.hpp"

int main() {



    Graph G_test = Graph();
    auto apilien = "https://api.kucoin.com/api/v1/symbols";
    json j_complete = getapidata(apilien);
    auto J_data = j_complete["data"];
    G_test.fillTickersWithKucoin(J_data);
    //std::cout << G_test.associatedTickersList.size();
    G_test.initializeAdjacencyMatrix();


    Time time = Time();
    for(int i=0; i<10; i++) {

        G_test.fillMatriceWithKucoin();
        G_test.bellmanFord(G_test.getIndexFromTicker("USDT"));
        G_test.detectNegativeCycle();
    }
    double bob = time.elapsed();
    cout<<bob*pow(10,3)<<"ms"<<endl;

    /*bool boolean = false;

    bool tests = true;
    if (tests) {
        boolean = startAllGraphTests();
        boolean = startAllBellmanFordTests();
    } else {
        try {
            //Graph graph = Graph("arbitrage3Cryptos.txt", &boolean);
            Graph graph = Graph("3cryptos.txt", &boolean);
            //Graph graph = Graph("devMathExample.txt", &boolean);
            //Graph graph = Graph("codeSpeedyExample.txt", &boolean);
            //Graph graph = Graph("full6Vertices.txt", &boolean);

            if (!boolean) {
                cout << "[Error] Error while instantiating the class, please check the logs" << endl;
            } else {

                int index = graph.getIndexFromTicker("ETH");

                Time time = Time();
                for(int i=0; i<10; i++) {
                    graph.bellmanFord(0);
                }
                double bob = time.elapsed();
                //cout<<bob*pow(10,3)<<"ms"<<endl;


                for(int i=0;i<1000;i++){
                    graph.addTicker(to_string(i));
                }

                time = Time();
                index = graph.getIndexFromTicker("50000");
                bob = time.elapsed();
                cout<<bob*pow(10,3)<<"ms"<<endl;


                graph.detectNegativeCycle();
            }
        }
        catch (exception &e) {
            cout << "Standard exception: " << e.what() << endl;
        }
    }

*/
    return EXIT_SUCCESS;
}
