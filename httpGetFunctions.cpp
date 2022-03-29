//
// Created by Didier on 09/03/2022.
//

#include "httpGetFunctions.hpp"

json getApiData(const char* apiLink) {// renvoi un json BRUTE de n'importe quel api, en fonction de l'api il peut nécessiter une modification
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
    json PA=getApiData("https://api.kucoin.com/api/v1/symbols");// use fnct getApiData
    return PA["data"];//PA[0].value("symbol1","erreur") // to get the symbols of this output
}

json getOrderBookfromKucoin(const string& symbol)//return a Json with the Asks and Bid data
{
    string Link = "http://api.kucoin.com/api/v1/market/orderbook/level2_20?symbol=" +symbol; //set in a string the link to the api
    const char *str = Link.c_str();
    auto j_complete =getApiData(str);
    auto J_data = j_complete["data"];// json data process
    return J_data;

}

json getAllSymbolsFromCEX(){
    json PA=getApiData("http://cex.io/api/currency_limits");// use fnct getApiData
    return PA["data"]["pairs"];//PA[0].value("symbol1","erreur") // to get the symbols of this output

}

vector<vector<double>> getOrderBookfromCexIO(const string& symbol1, const string& symbol2)//return a vector vector double with ask bid and quantity
{// A améliorer
    string Link = "http://cex.io/api/order_book/" +symbol1+"/"+symbol2; //set in a string the link to the api
    const char *str = Link.c_str();
    auto j_complete =getApiData(str);
    //cout << j_complete["bids"][0][0]<< endl;
    auto valeurbid = to_string(j_complete["bids"][0][0]);
    //cout << valeurbid << endl;
    double valeurDbid = stod(valeurbid);
    auto quantibid = to_string(j_complete["bids"][0][1]);
    double quantiDbid = stod(quantibid);
    auto valeurask = to_string(j_complete["asks"][0][0]);
    auto valeurDask = stod(valeurask);
    auto quantiask = to_string(j_complete["asks"][0][1]);
    auto quantiDask = stod(quantiask);
    vector<double> Askvector;
    vector<double> Bidvector;
    //Askvector.push_back(vector<double>);
    Askvector.push_back(valeurDask);
    Askvector.push_back(quantiDask);
    Bidvector.push_back(valeurDbid);
    Bidvector.push_back(quantiDbid);
    vector<vector<double>> Finalvector;
    Finalvector.push_back(Askvector);
    Finalvector.push_back(Bidvector);
    return Finalvector;

}