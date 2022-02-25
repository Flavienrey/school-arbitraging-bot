
#include "Graph.hpp"
#include <exception>
#include "GraphTests.hpp"


int main() {
    bool boolean = false;
    bool tests = false;

    if (tests) {
        boolean = startAllTests();
    } else {
        try {
            //Graph graph = Graph("arbitrage3Cryptos.txt", &booleen);
            Graph graph = Graph("3cryptos.txt", &boolean);
            //Graph graph = Graph("devMathExample.txt", &booleen);
            //Graph graph = Graph("codeSpeedyExample.txt", &booleen);
            if (!boolean) {
                cout << "[Error] Error while instantiating the class, please check the logs" << endl;
            } else {
                graph.setTicker(0, "BTC");
                graph.setTicker(1, "USDT");
                graph.setTicker(2, "ETH");
                graph.printGraph();

                graph.bellmanFord(0);
                graph.detectNegativeCycle();

            }

        }

        catch (exception &e) {
            cout << "Standard exception: " << e.what() << endl;
        }
    }


    return EXIT_SUCCESS;
}
