//
// Created by Didier on 09/03/2022.
//

#include "httpGetFunctions.hpp"



json getapidata(const char* apilink) {// renvoi un json BRUTE de n'importe quel api, en fonction de l'api il peut nécessiter une modification
    json j_complete;
    cpr::Response r = cpr::Get(cpr::Url{apilink},cpr::VerifySsl(false));//requete get sur le lien "apilink"
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