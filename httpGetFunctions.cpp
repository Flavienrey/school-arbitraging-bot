//
// Created by Didier on 09/03/2022.
//

#include "httpGetFunctions.hpp"

//Renvoie un json BRUT de n'importe quel api, en fonction de l'api il peut nécessiter une modification
json getApiData(const char* apiLink) {
    json j_complete;
    cpr::Response r = cpr::Get(cpr::Url{apiLink},cpr::VerifySsl(false));//requete get sur le lien "apilink"
    //std::cout << "Status code: " << r.status_code << '\n';//affiche le Status code
    if (r.status_code == 200) { //200 correspond a une réponse valide de l'api
        j_complete = json::parse(r.text);// parse puis retourne un json

        return j_complete;
    }
    else {
        printf("erreur dans l'appel de l'api");
        return 0;
    }
}

json getAllSymbolsFromKucoin(){

    //Uses the function getApiData
    json PA=getApiData("https://api.kucoin.com/api/v1/symbols");

    return PA["data"];
}

//Returns a Json with the Asks and Bid data
json getOrderBookfromKucoin(const string& symbol){

    string Link = "http://api.kucoin.com/api/v1/market/orderbook/level2_20?symbol=" +symbol; //set in a string the link to the api
    const char *str = Link.c_str();
    auto j_complete =getApiData(str);
    auto J_data = j_complete["data"];// json data process

    return J_data;
}

//
json getAllSymbolsFromCEX(){
    json PA=getApiData("http://cex.io/api/currency_limits");// use fnct getApiData

    return PA["data"]["pairs"];
}

vector<vector<double>> getOrderBookfromCexIO(const string& symbol1, const string& symbol2)//return a Json with the Asks and Bid data
{
    string Link = "http://cex.io/api/order_book/" +symbol1+"/"+symbol2; //set in a string the link to the api
    const char *str = Link.c_str();
    auto j_complete = getApiData(str);
    cout << j_complete["bids"][0][0]<< endl;
    auto valeurbid = to_string(j_complete["bids"][0][0]);
    cout << valeurbid << endl;
    double valeurDbid = stod(valeurbid);
    auto quantibid = to_string(j_complete["bids"][0][1]);
    double quantiDbid = stod(quantibid);
    auto valeurask = to_string(j_complete["asks"][0][0]);
    auto valeurDask = stod(valeurask);
    auto quantiask = to_string(j_complete["asks"][0][1]);
    auto quantiDask = stod(quantiask);
    vector<double> retour;
    vector<double> retourr;

    //retour.push_back(vector<double>);
    retour.push_back(valeurDask);
    retour.push_back(quantiDask);
    retourr.push_back(valeurDbid);
    retourr.push_back(quantiDbid);

    vector<vector<double>> retourF;
    retourF.push_back(retour);
    retourF.push_back(retourr);

    return retourF;
}