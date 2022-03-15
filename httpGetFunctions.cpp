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
json getorderbookfromkucoin(const string& symbol)//return a Json with the Asks and Bid data
{
    string link = "http://api.kucoin.com/api/v1/market/orderbook/level2_20?symbol=" + symbol; //set in a string the link to the api
    cpr::Response r = cpr::Get(cpr::Url{symbol},cpr::VerifySsl(false));
    json j_complete = json::parse(r.text); // api kucoin to json data process
    auto J_data = j_complete["data"];// json data process
    return J_data ;//
    }