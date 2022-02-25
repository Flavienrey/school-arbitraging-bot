
#include <exception>
#include "Graph.hpp"
#include "GraphTests.hpp"
#include "BellmanFordTests.hpp"
#include "Time.hpp"

int main() {
    bool boolean = false;

    bool tests = false;
    if (tests) {
        boolean = startAllGraphTests();
        boolean = startAllBellmanFordTests();
    } else {
        try {
            //Graph graph = Graph("arbitrage3Cryptos.txt", &boolean);
            //Graph graph = Graph("3cryptos.txt", &boolean);
            //Graph graph = Graph("devMathExample.txt", &boolean);
            //Graph graph = Graph("codeSpeedyExample.txt", &boolean);
            Graph graph = Graph("full6Vertices.txt", &boolean);

            if (!boolean) {
                cout << "[Error] Error while instantiating the class, please check the logs" << endl;
            } else {
                graph.setTicker(0, "BTC");
                graph.setTicker(1, "USDT");
                graph.setTicker(2, "ETH");

                graph.printGraph();

                Time time = Time();
                for(int i=0; i<10; i++) {
                    graph.bellmanFord(0);
                }
                double bob = time.elapsed();
                cout<<bob*pow(10,3)<<"ms"<<endl;


                graph.detectNegativeCycle();
            }
        }
        catch (exception &e) {
            cout << "Standard exception: " << e.what() << endl;
        }
    }


    return EXIT_SUCCESS;
}
