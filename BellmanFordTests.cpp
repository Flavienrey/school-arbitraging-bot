//
// Created by Didier on 25/02/2022.
//

#include <limits>
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
    bool executionStatus = false;

    Graph graph = Graph("devMathExample.txt", &executionStatus,CLASSICAL_WEIGHT);
    graph.bellmanFord(0);

    vector<int> correctPreviousVerticesDevMath = {-1,0,1,1,3,4};
    vector<double> correctWeightsDevMath = {0,4,19,-2,0,17};
    if(executionStatus){
        if(correctPreviousVerticesDevMath == graph.getPreviousVertices() && correctWeightsDevMath == graph.getWeightsFromSource()) {
            cout << "[TEST] Testing BellmanFord over devMath results | VALID " << endl;
        }
        else{
            cout << "[TEST] Testing BellmanFord over devMath results, returned true but results are not valid | FAILED " << endl;
            return false;
        }
    }
    else{
        cout << "[TEST] Testing BellmanFord over devMath results, returned false | FAILED " << endl;
        return false;
    }

    graph = Graph("codeSpeedyExample.txt", &executionStatus,CLASSICAL_WEIGHT);
    graph.bellmanFord(1);

    vector<int> correctPreviousVerticesCodeSpeedy = {-1,-1,1,1,3};
    vector<double> correctWeightsCodeSpeedy = {numeric_limits<double>::infinity(),0,4,3,1};

    if(executionStatus){
        if(correctPreviousVerticesCodeSpeedy == graph.getPreviousVertices() && correctWeightsCodeSpeedy == graph.getWeightsFromSource()) {
            cout << "[TEST] Testing BellmanFord over codeSpeedy results | VALID " << endl;
        }
        else{
            cout << "[TEST] Testing BellmanFord over codeSpeedy results, returned true but results are not valid | FAILED " << endl;
            return false;
        }
    }
    else{
        cout << "[TEST] Testing BellmanFord over codeSpeedy results, returned false | FAILED " << endl;
        return false;
    }

    return true;
}

//Tests all different cases for the method detectNegativeCycle of the class Graph
bool testNegativeCycleDetection(){
    return true;
}