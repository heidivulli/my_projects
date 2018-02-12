#ifndef TOIMIJARP_H
#define TOIMIJARP_H

#include "sijainti.h"


/**
 * @brief toimijaRP on rajapintaluokka, jonka jokainen pelin toimija-olio toteuttaa.
 */

class toimijaRP {

public:

    /**
      * @brief Rajapintaluokan oletusrakentaja.
      * @post Toimija ei alussa ole tuhottu-tilassa.
      */
    toimijaRP() = default;

    /**
      * @brief Rajapintaluokassa on oletusarvoinen virtuaalipurkaja.
      */
    virtual ~toimijaRP() = default;

    /**
     * @brief annaSijainti palauttaa komponentin sijainnin.
     * @pre -
     * @return komponentin sijainti.
     * @post Poikkeustakuu: vahva.
     */
    virtual sijainti annaSijainti() const;   
    
    /**
     * @brief asetaSijainti asettaa toimijan annettuun sijaintiin.
     * @param sij Toimijan uusi sijainti.
     * @pre -
     * @post Toimijan sijainti on sij. Poikkeustakuu: vahva.
     */
    virtual void asetaSijainti(sijainti sij);
    
private:

    sijainti sijainti_;

};


#endif // TOIMIJARP_H
