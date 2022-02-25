//
// Created by Didier on 25/02/2022.
//

#include "BellmanFordTests.hpp"
#include "Graph.hpp"

//Starts all tests and return true if the execution is successful
bool startAllBellmanFordTests(){
    bool successStatus;

    cout<<endl<<"[TEST] Beginning of the tests"<<endl<<endl;
    cout<<"---Testing bellmanFord algorithm---"<<endl<<endl;
    successStatus = testBellmanFordAlgorithm();
    if(!successStatus) {
        cout<<"bellmanFord algorithm tests failed, please check what's wrong"<<endl;
        cout<<endl<<"[TEST] Some tests failed, please check !"<<endl;
        return false;
    }
    else{
        cout<<endl<<"BellmanFord algorithm tests successful"<<endl;
    }

    cout<<endl<<"---Testing detectNegativeCycle function---"<<endl<<endl;
    successStatus = testNegativeCycleDetection();
    if(!successStatus) {
        cout<<"DetectNegativeCycle function tests failed, please check what's wrong"<<endl;
        cout<<endl<<"[TEST] Some tests failed, please check !"<<endl;
        return false;
    }
    else{
        cout<<endl<<"DetectNegativeCycle function tests successful"<<endl;
    }

    cout<<endl<<"[TEST] All tests passed successfully, well done master !"<<endl;
    return true;
}

//Tests all different cases for the method bellmanFord of the class Graph
bool testBellmanFordAlgorithm(){
    return true;
}

//Tests all different cases for the method detectNegativeCycle of the class Graph
bool testNegativeCycleDetection(){
    return true;
}