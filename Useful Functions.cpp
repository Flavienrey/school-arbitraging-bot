//
// Created by Didier on 28/03/2022.
//

#include <fstream>
#include "Time.hpp"
#include "Useful Functions.hpp"

bool writeOpportunitiesInCSV(const string& filename, const string& exchange, const string& bestRoute, double opportunitySize, double percentage) {

    ofstream outputFile("./Opportunities/"+filename, ios::out | ios::app);

    //If the file is correctly opened
    if(outputFile){
        //We save our data
        outputFile<<exchange<<";"<<bestRoute<<";"<<opportunitySize<<";"<<percentage<<";"<<Time::getCurrentDate()<<";"<<Time::getCurrentTime()<<";"<<endl;
        outputFile.close();
    }

    return true;
}

bool createColumnTitlesInCSV(const string &filename) {
    ofstream outputFile("./Opportunities/"+filename, ios::out | ios::app);

    //If the file is correctly opened
    if(outputFile) {
        outputFile << "Exchange;Route;Opportunity Size;Percentage without fees;Date;Time;\n";
        outputFile.close();
    }

    return true;
}
