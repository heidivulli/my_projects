#ifndef TEEKKARIKYBORGI_H
#define TEEKKARIKYBORGI_H

#include "ruutu.h"
#include "toimijaRP.h"

#include <memory>
#include <QObject>
#include <QGraphicsPixmapItem>

/**
  * @brief teekkariKyborgi hallinnoi logiikkaa parkkihallissa olevan lauran ja
  * kyborgien takana.
  */

class teekkariKyborgi : public QObject, public QGraphicsPixmapItem,
        public toimijaRP, public std::enable_shared_from_this<teekkariKyborgi>
{
public:
    /**
      * @brief Rakentaja.
      * @param elamat, jotka kyborgille asetetaan. ruudukko, jossa kyborgi
      * liikkuu.
      */
    teekkariKyborgi(int elamat,
                    std::map<std::pair<int,int>,std::shared_ptr<ruutu>> & ruudukko);
    /**
      * @brief Purkaja
      */
    ~teekkariKyborgi();

    /**
      * @brief annaElamat antaa kyborgilla olevat elämäpisteet.
      * @return kyborgin elämät.
      * Poikkeustakuu: nothrow.
      */
    int annaElamat();

    /**
      * @brief annaSuunta antaa kyborgin suunnan.
      * @return suunta, jonne kyborgi osoittaa.
      * Poikkeustakuu: nothrow.
      */
    char annaSuunta();

    /**
      * @brief annaToimintapisteet antaa kyborgin toimintapisteet.
      * @return kyborgin toimintapisteet.
      * Poikkeustakuu: nothrow.
      */
    int annaToimintapisteet();

    /**
      * @brief kaanny kääntää kyborgin haluttuun suuntaan.
      * @param suunta, johon kyborgi halutaan kääntää.
      * @post kyborgi on käännetty.
      * Poikkeustakuu: vahva.
      */
    void kaanny(char suunta);

    /**
      * @brief voikoLiikkua kertoo, voiko kyborgi liikkua haluttuun sijaintiin.
      * @param sijainti, johon kyborgi halutaan siirtää.
      * @return true, jos kyborgi voi liikkua haluttuun sijaintiin. false, jos
      * kyborgi ei voi liikkua haluttuun sijaintiin.
      * Poikkeustakuu: vahva.
      */
    bool voikoLiikkua(sijainti sij);

    /**
      * @brief liikuVasemmalle liikuttaa kyborgia yhden ruudun vasemmalle.
      * @param matka, jonka verran kyborgia halutaan liikuttaa,
      * @return true, jos kyborgi siirrettiin vasemmalle. false, jos kyborgia
      * ei voitu siirtää vasemmalle.
      * Poikkeustakuu: vahva.
      */
    bool liikuVasemmalle(int matka);

    /**
      * @brief liikuOikealle liikuttaa kyborgia yhden ruudun oikealle.
      * @param matka, jonka verran kyborgia halutaan liikuttaa,
      * @return true, jos kyborgi siirrettiin oikealle. false, jos kyborgia
      * ei voitu siirtää oikealle.
      * Poikkeustakuu: vahva.
      */
    bool liikuOikealle(int matka);

    /**
      * @brief liikuAlas liikuttaa kyborgia yhden ruudun alas.
      * @param matka, jonka verran kyborgia halutaan liikuttaa,
      * @return true, jos kyborgi siirrettiin alas. false, jos kyborgia
      * ei voitu siirtää alas.
      * Poikkeustakuu: vahva.
      */
    bool liikuAlas(int matka);

    /**
      * @brief liikuYlos liikuttaa kyborgia yhden ruudun ylemmäs.
      * @param matka, jonka verran kyborgia halutaan liikuttaa,
      * @return true, jos kyborgi siirrettiin ylös. false, jos kyborgia
      * ei voitu siirtää ylös.
      * Poikkeustakuu: vahva.
      */
    bool liikuYlos(int matka);

    /**
      * @brief liiku kontrolloi kyborgien liikettä. Kutsuu yllä olevia
      * funktioita.
      * @param näppäin, jota käyttäjä on painanut.
      * @return true, jos kyborgia liikutettiin. false, jos kyborgia
      * ei voitu liikuttaa.
      * Poikkeustakuu: vahva.
      */
    bool liiku(std::string nappain);

    /**
      * @brief ammu tarkistaa, onko kyborgilla tarpeeksi toimintapisteitä
      * ampumista varten.
      * @return true, jos kyborgi voi ampua. false, jos kyborgi ei voi ampua.
      * Poikkeustakuu: vahva.
      */
    bool ammu();

    /**
      * @brief vahennaElamia vähentää kyborgin elämäpisteitä.
      * @return true, jos kyborgi jäi eloon elämien vähennyksen jälkeen. false,
      * jos kyborgi kuoli (eli elämäpisteet loppuivat).
      * Poikkeustakuu: vahva.
      */
    bool vahennaElamia();

    /**
      * @brief palautaToimintapisteet palauttaa kyborgin toimintapisteet takaisin
      * täyteen.
      * @post toimintapisteet on täytetty.
      * Poikkeustakuu: nothrow.
      */
    void palautaToimintapisteet();

private:
    char suunta_;
    std::map<std::pair<int,int>,std::shared_ptr<ruutu>> ruudukko_;
    int toimintaPisteet_;
    int elamat_;

};


#endif // TEEKKARIKYBORGI_H
