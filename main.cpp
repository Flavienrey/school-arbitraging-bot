#include <iostream>
#include "Graph.hpp"

int main() {
    bool* booleen;
    Graph graph = Graph("3cryptos.txt",booleen);
    graph.printGraph();
    return 0;
}
