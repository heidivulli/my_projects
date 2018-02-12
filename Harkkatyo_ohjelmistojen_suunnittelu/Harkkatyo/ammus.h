#ifndef AMMUS_H
#define AMMUS_H

#include "ruutu.h"
#include "sijainti.h"
#include "vihollinen.h"

#include <QGraphicsPixmapItem>
#include <QObject>

/**
 * @brief ammus-luokka luo ammus-olion, jota liikutetaan sankarin tai vihollisen ampuessa
 */

class phalliLogiikka;

class ammus : public QObject, public QGraphicsPixmapItem {
Q_OBJECT

public:
    /**
    * @brief Rakentaja
    * @param phallilogiikka ja ammuksen ampuja
    */
    ammus(std::shared_ptr<phalliLogiikka> pLogiikka,
          std::shared_ptr<toimijaRP> ampuja);

    /**
    * @brief Purkaja
    */
    ~ammus();

    /**
     * @brief kaanny kääntää ammuksen osoittamaan oikeaan suuntaan.
     * @param suunta, johon ammus halutaan kääntää.
     * @post ammusta on käännetty.
     */
    void kaanny(char suunta);

    /**
     * @brief asetaSijainti asettaa ammuksen alkusijainnin
     * @param x ja y, mikä halutaan antaa ammuksen sijainniksi
     * @pre -
     * @post Sijainti on asetettu
     */
    void asetaSijainti(int x, int y);

public slots:
    /**
     * @brief liiku liikuttaa ammusta nopeudella 3.
     * @post Ammuksen sijainti on siirretty
     */
    void liiku();

private:   
    std::shared_ptr<toimijaRP> ampuja_;   
    std::shared_ptr<phalliLogiikka> pLogiikka_;
    sijainti sij_;
    char suunta_;

};

#endif // AMMUS_H
