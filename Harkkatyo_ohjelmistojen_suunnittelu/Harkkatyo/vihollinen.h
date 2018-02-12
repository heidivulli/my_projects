#ifndef VIHOLLINEN_H
#define VIHOLLINEN_H

#include "ruutu.h"
#include "toimijaRP.h"

#include <memory>
#include <QGraphicsPixmapItem>
#include <QObject>


/**
  * @brief vihollinen hallinnoi vihollisen ampumista ja liikkumista.
  */

class vihollinen : public QObject, public QGraphicsPixmapItem,
        public toimijaRP, public std::enable_shared_from_this<vihollinen>
{
public:
    /**
      * @brief Rakentaja.
      */
    vihollinen(std::map<std::pair<int,int>,std::shared_ptr<ruutu>> & ruudukko,
               int elamat, int pisteet, int raha);
    /**
      * @brief Purkaja
      */
    ~vihollinen();

    /**
      * @brief annaSaatavaRaha antaa vihollisen tuhoamisesta saatavan rahan.
      * @return rahamäärä, jonka vihollisen tuhoamisesta saa.
      * Poikkeustakuu: nothrow.
      */
    int annaSaatavaRaha();

    /**
      * @brief annaSaatavatPisteet antaa vihollisen tuhoamisesta saatavan pistemäärän.
      * @return pistemäärä, jonka vihollisen tuhoamisesta saa.
      * Poikkeustakuu: nothrow.
      */
    int annaSaatavatPisteet();

    /**
      * @brief annaSuunta antaa vihollisen suunnan.
      * @return suunta, jonne vihollinen osoittaa.
      * Poikkeustakuu: nothrow.
      */
    char annaSuunta();

    /**
      * @brief onkoToimintapisteita kertoo, onko vihollisella toimintapisteitä jäljellä.
      * @return true, jos toimintapisteitä on jäljellä. false, jos toimintapisteitä
      * ei ole jäljellä.
      * Poikkeustakuu: nothrow.
      */
    bool onkoToimintapisteita();

    /**
      * @brief palautaToimintapisteet palauttaa vihollisella olevat toimintapisteet
      * täyteen.
      * @post vihollisen toimintapisteet on täytetty.
      * Poikkeustakuu: nothrow.
      */
    void palautaToimintapisteet();

    /**
      * @brief voikoAmpua tarkistaa, voiko vihollinen ampua tarkasteltavaan ruutuun.
      * @param ruutu, jota kohti ammutaan. ampumissuunta, johon ammutaan.
      * @return true, jos vihollinen voi ampua. false, jos vihollinen ei voi ampua.
      * Poikkeustakuu: vahva.
      */
    bool voikoAmpua(std::shared_ptr<ruutu> tarkisteltava, char ampumisSuunta);

    /**
      * @brief kaanny kääntää vihollisen haluttuun suuntaan.
      * @param suunta, johon vihollinen halutaan kääntää.
      * @post vihollinen on käännetty.
      * Poikkeustakuu: vahva.
      */
    void kaanny(char suunta);

    /**
      * @brief voikoLiikkua kertoo, voiko vihollinen liikkua haluttuun sijaintiin.
      * @param sijainti, johon vihollinen halutaan siirtää.
      * @return true, jos vihollinen voi liikkua haluttuun sijaintiin. false, jos
      * vihollinen ei voi liikkua haluttuun sijaintiin.
      * Poikkeustakuu: vahva.
      */
    bool voikoLiikkua(sijainti sij);

    /**
      * @brief liikuVasemmalle liikuttaa vihollista yhden ruudun vasemmalle.
      * @param matka, jonka verran vihollista halutaan liikuttaa,
      * @return true, jos vihollinen siirrettiin vasemmalle. false, jos vihollista
      * ei voitu siirtää vasemmalle.
      * Poikkeustakuu: vahva.
      */
    bool liikuVasemmalle(int matka);

    /**
      * @brief liikuOikealle liikuttaa vihollista yhden ruudun oikealle.
      * @param matka, jonka verran vihollista halutaan liikuttaa,
      * @return true, jos vihollinen siirrettiin oikealle. false, jos vihollista
      * ei voitu siirtää oikealle.
      * Poikkeustakuu: vahva.
      */
    bool liikuOikealle(int matka);

    /**
      * @brief liikuAlas liikuttaa vihollista yhden ruudun alas.
      * @param matka, jonka verran vihollista halutaan liikuttaa,
      * @return true, jos vihollinen siirrettiin alas. false, jos vihollista
      * ei voitu siirtää alas.
      * Poikkeustakuu: vahva.
      */
    bool liikuAlas(int matka);

    /**
      * @brief liikuYlos liikuttaa vihollista yhden ruudun ylemmäs.
      * @param matka, jonka verran vihollista halutaan liikuttaa,
      * @return true, jos vihollinen siirrettiin ylös. false, jos vihollista
      * ei voitu siirtää ylös.
      * Poikkeustakuu: vahva.
      */
    bool liikuYlos(int matka);

    /**
      * @brief liiku kontrolloi vihollisen liikettä. Kutsuu yllä olevia
      * funktioita.
      * @param näppäin, jota käyttäjä on painanut.
      * @return true, jos vihollista liikutettiin. false, jos vihollista
      * ei voitu liikuttaa.
      * Poikkeustakuu: vahva.
      */
    bool liiku(char liikkumisSuunta);

    /**
      * @brief vahennaElamia vähentää vihollisen elämäpisteitä.
      * @return true, jos vihollinen jäi eloon elämien vähennyksen jälkeen. false,
      * jos vihollinen kuoli (eli elämäpisteet loppuivat).
      * Poikkeustakuu: vahva.
      */
    bool vahennaElamia(int maara);

private:
    int elamat_;    
    std::map<std::pair<int,int>,std::shared_ptr<ruutu>> ruudukko_;
    int saatavaRaha_;
    int saatavatPisteet_;
    char suunta_;
    int toimintaPisteet_;
};


#endif // VIHOLLINEN_H
