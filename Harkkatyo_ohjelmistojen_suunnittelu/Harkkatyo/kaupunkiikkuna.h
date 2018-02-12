#ifndef KAUPUNKIIKKUNA_H
#define KAUPUNKIIKKUNA_H

#include "kauppa.h"
#include "parkkihalli.h"
#include "toimijaRP.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QMainWindow>
#include <memory>

/**
 * @brief kaupunkiIkkuna-luokka esittää pelin grafiikan kaupungissa pelattaessa
 */

namespace Ui {
class kaupunkiIkkuna;
}


class kaupunkiIkkuna : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Rakentaja
     */
    explicit kaupunkiIkkuna(QWidget *parent = 0);

    /**
     * @brief Purkaja
     */
    ~kaupunkiIkkuna();

    /**
     * @brief asetaTausta, asetetaan kartan kuva näkyville kaupunkiIkkunaan
     * @param item, kaupunkiIkkunassa näkyvä karttakuva
     * @post taustakuva on asetettu, Poikkeustakuu: vahva
     */
    void asetaTausta(QGraphicsPixmapItem *item);

    /**
     * @brief asetaLauranKuva, asetetaan Lauran kuva näkymään kartalla
     * @param uusiLaura, osoitin laura-olioon
     * @pre laura-olio on luotu
     * @post Lauran kuva on asetettu kartalle,
     * poikkeustakuu: vahva
     */
    void asetaLauranKuva(std::shared_ptr<toimijaRP> uusiLaura);

    /**
     * @brief Asettaa parkkihallin kaupunki-ikkunaan
     * @param osoitin parkkihalliin
     * @pre -
     * @post Parkkihalli on kaupunki-ikkunassa
     */
    void asetaParkkihalli(std::shared_ptr<parkkihalli> phalli);

    /**
     * @brief phalliNapinTila, asettaa phalli-napin joko käytettäväksi tai ei,
     * riippuen siitä onko Laura tarpeeksi lähellä jotakin parkkihallia
     * @param tila, jos true = nappi aktivoituu, muuten ei
     * @post nappi on aktivoitu sen mukaan onko Laura tarpeeksi lähellä parkkihallia
     * poikkeustakuu: nothrow
     */
    void phalliNapinTila(bool tila);

    /**
     * @brief asetaKaupanKuva, asettaa kaupan kuvan kartalle
     * @param sij, kaupan sijainti
     * @pre kaupalla on sijainti
     * @post kaupan kuva on kartalla
     * poikkeustakuu: vahva
     */
    void asetaKaupanKuva(sijainti &sij);

    /**
     * @brief kauppaNapinTila, asettaa kauppa-napin joko käytettäväksi tai ei,
     * riippuen siitä onko Laura tarpeeksi lähellä kauppaa
     * @param tila, jos true = nappi aktivoituu, muuten ei
     * @post nappi on aktivoitu sen mukaan onko Laura tarpeeksi lähellä kauppaa
     * poikkeustakuu: nothrow
     */
    void kauppaNapinTila(bool tila);

    /**
     * @brief Päivittää lähellä olevan parkkihallin tiedot
     * käyttöliittymään, parkkihallinTiedot QTextBrowseriin.
     * @param osoitin parkkihalliin.
     * @pre -
     * @post Parkkihallin tiedot päivitetty käyttöliittymään. Jos
     * osoitin on nullptr, asetetaan QTextBrowser tyhjäksi.
     */
    void paivitaParkkihallinTiedot(std::shared_ptr<parkkihalli> phalli);

    /**
     * @brief paivitaRahat, päivittää kaupunkiIkkunassa näkyvät rahat
     * @param rahat, pelaajan voittamat rahat
     * @post rahat on päivitetty kaupunkiIkkunaan
     * poikkeustakuu: nothrow
     */
    void paivitaRahat(int rahat);

    /**
     * @brief paivitaPisteet, päivittää kaupunkiIkkunassa näkyvät pisteet
     * @param pisteet, pelaajan saamat pisteet parkkihalleista
     * @post pisteet on päivitetty kaupunkiIkkunaan
     * poikkeustakuu: nothrow
     */
    void paivitaPisteet(int pisteet);

    /**
     * @brief paivitaParkkihallinKuva päivittää kaupunki-ikkunaan parkkihallin
     * kuva. Kuva vaihtuu, jos parkkihalli on tuhoutunut tai vaikeusaste muuttunut.
     * @param phalli, jonka kuva halutaan muuttaa.
     * @pre parkkihalli on asetettu sceneen.
     * @post parkkihallin kuva on päivitetty karttaan.
     * @poikkeustakuu nothrow.
     */
    void paivitaParkkihallinKuva(std::shared_ptr<parkkihalli> phalli);

public slots:
    void avaaPhalliPeli();
    /**
     * @brief avaaKauppa, piilottaa kaupunkiIkkunan
     * lähettää kauppaNappiPainettu-signaalin
     */
    void avaaKauppa();
    /**
     * @brief lopetaPeliin tullaan painettaessa sulje nappulaa.
     * Lähettää lopetaNappiPainettu() signaalin
     */
    void lopetaPeli();

signals:
    /**
     * @brief phalliNappiPainettu on signaali,
     * joka lähetetään kun pelaaja painaa phalli-nappia.
     * se napataan kaupungissa
     */
    void phalliNappiPainettu();
    /**
     * @brief kauppaNappiPainettu on signaali,
     * joka lähetetään kun pelaaja painaa kauppa-nappia.
     * se napataan kaupungissa
     */
    void kauppaNappiPainettu();

    /**
     * @brief lopetaNappiPainettu on signaali,
     * joka lähetetään kun pelaaja painaa lopeta-nappia.
     * se napataan kaupungissa
     */
    void lopetaNappiPainettu();

private:
    Ui::kaupunkiIkkuna *ui;
    QGraphicsScene *scene_;

};


#endif // KAUPUNKIIKKUNA_H
