//
// Created by Didier on 22/02/2022.
//

#include "GraphTests.hpp"
#include "Graph.hpp"

bool startAllTests(){
    bool successStatus = true;

    cout<<endl<<"---[TEST] Beginning of the tests---"<<endl;
    cout<<"---Testing graph constructor---"<<endl;
    successStatus = testGraph();
    if(!successStatus) {
        cout<<"Graph constructor tests failed, please check what's wrong"<<endl;
        cout<<endl<<"[TEST] Some tests failed, please check !"<<endl;
        return false;
    }
    else{
        cout<<"Graph constructor tests successful | VALID"<<endl;
    }

    cout<<endl<<"---Testing addEdge function---"<<endl;
    successStatus = testAddEgde();
    if(!successStatus) {
        cout<<"addEdge function tests failed, please check what's wrong"<<endl;
        cout<<endl<<"[TEST] Some tests failed, please check !"<<endl;
        return false;
    }
    else{
        cout<<"addEdge function tests successful | VALID"<<endl;
    }

    cout<<endl<<"---Testing setTicker setter---"<<endl;
    successStatus = testSetTicker();
    if(!successStatus) {
        cout<<"setTicker setter tests failed, please check what's wrong"<<endl;
        cout<<endl<<"[TEST] Some tests failed, please check !"<<endl;
        return false;
    }
    else{
        cout<<"setTicker setter tests successful | VALID"<<endl;
    }

    cout<<endl<<"[TEST] All tests passed successfully, well done master !"<<endl;
    return true;
}

bool testGraph(){
    bool executionStatus;

    //Doit réussir
    Graph newGraph =  Graph("3cryptos.txt",&executionStatus);

    if(executionStatus){
        cout<<"[TEST] Instanciating test with 3 cryptos and a bool correct | VALID "<<endl;
    }
    else{
        cout<<"[TEST] Instanciating test with 3 cryptos and a bool correct | ERROR "<<endl;
        return false;
    }

    //Doit échouer pour return true car fichier inexistant
    Graph newGraph2 =  Graph("3crdazazyptos.txt",&executionStatus);

    if(!executionStatus){
        cout<<"[TEST] Instanciating test with a wrong filename, should get an error message | VALID "<<endl;
    }
    else{
        cout<<"[TEST] Instanciating test with a wrong filename, should get an error message | ERROR "<<endl;
        return false;
    }

    return true;
}

bool testAddEgde(){
    return true;
}


bool testSetTicker(){
    return true;
}