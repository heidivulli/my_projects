#ifndef SIJAINTI_H
#define SIJAINTI_H


/**
 * @brief Sijainti on luokka, jonka avulla tarkastellaan ja muutetaan pelissä
 * olevien komponenttien sijaintia.
 */

class sijainti {

public:
    
    /**
     * @brief Rakentaja
     */
    sijainti();

    /**
      * @brief Purkaja.
      */
    ~sijainti();
    
    /**
     * @brief annaX palauttaa sijainnin x-koordinaatin.
     * @return x-koordinaatin.
     * @post Poikkeustakuu: nothrow.
     */
    int annaX();
    
    /**
     * @brief annaY palauttaa sijainnin y-koordinaatin.
     * @return y-koordinaatin.
     * @post Poikkeustakuu: nothrow.
     */
    int annaY();
    
    /**
     * @brief asetaXY asettaa sijainnin uuteen paikkaan annettujen koordinaattien perusteella.
     * @param x uuden sijainnin x-koordinaatti
     * @param y uuden sijainnin y-koordinaatti
     * @post Sijainti on päivitetty. Poikkeustakuu: vahva.
     */
    void asetaXY(int x, int y);
    
    /**
     * @brief onkoLahella kertoo, onko annettu sijainti lähellä tätä sijaintia.
     * @param sij sijainti, jonka läheisyyttä tutkitaan.
     * @return 'true', jos sij on lähellä tarkasteltavaa sijaintia, muuten 'false'.
     * @post Poikkeustakuu: nothrow.
     */
    bool onkoLahella(sijainti const &sij) const;

private:
    int x_;
    int y_;
};


#endif // SIJAINTI_H
