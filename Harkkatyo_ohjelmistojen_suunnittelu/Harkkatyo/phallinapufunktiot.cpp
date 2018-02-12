#include "phallinapufunktiot.h"

#include <regex>
#include <QTextStream>






// Laskee sijainnin perusteella, missä ruudussa ollaan.
std::shared_ptr<ruutu> laskeSijainninRuutu(sijainti sij,
                                           std::map<std::pair<int,int>,
                                           std::shared_ptr<ruutu>> ruudukko) {
    int x{sij.annaX()};
    int y{sij.annaY()};
    std::map<std::pair<int,int>,std::shared_ptr<ruutu>>::iterator iterRuudukko{ruudukko.begin()};
    while(iterRuudukko != ruudukko.end()) {
        std::pair<int,int> sijaintiPairina{iterRuudukko->first};
        if (sijaintiPairina.first == x/75 and sijaintiPairina.second == y/75) {
            break;

        }
        ++ iterRuudukko;
    }
    return iterRuudukko->second;
}



QString avaaEsteTiedosto(QString tiedostoNimi)
{
    QString line{""};
    QFile tiedosto(tiedostoNimi);
    if(!tiedosto.exists()){
        return line;
    }
    else if(!tiedosto.open(QIODevice::ReadOnly | QIODevice::Text)){
        return line;
    }

    //arvotaan joku 1-5 väliltä, tämä vaikuttaa siihe
    //mikä tiedoston rivi luetaan
    int arvontaLuku = rand() %5;
    int indeksi{0};


    QTextStream in(&tiedosto);
    while(!in.atEnd()){
        line = in.readLine();
        if(indeksi == arvontaLuku){
            break;

        }
        ++indeksi;
    }

    //muutetaan QString std::stringiksi


    return line;
}




std::vector<std::string> tarkistaString(QString esteQString)
{

    std::string esteString = esteQString.toStdString();
    std::vector<std::string> esteVektori;
    std::regex valiMerkki("(\\S+)");

    auto tekstiAlkaa = std::sregex_iterator(esteString.begin(),esteString.end(), valiMerkki);
    auto tekstiLoppuu = std::sregex_iterator();

    if(std::distance(tekstiAlkaa,tekstiLoppuu) != 8){
        return esteVektori;
    }

    for(std::sregex_iterator indeksi = tekstiAlkaa; indeksi != tekstiLoppuu; ++indeksi){
        std::smatch iteraattorinOsoite = *indeksi;
        std::string riviString = iteraattorinOsoite.str();
        //tarkistetaan oikea koko
        if(riviString.length() != 11){
            return esteVektori;
        }
        //tarkistetaan että on vain välill 0-2 numeroita
        std::regex rivinMalli("[0-2]+");
        if(!std::regex_match(riviString,rivinMalli)){
            return esteVektori;
        }

        esteVektori.push_back(riviString);


    }
    return esteVektori;
}


//----- Toimijoiden poistaminen -----//

void poistaToimijaRuudukosta(std::map<std::pair<int,int>,std::shared_ptr<ruutu>> &ruudukko, std::shared_ptr<toimijaRP> toimija) {
    sijainti toimijanSij{toimija->annaSijainti()};
    std::shared_ptr<ruutu> toimijanRuutu {laskeSijainninRuutu(toimijanSij,ruudukko)};
    std::map<std::pair<int,int>,std::shared_ptr<ruutu>>::iterator mapiter;
    mapiter = ruudukko.begin();
    while(mapiter != ruudukko.end()) {
        if (mapiter->second == toimijanRuutu) {
            (mapiter->second)->poistaKomponentti();
            return;
        }
        ++ mapiter;
    }

}
