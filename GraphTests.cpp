//
// Created by Didier on 22/02/2022.
//

#include "GraphTests.hpp"
#include "Graph.hpp"

bool startAllTests(){
    bool successStatus = true;

    cout<<endl<<"[TEST] Beginning of the tests"<<endl<<endl;
    cout<<"---Testing graph constructor---"<<endl<<endl;
    successStatus = testGraph();
    if(!successStatus) {
        cout<<"Graph constructor tests failed, please check what's wrong"<<endl;
        cout<<endl<<"[TEST] Some tests failed, please check !"<<endl;
        return false;
    }
    else{
        cout<<endl<<"Graph constructor tests successful"<<endl;
    }

    cout<<endl<<"---Testing addEdge function---"<<endl;
    successStatus = testAddEgde();
    if(!successStatus) {
        cout<<"addEdge function tests failed, please check what's wrong"<<endl;
        cout<<endl<<"[TEST] Some tests failed, please check !"<<endl;
        return false;
    }
    else{
        cout<<endl<<"AddEdge function tests successful"<<endl;
    }

    cout<<endl<<"---Testing setTicker setter---"<<endl<<endl;
    successStatus = testSetTicker();
    if(!successStatus) {
        cout<<"setTicker setter tests failed, please check what's wrong"<<endl;
        cout<<endl<<"[TEST] Some tests failed, please check !"<<endl;
        return false;
    }
    else{
        cout<<endl<<"SetTicker setter tests successful"<<endl;
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

    bool executionStatus;

    Graph newGraph =  Graph("3cryptos.txt",&executionStatus);

    //Doit réussir
    executionStatus = newGraph.setTicker(0,"BTC");
    if(executionStatus){
        cout<<"[TEST] Setting the ticker's name of index 0 | VALID "<<endl;
    }
    else{
        cout<<"[TEST] Setting the ticker's name of index 0 | ERROR "<<endl;
        return false;
    }

    executionStatus = newGraph.setTicker(-1,"BTC");
    if(!executionStatus){
        cout<<"[TEST] Setting the ticker's name of negative index, should drop an error | VALID "<<endl;
    }
    else{
        cout<<"[TEST] Setting the ticker's name of negative index, should drop an error | ERROR "<<endl;
        return false;
    }

    executionStatus = newGraph.setTicker(66,"BTC");
    if(!executionStatus){
        cout<<"[TEST] Setting the ticker's name of out-of-range index, should drop an error | VALID "<<endl;
    }
    else{
        cout<<"[TEST] Setting the ticker's name of out-of-range index, should drop an error | ERROR "<<endl;
        return false;
    }

    return true;
}