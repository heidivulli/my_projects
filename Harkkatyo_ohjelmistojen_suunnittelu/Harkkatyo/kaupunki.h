#ifndef KAUPUNKI_H
#define KAUPUNKI_H

#include "kauppa.h"
#include "kauppaikkuna.h"
#include "kaupunkiikkuna.h"
#include "parkkihalli.h"
#include "parkkihalliikkuna.h"
#include "phallilogiikka.h"
#include "tilasto.h"
#include "toimijaRP.h"

#include <QImage>
#include <QObject>
#include <memory>
#include <vector>



/**
 * @brief luokka, joka pitää huolta suurimmasta osasta pelin tiedoista.
 * Luo tilaston, parkkihallilogiikan, kaupunkiIkkunan ja "Lauran".
 * Periytetty QObjectista ja std::enable_shared_from_this, jotta this-pointteri
 * voidaan muuttaa shared_ptr:ksi.
 */
class kaupunki : public QObject , public std::enable_shared_from_this<kaupunki> {
Q_OBJECT

public:

    /**
      * @brief Rakentaja.
      * @post Kaupunki on alustustilassa.
      */
    kaupunki(std::shared_ptr<kaupunkiIkkuna> kIkkuna);

    /**
      * @brief Purkaja.
      */
    ~kaupunki();

    /**
     * @brief onkoParkkihalliLahella, tarkistaa onko jokin parkkihalli lähellä
     * aina kun Laura liikkuu.
     * @param Lauran sijainti
     * @pre Kaupunki on pelitilassa.
     * @post Poikkeustakuu: vahva.
     */
    void onkoParkkihalliLahella(sijainti sij);

    /**
     * @brief asetaTausta asettaa pelialueen karttakuvan.
     * @param taustakuva, pelialueena käytettävä karttakuva.
     * @pre Kaupunki on alustustilassa.
     * @post Pelialueen karttakuva on asetettu. Poikkeustakuu: perus.
     */
    void asetaTausta(QImage &taustakuva);

    /**
     * @brief asetaParkkihalli lisää kaupunkiin parkkihallin.
     * @param osoitin vektoriin, jossa on osoittime kaikkiin parkkihalleihin
     * @pre Kaupunki on alustustilassa.
     * @post Parkkihalli on lisätty kaupunkiin. Poikkeustakuu: perus
     */
    void asetaParkkihalli();


    /**
     * @brief Päivittää parkkihallien tiedot API-rajapinnan
     * mukaisia
     * @param Tiedoston nimi jota halutaan lukea. Jos halutaan käyttää
     * API-rajapintaa, tiedoston nimeksi asetetaan ""
     * @pre -.
     * @post Parkkihallien tiedot ovat ajan tasalla
     * @return true, jos parkkihallien päivittäminen onnistui.
     * false jos se epäonnistui.
     *
     */
    bool haeParkkihallit(const QString & tiedosto);

    /**
     * @brief asettaa tilaston kaupungin privateen.
     * @param osoitin tilastoon.
     * @pre kaupunki on alustustilassa.
     * @post tilasto on asetettu kaupunkiin.
     */

    void asetaTilasto(std::shared_ptr<tilasto> uusiTilasto);

    /**
     * @brief peliAlkaa siirtää kaupungin alustustilasta pelitilaan.
     * @pre Kaupunki on alustustilassa.
     * @post Kaupunki on pelitilassa. Poikkeustakuu: nothrow.
     */
    void peliAlkaa();

    /**
     * @brief onkoPeliLoppunut kertoo, onko peli loppunut vai ei.
     * @pre Kaupunki on pelitilassa.
     * @return 'true', jos peli on loppunut, muuten 'false'.
     * @post Poikkeustakuu: nothrow.
     */
    bool onkoPeliLoppunut() const;

    /**
     * @brief asetaLaura antaa laurana kaupungille
     * sekä asettaa lauran sijainnin kartalla
     * @param uusiLaura, osoitin luotuun lauraan
     * @pre uusiLaura osoittaa luotuun olioon
     * @post Laura on annettu kaupungille ja lauralla on sijainti
     * poikkeustakuu: vahva
     */
    void asetaLaura(std::shared_ptr<toimijaRP> uusiLaura);

    /**
     * @brief asetaKaupanSijainti, asettaa kaupalle sijainnin kartalla
     * kauppa-oliota ei kuitenkaan vielä luoda
     * @post kaupan sijainti on tallennettu kaupungin privateen
     * poikkeustakuu: vahva
     */
    void asetaKaupanSijainti();

    /**
     * @brief onkoKauppaLahella, vertaa kaupan ja Lauran sijaintia,
     * ja tarkistaa onko etäisyys alle 20
     * @param sij, Lauran sen hetkinenn sijainta
     * @pre lauralla ja kaupalla on sijainti
     * @post poikkeustakuu: vahva
     */
    void onkoKauppaLahella(sijainti sij);

public slots:
    /**
     * @brief siirryParkkihalliin avaa parkkihalli-ikkunan.
     * Luo phallilogiikka-olion sekä jäädyttää kaupunki-ikkunan.
     * @pre kaupunki on pelitilassa
     * @post Poikkeustakuu: perus
     */
    void siirryParkkihalliin();
    /**
     * @brief lopetaPeli sulkee peli-ikkunan ja avaa lopetus-ikkunan.
     * Funktioon tullaan, jos onkoPeliLoppunut-funktio palauttaa 'true' tai
     * pelaaja painaa Lopeta-nappia.
     * @pre Kaupunki on pelitilassa. onkoPeliLoppunut-funktio palautti arvon
     * 'true' tai pelaaja painoi Lopeta-nappia.
     * @post Peli-ikkuna on suljettu ja lopeta-ikkuna avattu. Poikkeustakuu:
     * perus
     */
    void lopetaPeli();

    /**
     * @brief tarkistaa, onko peli loppunut. Jos ei,
     * avaa kaupunkiIkkuna uudestaan. Hakee myös parkkihallidatan
     * API-rajapinnasta kutsumalla haeParkkihallit() ja asetaParkkihallit()
     * funktioita.
     * @pre parkkihalli-peli on loppunut
     * @post kaupunkiIkkuna on avattu uudestaan ja parkkihallien tiedot on
     * päivitetty API-rajapinnan antaman datan mukaiseksi.
     */
    void avaaKikkunaUudestaan();

    /**
     * @brief siirryKauppaan, luo uuden Kauppa-olion
     * ja anta sille kauppaikkunan, rahat ja lauran
     * @post poikkeustakuu: vahva
     */
    void siirryKauppaan();

    /**
     * @brief palaaKaupasta, avaa kaupunkiIkkunan uudelleen,
     * päivittää rahat tilastoon ja kaupunkiIkkunaan
     * @param loputRahat, jäljelle jääneet rahat
     * @post poikkeustakuu: vahva
     */
    void palaaKaupasta(int loputRahat);

private:

    std::shared_ptr<kaupunkiIkkuna> kaupunkiIkkuna_;
    std::shared_ptr<std::vector
            <std::shared_ptr<parkkihalli>>> parkkihallit_;
    //tallennetaan tänne, jos jokin parkkihalli on toimijan lähellä
    std::shared_ptr<parkkihalli> lahellaOlevaParkkihalli_;
    QImage taustakuva_;
    std::shared_ptr<tilasto> tilasto_;
    std::shared_ptr<toimijaRP> laura_;
    //kertoo, onko peli alustustilassa (True) vai onko alkanut (False)
    bool peliAlustustilassa_;
    std::shared_ptr<parkkihalliIkkuna> phalliIkkuna_;
    std::shared_ptr<phalliLogiikka> phallilogiikka_;
    std::shared_ptr<Kauppa> kauppa_;
    sijainti kaupanSijainti_;
    std::shared_ptr<KauppaIkkuna> kauppaIkkuna_;
};



#endif // KAUPUNKI_H
