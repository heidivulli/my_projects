#ifndef PHALLINAPUFUNKTIOT_H
#define PHALLINAPUFUNKTIOT_H

#include "ruutu.h"

#include <algorithm>
#include <map>
#include <memory>
#include <vector>
#include <QFile>


/**
 * @brief laskeSijainninRuutu laskee sijainnin avulla mitä ruutua tarkoitetaan.
 * @param sijainti, jonka ruutu halutaan laskea. ruudukko, josta ruutu
 * etsitään.
 * @return palauttaa ruudun, jonka sijainti on annettu sijainti.
 */
std::shared_ptr<ruutu> laskeSijainninRuutu(sijainti sij,
                      std::map<std::pair<int,int>,std::shared_ptr<ruutu>> ruudukko);

/**
 * @brief avaaEste tiedosto avaa esteKonffi tiedoston
 * ja lukee sen. A
 * @param tiedostoNimi, joka halutaan lukea. QString
 * @return palauttaa yhden tiedoston rivin.
 * Funktio arpoo yhden rivin väliltä 1-5 jonka se palauttaa
 */
QString avaaEsteTiedosto(QString tiedostoNimi);

/**
 * @brief tarkistaString tarkistaa luetun stringin.
 * Stringissä täytyy olla kahdeksan välilyönnillä
 * erotettua stringiä. Nämä stringit täytyvät olla
 * 11 merkin pituisia. Sallitut merkit ovat 0,1 ja 2
 * @param esteQString, joka tarkistetaan.
 * @return palauttaa vektorin, mihin on tallennettu
 * välilyönneillä erotetut stringit. Jos vektorin koko
 * ei ole kahdeksan, on tarkastelussa löytynyt virhe
 */
std::vector<std::string> tarkistaString(QString esteQString);

/**
 * @brief poistaToimijaRuudukosta poistaa toimijan ruudukosta.
 * @param ruudukko, josta toimija halutaan poistaa. toimija, joka halutaan
 * poistaa ruudukosta.
 * @post poistaa toimijan ruudukosta.
 */
void poistaToimijaRuudukosta(std::map<std::pair<int,int>,
                             std::shared_ptr<ruutu>> &ruudukko,
                             std::shared_ptr<toimijaRP> toimija);

#endif // PHALLINAPUFUNKTIOT_H
