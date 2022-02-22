
#include "Graph.hpp"
#include <exception>
#include "GraphTests.hpp"

int main() {
    bool booleen = false;
    bool tests = true;

    if(tests){
        startAllTests();
    }
    else {
        try {
            Graph graph = Graph("3cryptos.txt", &booleen);
            if (!booleen) {
                cout << "[Error] Error while instanciating the class, please check the logs" << endl;
            } else {
                graph.setTicker(0, "BTC");
                graph.setTicker(1, "USDT");
                graph.setTicker(2, "ETH");
                graph.printGraph();
            }

        }

        catch (exception &e) {
            cout << "Standard exception: " << e.what() << endl;
        }
    }


    return EXIT_SUCCESS;
}
