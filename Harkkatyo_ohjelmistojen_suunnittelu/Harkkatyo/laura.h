#ifndef LAURA_H
#define LAURA_H

#include "kaupunki.h"
#include "toimijaRP.h"

#include <memory>
#include <QKeyEvent>

/**
 * @brief laura-luokka sisältää tiedot Lauran kaupuningista, aseista sekä suunnasta.
 * Hoitaa metodeillaan liikkumisen sekä ase-kirjanpidon.
 */


class laura : public QObject, public QGraphicsPixmapItem, public toimijaRP{
        Q_OBJECT

public:
    /**
     * @brief laura, rakentaja
     */
    laura();
    /**
     * @brief Purkaja
     */
    ~laura();

    /**
     * @brief asetaKaupunki, asettaa Lauralle kaupungin
     * @param lauranKaupunki, kaupunki, jossa Laura seikkailee
     * @pre kaupunki on pelissä käytettävä kaupunki
     * @post kaupunki on asetettu
     */
    void asetaKaupunki(std::shared_ptr<kaupunki> lauranKaupunki);
    /**
     * @brief kaanny, kääntää Lauran annettuun suuntaan
     * @param suunta, Lauran uusi suunta
     * @pre suunta on y, a, o tai v
     * @post Lauralla on uusi suunta, poikkeustakuu: vahva
     */
    void kaanny(char suunta);
    /**
     * @brief annaSuunta, palauttaa Lauran sen hetkisen suunnan
     * @return Lauran sen hetkinen suunta
     * @pre Lauralle on asetettu suunta
     * @post palautettava arvo on y, a, o tai v, poikkeustakuu: nothrow
     */
    char annaSuunta();

    /**
     * @brief liikuVasemmalle, liikuttaa Lauraa vasemmalle tietyn matkan,
     * mutta ei kartan ulkopuolelle
     * @param matka, Lauran liikkuma matka
     * @post Laura on liikkunut tietyn matkan ja on kartalla
     * poikkeustakuu: perus
     */
    void liikuVasemmalle(int matka);
    /**
     * @brief liikuOikealle, liikuttaa Lauraa oikealle tietyn matkan,
     * mutta ei kartan ulkopuolelle
     * @param matka, Lauran liikkuma matka
     * @post Laura on liikkunut tietyn matkan ja on kartalla
     * poikkeustakuu: perus
     */
    void liikuOikealle(int matka);
    /**
     * @brief liikuAlas, liikuttaa Lauraa alas tietyn matkan,
     * mutta ei kartan ulkopuolelle
     * @param matka, Lauran liikkuma matka
     * @post Laura on liikkunut tietyn matkan ja on kartalla
     * poikkeustakuu: perus
     */
    void liikuAlas(int matka);
    /**
     * @brief liikuYlos, liikuttaa Lauraa ylos tietyn matkan,
     * mutta ei kartan ulkopuolelle
     * @param matka, Lauran liikkuma matka
     * @post Laura on liikkunut tietyn matkan ja on kartalla
     * poikkeustakuu: perus
     */
    void liikuYlos(int matka);

    /**
     * @brief onkoKilpi, palauttaa tiedon onko Lauralla jo kilpi
     * @return palauttaa true, jos Lauralla on kilpi, muuten false
     * @post Poikkeustakuu: nothrow
     */
    bool onkoKilpi();
    /**
     * @brief kilpiOstettu, Lauralla on nyt kilpi
     * @pre Lauralle ei ollut aiemmin kilpeä
     * @post onkoKilpi() palauttaa true
     * poikkeustakuu: nothrow
     */
    void kilpiOstettu();

    /**
     * @brief nollaaKilpi nollaa Lauran kilven.
     * @post kilpi on nollattu.
     * poikkeustakuu: nothrow
     */
    void nollaaKilpi();

    /**
     * @brief annaAse, antaa Lauran sen hetkisen aseen
     * @return Lauran ase
     * @post palautettava arvo on 0, 1 tai 2
     * poikkeustakuu: nothrow
     */
    int annaAse();
    /**
     * @brief uusiAse, päivittää Lauralle uuden aseen joka on ostettu
     * @param ase, Lauralle ostettu ase
     * @pre ase on 1 tai 2, sekä edellistä asetta vahvempi
     * @post Lauralla on uusi, vahvempi ase
     * poikkeustakuu: nothrow
     */
    void uusiAse(int ase);

    /**
     * @brief keyPressEvent hallinnoi näippäimistöstä saatavia signaleja
     * @param event, näppäin, jota pelaaja on painanut liikuttaakseen Lauraa kartalla
     * @pre pelaaja on painanut jotain näppäimistön näppäintä
     * @post jos näppäin on jokin nuolinäppäimistä, kutsutaan metodia,
     * joka liikuttaa Lauraa kyseiseen suuntaan
     * poikkeustakuu:vahva
     */
    void keyPressEvent(QKeyEvent *event);

private:
    std::shared_ptr<kaupunki> kaupunki_;
    //lauran sen hetkinen suunta
    char suunta_;

    //true = kilpi käytössä, false = ei käytössä
    bool kilpi_;

    //numero kertoo, mikä ase lauralla on käytössä
    //0 = perusase
    //1 = haulikko
    //2 = konekivääri
    int ase_;
};


#endif // LAURA_H
