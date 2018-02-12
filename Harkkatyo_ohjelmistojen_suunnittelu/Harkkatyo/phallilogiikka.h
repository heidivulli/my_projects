#ifndef PHALLILOGIIKKA_H
#define PHALLILOGIIKKA_H

#include "parkkihalli.h"
#include "parkkihalliikkuna.h"
#include "ruutu.h"
#include "tilasto.h"
#include "toimijaRP.h"

#include <map>
#include <memory>
#include <QImage>
#include <QKeyEvent>
#include <QObject>
#include <utility>
#include <vector>

/**
 * @brief Vastuussa parkkihalli-näkymässä tapahtuvasta pelin pyörittämisestä.
 * Pitää kirjaa kaikista tapahtumista.
 */


class phalliLogiikka : public QObject,
        public std::enable_shared_from_this<phalliLogiikka>{
Q_OBJECT

public:

    /**
      * @brief Rakentaja.
      * @param ase, joka Lauralla on käytössä. kilpi totuusarvona.
      * parkkihalliIkkuna, jota käytetään. phalli, jossa tapahtumat
      * tapahtuu. tilasto, johon talletetaan parkkihallin tapahtumat.
      */
    phalliLogiikka(int ase, bool kilpi,
                   std::shared_ptr<parkkihalliIkkuna> phalliIkkuna,
                   std::shared_ptr<parkkihalli> phalli,
                   std::shared_ptr<tilasto> til);

    /**
      * @brief Purkaja.
      */
    ~phalliLogiikka();

    /**
     * @brief annaAktiivinenToimija(), antaa aktiivisena olevan toimijan.
     * @pre aktiivinenToimija_ on asetettu.
     * @post Poikkeustakuu: nothrow.
     */
    std::shared_ptr<toimijaRP> annaAktiivinenToimija();

    /**
     * @brief annaRuudukko() antaa ruudukon.
     * @pre ruudukko_ on asetettu.
     * @post Poikkeustakuu: nothrow.
     */
    std::map<std::pair<int,int>,std::shared_ptr<ruutu>> annaRuudukko();

    /**
     * @brief Luo ja asettaa parkkihallin ruudukon phallilogiikan privateen.
     * @post Ruudukko on asetettu privaten ruudukko_ muuttujaan.
     * Poikkeustakuu: vahva.
     */
    // Kutsutaan kaupungin metodissa. Asetetaan ennen toimijoita.
    void asetaRuudukko();

    /**
     * @brief asetaTausta asettaa parkkihalliin taustakuvan.
     * @param taustakuva, parkkihallin pelialueena käytettävä karttakuva.
     * @post Parkkihallin taustakuva on asetettu. Poikkeustakuu: vahva.
     */
    void asetaTausta(QImage & taustakuva);

    /**
     * @brief asetaEsteet piirtää esteet karttaan
     * @pre lueEsteet funktio on suoritettu
     */
    void asetaEsteet();

    /**
     * @brief lueEsteet lukee konffitiedoston ja sen
     * perusteella tallentaa esteet ruudukkoon
     * @pre ruudukkoon on asetettuna esteet.
     * @return true, jos lukeminen onnistu ja
     * false jos lukeminen epäonnistui.
     */
    bool lueEsteet();

    /**
     * @brief asetaToimijat asettaa parkkihalliin toimijat.
     * @pre parkkihalliin on asetettu tausta.
     * @post Poikkeustakuu: vahva.
     */
    void asetaToimijat();

    /**
     * @brief asetaAktiivinenToimija asettaa aktiivisen toimijan privateen.
     * @param toimija, joka on aktiivisena.
     * @post Aktiivinen toimija on asetettu. Poikkeustakuu: vahva.
     */
    void asetaAktiivinenToimija(std::shared_ptr<toimijaRP> toimija);

    /**
     * @brief asetaAmmus asettaa parkkihalliin ammuksen.
     * @pre Parkkihallipeli on aloitettu ja toimijallla on toimintapisteitä.
     * @post Ammus on asetettu. Poikkeustakuu: vahva.
     */
    void asetaAmmus();

    /**
     * @brief lopeta sulkee parkkihallissa tapahtuvan pelin ja siirrytään
     * takaisin karttanäkymään. Asettaa parkkihallin tuhotuksi
     * @post Parkkihalli-ikkuna on suljettu ja karttanäkymä aukeaa.
     * Parkkihalli on asetettu tuhotuksi.
     * Poikkeustakuu: perus
     */
    void lopeta();

    /**
     * @brief phalliPeliAlkaa avaa parkkihalli-ikkunan ja piirtää toimijat
     * sinne.
     * @post Parkkihalli-ikkuna aukeaa ja sinne on piirretty toimijat.
     * Poikkeustakuu: perus
     */
    void phalliPeliAlkaa();

    /**
     * @brief vaihdaVuoroPelaajalle vaihtaa vuoron vastustajalta pelaajalle.
     * @pre vastustajan vuoro on ollut aiemmin.
     * @post Vuoro on vaihdettu pelaajalle. Sankarien toimintapisteet ovat
     * täytetty uudestaan. Poikkeustakuu: perus
     */
    void vaihdaVuoroPelaajalle();

    /**
     * @brief sankariinOsui-metodiin tullaan, jos ammus on osunut sankariin.
     * Metodin kautta vähennetään sankarin elämiä ja poistetaan tuhottu
     * sankari.
     * @param toimija, johon osuttiin.
     * @pre ammus on liikkunut ruutuun, jossa on sankari.
     * @post sankarin elämiä on vähennetty. Poikkeustakuu: perus
     */
    void sankariinOsui(std::shared_ptr<toimijaRP> toimija);

    /**
     * @brief viholliseenOsui-metodiin tullaan, jos ammus on osunut viholliseen.
     * Metodin kautta vähennetään vihollisen elämiä ja poistetaan tuhottu
     * vihollinen.
     * @param vihollinen, johon osuttiin.
     * @pre ammus on liikkunut ruutuun, jossa on vihollinen.
     * @post Vihollisen elämiä on vähennetty. Poikkeustakuu: perus
     */
    void viholliseenOsui(std::shared_ptr<vihollinen> vihulainen);

public slots:
    /**
     * @brief nappainPainettunaLiiku kontrolloi kaikkea liikkumiseen liittyvää.
     * Esim. vähennetään toimintapisteitä ja käsketään toimijaa liikkumaan.
     * @param Näppäin, jota painettiin.
     * @pre Sankarit on asetettu ja nuolinäppäintä on painettu.
     * @post Sankaria on liikutettu ja sen toimintapisteitä on vähennetty.
     * Poikkeustakuu: vahva
     */
    void nappainPainettunaLiiku(std::string nappain);

    /**
     * @brief nappainPainettunaAmmu kontrolloi kaikkea ampumiseen liittyvää.
     * @pre Sankarit on asetettu ja välilyöntiä on painettu,
     * @post Sankari on ampunut ja sen toimintapisteitä on vähennetty.
     * Poikkeustakuu: vahva
     */
    void nappainPainettunaAmmu();

    /**
     * @brief lauranVuoro vaihtaa aktiiviseksi toimijaksi Lauran.
     * @pre Laura on asetettu.
     * @post Muuttujaan aktiivinenToimija_ on asetettu lauran tiedot.
     * Poikkeustakuu: nothrow
     */
    void lauranVuoro();

    /**
     * @brief kyborgi1Vuoro vaihtaa aktiiviseksi toimijaksi kyborgi1.
     * @pre Kyborgi1 on asetettu ja kyborgit_ vektorin koko ei ole 0.
     * @post Muuttujaan aktiivinenToimija_ on asetettu kyborgi1 tiedot.
     * Poikkeustakuu: nothrow
     */
    void kyborgi1Vuoro();

    /**
     * @brief kyborgi2Vuoro vaihtaa aktiiviseksi toimijaksi kyborgi2.
     * @pre Kyborgi2 on asetettu ja kyborgit_ vektorin koko ei ole < 2.
     * @post Muuttujaan aktiivinenToimija_ on asetettu kyborgi2 tiedot.
     * Poikkeustakuu: nothrow
     */
    void kyborgi2Vuoro();

    /**
     * @brief vaihdaVuoroVastustajalle vaihtaa vuoron vastustajalle ja
     * käynnistää tekoälyn.
     * @pre Pelaajan vuoro on loppunut.
     * @post Vuoro on vaihdettu, toimintapisteet vihollisille palautetaan ja
     * tekoäly aloitetaan.
     * Poikkeustakuu: nothrow
     */
    void vaihdaVuoroVastustajalle();

private:
    int aktiivinenAse_;
    std::shared_ptr<toimijaRP> aktiivinenToimija_;
    std::vector<std::shared_ptr<este>> esteet_;
    std::vector<std::shared_ptr<toimijaRP>> kyborgit_;
    bool onkoKilpi_;
    // Lähellä oleva parkkihalli
    std::shared_ptr<parkkihalli> parkkihalli_;
    std::shared_ptr<parkkihalliIkkuna> parkkihalliIkkuna_;
    std::shared_ptr<toimijaRP> phallinLaura_;
    // Ensimmäisenä pairissa vaakasuunnan rivinumero, toisena pystysuunnan.
    std::map<std::pair<int,int>,std::shared_ptr<ruutu>> ruudukko_;   
    std::shared_ptr<tilasto> tilasto_;
    std::vector<std::shared_ptr<vihollinen>> viholliset_;
};



#endif // PHALLILOGIIKKA_H
