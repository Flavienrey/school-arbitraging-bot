//
// Created by Didier on 22/02/2022.
//

#include "GraphTests.hpp"
#include "Graph.hpp"

bool startAllTests(){
    bool successStatus = true;

    successStatus = testGraph();
    if(!successStatus) {
        return false;
    }

    successStatus = testAddEgde();
    if(!successStatus) {
        return false;
    }

    successStatus = testSetTicker();
    if(!successStatus) {
        return false;
    }

    return true;
}

bool testGraph(){
    bool executionStatus;

    //Doit réussir
    Graph newGraph =  Graph("3cryptos.txt",&executionStatus);

    if(executionStatus){
        cout<<"[TEST] Instanciating test with 3 cryptos and a bool correct | VALID | "<<endl;
    }
    else{
        cout<<"[TEST] Instanciating test with 3 cryptos and a bool correct | ERROR | "<<endl;
        return false;
    }

    //Doit réussir
    Graph newGraph2 =  Graph("3crdazazyptos.txt",&executionStatus);

    if(!executionStatus){
        cout<<"[TEST] Instanciating test with 3 cryptos and a bool correct | VALID | "<<endl;
    }
    else{
        cout<<"[TEST] Instanciating test with 3 cryptos and a bool correct | ERROR | "<<endl;
        return false;
    }

    return true;
}

bool testAddEgde(){
    return false;
}


bool testSetTicker(){
    return false;
}