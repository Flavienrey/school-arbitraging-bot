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

    cout<<endl<<"---Testing setWeight function---"<<endl<<endl;
    successStatus = testSetWeight();
    if(!successStatus) {
        cout<<"SetWeight function tests failed, please check what's wrong"<<endl;
        cout<<endl<<"[TEST] Some tests failed, please check !"<<endl;
        return false;
    }
    else{
        cout<<endl<<"SetWeight function tests successful"<<endl;
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

    //Should be a success
    Graph newGraph =  Graph("3cryptos.txt",&executionStatus);

    if(executionStatus){
        cout<<"[TEST] Instantiating test with 3 cryptos | VALID "<<endl;
    }
    else{
        cout<<"[TEST] Instantiating test with 3 cryptos | FAILED "<<endl;
        return false;
    }

    newGraph =  Graph("emptyGraph.txt",&executionStatus);

    if(executionStatus){
        cout<<"[TEST] Instantiating test with an empty graph (0 edges) | VALID "<<endl;
    }
    else{
        cout<<"[TEST] Instantiating test with an empty graph (0 edges) | FAILED "<<endl;
        return false;
    }

    //Should fail to be a valid test
    newGraph =  Graph("bob.txt",&executionStatus);

    if(!executionStatus){
        cout<<"[TEST] Instantiating test with a wrong filename, should get an error message | VALID "<<endl;
    }
    else{
        cout<<"[TEST] Instantiating test with a wrong filename, should get an error message | FAILED "<<endl;
        return false;
    }

    return true;
}


bool testSetWeight(){
    bool executionStatus;

    Graph newGraph =  Graph("emptyGraph.txt",&executionStatus);

    executionStatus = newGraph.setWeight(0,1,10);
    if(executionStatus){
        if(newGraph.getAdjacencyMatrix()[0][1]==10){
            cout<<"[TEST] Adding a valid edge to the graph, weight changed | VALID "<<endl;
        }
        else{
            cout<<"[TEST] Adding a valid edge to the graph, weight not changed | FAILED "<<endl;
        }
    }
    else{
        cout<<"[TEST] Adding a valid edge to the graph | FAILED "<<endl;
        return false;
    }

    executionStatus = newGraph.setWeight(1,1,10);
    if(!executionStatus){
        if(newGraph.getAdjacencyMatrix()[1][1]==0){
            cout<<"[TEST] Adding an edge looping on a vertice, should drop an error | VALID "<<endl;
        }
        else{
            cout<<"[TEST] Adding an edge looping on a vertice, edge value changed where it shouldn't | FAILED "<<endl;
        }
    }
    else{
        cout<<"[TEST] Adding an edge looping on a vertice, should drop an error | FAILED "<<endl;
        return false;
    }

    executionStatus = newGraph.setWeight(0,1,0);
    if(!executionStatus){
        if(newGraph.getAdjacencyMatrix()[0][1]!=0){
            cout<<"[TEST] Adding a weight of 0 on an edge, should drop an error, edge value unchanged | VALID "<<endl;
        }
        else{
            cout<<"[TEST] Adding a weight of 0, should drop an error, edge value changed | FAILED "<<endl;
        }
    }
    else{
        cout<<"[TEST] Adding a weight of 0 on an edge, should drop an error | FAILED "<<endl;
        return false;
    }

    executionStatus = newGraph.setWeight(-1,1,5);
    if(!executionStatus){
        cout<<"[TEST] Adding an edge with a negative index on first vertice, should drop an error | VALID "<<endl;
    }
    else{
        cout<<"[TEST] Adding an edge with a negative index on first vertice, should drop an error | FAILED "<<endl;
        return false;
    }

    executionStatus = newGraph.setWeight(1,-1,5);
    if(!executionStatus){
        cout<<"[TEST] Adding an edge with a negative index on second vertice, should drop an error | VALID "<<endl;
    }
    else{
        cout<<"[TEST] Adding an edge with a negative index on second vertice, should drop an error | FAILED "<<endl;
        return false;
    }

    executionStatus = newGraph.setWeight(66,1,5);
    if(!executionStatus){
        cout<<"[TEST] Adding an edge with an out-of-range index on the first vertice, should drop an error | VALID "<<endl;
    }
    else{
        cout<<"[TEST] Adding an edge with a negative index on the first vertice, should drop an error | FAILED "<<endl;
        return false;
    }

    executionStatus = newGraph.setWeight(1,66,5);
    if(!executionStatus){
        cout<<"[TEST] Adding an edge with an out-of-range index on the second vertice, should drop an error | VALID "<<endl;
    }
    else{
        cout<<"[TEST] Adding an edge with a negative index on the second vertice, should drop an error | FAILED "<<endl;
        return false;
    }

    return true;
}


bool testSetTicker(){

    bool executionStatus;

    Graph newGraph =  Graph("3cryptos.txt",&executionStatus);

    //Should work
    executionStatus = newGraph.setTicker(0,"BTC");
    if(executionStatus){
        cout<<"[TEST] Setting the ticker's name of index 0 | VALID "<<endl;
    }
    else{
        cout<<"[TEST] Setting the ticker's name of index 0 | FAILED "<<endl;
        return false;
    }

    executionStatus = newGraph.setTicker(-1,"BTC");
    if(!executionStatus){
        cout<<"[TEST] Setting the ticker's name of negative index, should drop an error | VALID "<<endl;
    }
    else{
        cout<<"[TEST] Setting the ticker's name of negative index, should drop an error | FAILED "<<endl;
        return false;
    }

    executionStatus = newGraph.setTicker(66,"BTC");
    if(!executionStatus){
        cout<<"[TEST] Setting the ticker's name of out-of-range index, should drop an error | VALID "<<endl;
    }
    else{
        cout<<"[TEST] Setting the ticker's name of out-of-range index, should drop an error | FAILED "<<endl;
        return false;
    }

    return true;
}

