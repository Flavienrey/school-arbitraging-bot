//
// Created by Didier on 09/03/2022.
//

#include "httpGetFunctions.hpp"

// Returns the json of the HTTP request based on the api link provided
json getApiData(const char* apiLink) {

    //Get HTTP request on the api link
    cpr::Response r = cpr::Get(cpr::Url{apiLink},cpr::VerifySsl(false));

    //If the request turns out to be valid
    if (r.status_code == 200) {

        //We parse then returns the request on the json format
        return json::parse(r.text);;
    }
    //Request not valid, we throw an error

    printf("[ERROR] Error in the HTTP request to the API \n");
    return -1;

}

json getAllSymbolsFromKucoin(){
    json listOfSymbols = getApiData("https://api.kucoin.com/api/v1/symbols");

    if(listOfSymbols != -1 ){
        return listOfSymbols["data"];
    }

    return -1;
}

json getAllSymbolsFromCEX(){
    json listOfSymbols = getApiData("http://cex.io/api/currency_limits");

    if(listOfSymbols != -1 ){
        return listOfSymbols["data"]["pairs"];
    }

    return -1;
}

//Returns a vector of vector double with ask bid and quantity
vector<vector<double>> getOrderBookFromCexIO(const string& symbol1, const string& symbol2){

    string Link = "http://cex.io/api/order_book/" +symbol1+"/"+symbol2; //set in a string the link to the api
    const char *str = Link.c_str();

    auto j_complete =getApiData(str);

    auto valeurbid = to_string(j_complete["bids"][0][0]);
    double valeurDbid = stod(valeurbid);

    auto quantibid = to_string(j_complete["bids"][0][1]);
    double quantiDbid = stod(quantibid);

    auto valeurask = to_string(j_complete["asks"][0][0]);
    auto valeurDask = stod(valeurask);

    auto quantiask = to_string(j_complete["asks"][0][1]);
    auto quantiDask = stod(quantiask);

    vector<double> Askvector;
    vector<double> Bidvector;
    Askvector.push_back(valeurDask);
    Askvector.push_back(quantiDask);
    Bidvector.push_back(valeurDbid);
    Bidvector.push_back(quantiDbid);

    vector<vector<double>> Finalvector;
    Finalvector.push_back(Askvector);
    Finalvector.push_back(Bidvector);

    return Finalvector;
}

//Returns a vector of vector double with ask bid and quantity
vector<vector<double>> getOrderBookFromKucoin(const string& symbol1, const string& symbol2){

    string Link = "http://api.kucoin.com/api/v1/market/orderbook/level2_20?symbol=" +symbol1+"-"+symbol2;
    const char *str = Link.c_str();
    auto j_complete =getApiData(str);

    auto valeurbid = to_string(j_complete["data"]["bids"][0][0]);
    valeurbid = valeurbid.substr(valeurbid.find('"')+1,valeurbid.size()-2);
    double valeurDbid = stod(valeurbid);
    auto quantibid = to_string(j_complete["data"]["bids"][0][1]);
    quantibid = quantibid.substr(quantibid.find('"')+1,quantibid.size()-2);
    double quantiDbid = stod(quantibid);

    auto valeurask = to_string(j_complete["data"]["asks"][0][0]);
    valeurask = valeurask.substr(valeurask.find('"')+1,valeurask.size()-2);
    auto valeurDask = stod(valeurask);
    auto quantiask = to_string(j_complete["data"]["asks"][0][1]);
    quantiask = quantiask.substr(quantiask.find('"')+1,quantiask.size()-2);
    auto quantiDask = stod(quantiask);

    vector<double> Askvector;
    vector<double> Bidvector;
    Askvector.push_back(valeurDask);
    Askvector.push_back(quantiDask);
    Bidvector.push_back(valeurDbid);
    Bidvector.push_back(quantiDbid);

    vector<vector<double>> Finalvector;
    Finalvector.push_back(Askvector);
    Finalvector.push_back(Bidvector);

    return Finalvector;
}

//Returns a vector of vector double with ask bid and quantity
vector<vector<double>> getOrderBookFromLaToken(const string& symbol1, const string& symbol2){

    string Link = "http://api.latoken.com/v2/book/" +symbol1+"/"+symbol2;
    const char *str = Link.c_str();
    auto j_complete =getApiData(str);

    auto bid = j_complete["bid"][0];

    auto tvaleurDbid = bid.value("cost","Error");
    double valeurDbid = stod(tvaleurDbid);

    auto quantibid = bid.value("quantity","Error");
    double quantiDbid = stod(quantibid);

    auto ask = j_complete["ask"][0];
    auto tvaleurask = ask.value("cost","Error");
    auto valeurDask = stod(tvaleurask);
    tvaleurask = ask.value("quantity","Error");
    auto quantiDask = stod(tvaleurask);

    vector<double> Askvector;
    vector<double> Bidvector;
    Askvector.push_back(valeurDask);
    Askvector.push_back(quantiDask);
    Bidvector.push_back(valeurDbid);
    Bidvector.push_back(quantiDbid);

    vector<vector<double>> Finalvector;
    Finalvector.push_back(Askvector);
    Finalvector.push_back(Bidvector);

    return Finalvector;

}