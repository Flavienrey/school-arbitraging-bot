
#include "Graph.hpp"

int main() {
    bool* booleen;
    Graph graph = Graph("3cryptos.txt",booleen);
    graph.setTicker(0,"BTC");
    graph.setTicker(1,"USDT");
    graph.setTicker(2,"ETH");
    graph.printGraph();
    return 0;
}
