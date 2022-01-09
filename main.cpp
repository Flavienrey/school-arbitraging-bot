#include <iostream>
#include "Graph.hpp"

int main() {
    bool* boool;
    Graph test = Graph("3cryptos.txt",boool);
    printf("débug %d\n",boool);
    test.printGraph();
    return 0;
}
