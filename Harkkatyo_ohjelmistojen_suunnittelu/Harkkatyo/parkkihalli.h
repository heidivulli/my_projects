#ifndef PARKKIHALLI_H
#define PARKKIHALLI_H

#include "sijainti.h"

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QString>



/**
 * @brief Sisältää tiedot yksittäisestä parkkihallista.
 */

class parkkihalli: public QObject, public QGraphicsPixmapItem{
Q_OBJECT

public:

    /**
     * @brief Rakentaja
     */
    parkkihalli();

    /**
      * @brief Purkaja.
      */
    ~parkkihalli();
    /**
     * @brief: annaID palauttaa parkkihallin ID:n
     * @pre: id on asetettu.
     * @return: parkkihallin ID.
     * @poikkeustakuu: nothrow.
     */

    QString annaID() const;

    /**
     * @brief annaVaikeus palauttaa parkkihallin vaikeuasasteen
     * @pre: parkkihallille on määritetty koko_ ja varattujenPaikkojenMaara_
     * @return: parkkihallin vaikeusaste
     * @poikkeustakuu: nothrow.
     */

    QString annaVaikeus() const;

    /**
     * @brief annaSijainti palauttaa parkkihallin sijainnin.
     * @pre sijainti on asetettu
     * @return Parkkihallin sijainti.
     * @poikkeustakuu: nothrow
     */

    sijainti annaSijainti() const;

    /**
      * @brief annaKokoString palauttaa parkkihallin määritetyn koon
      * stringinä
      * @return palauttaa kokoStringin (Pieni, Keskisuuri, Iso)
      * @poikkeustakuu: nothrow
      */

     QString annaKokoString() const;

    /**
     * @brief onkoTuhottu palauttaa tiedon, onko parkkihalli tuhottu.
     * @return 'true', jos parkkihalli on tuhottu, muuten 'false'.
     * @poikkeustakuu: nothrow
     */
    bool onkoTuhottu() const;

    /**
     * @brief asetaID asettaa parkkihallin id:n parkkihallin.
     * @param parkkihallin id
     * @post id_ asetettu
     * @poikkeustakuu: vahva
     */

    void asetaID(QString id);

    /**
     * @brief asetaNimi asettaa parkkihallin nimen
     * @param nimi, parkkihallin nimi QStringinä
     * @post nimi_ asetettu
     * @poikkeustakuu: vahva.
     */
    void asetaNimi(QString nimi);

    /**
     * @brief asetaSijainti asettaa parkkihallin sijainnin
     * koordinaattien perusteella. Laskee myös onko koordinaatit
     * kartan sisällä.
     * @param latitude, parkkihallin latitude koordinaatti
     * @param longitude, parkkihallin longitude koordinaatti
     * @return true, jos parkkihalli on kartan sisällä. False
     * jos ei ole kartan sisällä
     * @post sijainti_ asetettu , tai palautettu false
     * jos parkkihalli ei ole kartan sisällä
     * @poikkeustakuu: vahva.
     */
    bool asetaSijainti(QString latitude, QString longitude);

    /**
     * @brief asetaMaksimiKoko asettaa parkkihallin maksimikoon
     * lukuna. Asettaa myös koon stringinä (Pieni, Keskisuuri tai Iso)
     * riippuen maksimikoosta (koko<300 -> Pieni, 300<koko<500-> Keskisuuri,
     * koko> 500 ->Suuri
     * @param koko, parkkihallin maksimikoko QStringinä
     * @post koko_ ja kokoString_ asetettu
     * @poikkeustakuu: vahva
     */

    void asetaMaksimiKoko(QString koko);

    /**
     * @brief asetaVaratutPaikkojenMaara asettaa parkkihallin
     * varattujen paikkojen määrän
     * @param varatutPaikat, varatut paikat QStringinä
     * @post varattujenPaikkojenMaara_ asetettu
     * @poikkeustakuu:vahva
     */

    void asetaVaratutPaikkojenMaara(QString varatutPaikat) ;

    /**
     * @brief tuhoa asettaa parkkihallin tuhotuksi
     * @post onkoTuhottu_ on true
     * @poikkeustakuu: nothrow
     */
    void tuhoa();


    /**
     * @brief Asettaa parkkihallin vaikeuden. Vaikeusaste
     * riippu parkkihallin koosta ja varattujen paikkojen määrästä
     * @post Poikkeustakuu: vahva.
     */
    void asetaVaikeus() ;

private:
    QString id_;
    double koko_;
    QString kokoString_; //parkkihallin koko stringinä
    //(pieni, keskisuuri, iso)
    QString nimi_;
    bool onkoTuhottu_;
    sijainti sijainti_;
    QString vaikeusAste_;
    double varattujenPaikkojenMaara_;

};


#endif // PARKKIHALLI_H
