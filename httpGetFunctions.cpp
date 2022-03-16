//
// Created by Didier on 09/03/2022.
//

#include "httpGetFunctions.hpp"

json getApiData(const char* apiLink) {// renvoi un json BRUTE de n'importe quel api, en fonction de l'api il peut nécessiter une modification
    json j_complete;
    cpr::Response r = cpr::Get(cpr::Url{apiLink},cpr::VerifySsl(false));//requete get sur le lien "apilink"
    std::cout << "Status code: " << r.status_code << '\n';//affiche le Status code
    if (r.status_code == 200) { //200 correspond a une réponse valide de l'api
        j_complete = json::parse(r.text);// parse puis retourne un json

        return j_complete;
    }
    else {
        printf("erreur dans l'appel de l'api");
        return 0;
    }
}
json getOrderBookfromkucoin(const string& symbol)//return a Json with the Asks and Bid data
{
    string Link = "http://api.kucoin.com/api/v1/market/orderbook/level2_20?symbol=" +symbol; //set in a string the link to the api
    const char *str = Link.c_str();
    auto j_complete =getApiData(str);
    auto J_data = j_complete["data"];// json data process
    return J_data;

}

json getAllSymbolsFromCEX(){
    json PA=getApiData("http://cex.io/api/currency_limits");// use fnct getApiData
    PA = PA["data"]["pairs"];//PA[0].value("symbol1","erreur") // to get the symbols of this output
    return PA;
}
double getOrderPricefromCEX(const string& symbol1, const string& symbol2)//return a Json with the Asks and Bid data
{
    string Link = "https://cex.io/api/last_price/" +symbol1+"/"+symbol2; //set in a string the link to the api
    const char *str = Link.c_str();
    auto j_complete =getApiData(str);
    cout << j_complete["lprice"]<< endl;
    auto valeurS = to_string(j_complete["lprice"]);
    valeurS = valeurS.substr (1,valeurS.size()-1);
    valeurS = valeurS.substr (0,valeurS.size()-1);
    double valeurD = stod(valeurS);
    return valeurD;

}