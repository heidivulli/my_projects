#ifndef KAUPPA_H
#define KAUPPA_H

#include "kauppaikkuna.h"
#include "toimijaRP.h"

#include <memory>
#include <QGraphicsPixmapItem>
#include <QObject>

/**
 * @brief Kauppa-luokka hoitaa logiikan kun pelaaja ostaa kaupasta tuotteita.
 * Kauppa välittää myös tiedon ostetuista tuotteista Lauralle.
 */
class Kauppa: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    /**
     * @brief Kauppa, rakentaja
     * @param kauppaIkkuna, kaupan grafiikan näyttävä ikkuna
     * @param rahat, pelaajan voittamat rahat
     * @param kaupanLaura, pelissä seikkaileva Laura
     */
    Kauppa(std::shared_ptr<KauppaIkkuna> kauppaIkkuna, int rahat, std::shared_ptr<toimijaRP> kaupanLaura);
    /**
     * @brief purkaja
     */
    ~Kauppa();

    /**
     * @brief kauppaAukeaa välittää aukeavalle kaupan ikkunalle tarvittavat tiedot
     * käytössä olevista rahoista sekä Lauran aseista
     * @pre kaupunki on pelitilassa
     * @post Poikkeustakuu: perus
     */
    void kauppaAukeaa();

public slots:
    /**
     * @brief ostaKilpi lisää kilven Lauralle kun 
     * pelaaja on painanut ostaKilpi-nappia kauppaIkkunassa.
     * @pre rahaa on vähintään 500 e, Lauralle ei vielä ole kilpeä
     * @post Lauralla on kilpi, poikkeustakuu: vahva
     */
    void ostaKilpi();
    /**
     * @brief ostaHaulikko lisää haulikon Lauralle kun 
     * pelaaja on painanut ostaHaulikko-nappia kauppaIkkunassa.
     * @pre rahaa vähintään 1000 e, Lauralla on perusase
     * @post Lauralla on haulikko, poikkeustakuu: vahva
     */
    void ostaHaulikko();
    /**
     * @brief ostaKivaari lisää kivaarin Lauralle kun 
     * pelaaja on painanut ostaKivaari-nappia kauppaIkkunassa.
     * @pre rahaa vähintään 2000 e, Lauralla on joko perusase tai haulikko
     * @post Lauralla on kivaari, poikkeustakuu: vahva
     */
    void ostaKivaari();

private:
    std::shared_ptr<KauppaIkkuna> kaupanIkkuna_;
    int rahat_;
    std::shared_ptr<toimijaRP> laura_;


};

#endif // KAUPPA_H
