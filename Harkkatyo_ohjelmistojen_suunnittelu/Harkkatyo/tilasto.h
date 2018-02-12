#ifndef TILASTO_H
#define TILASTO_H

#include <memory>
#include <vector>


/**
 * @brief tilasto on luokka, jonka avulla pidetään kirjaa pelitilanteesta:
 * pisteistä, rahamäärästä, (tuhotuista) parkkihalleista, tuhotuista
 * vihollisista.
 */

class tilasto {

public:
    
    /**
      * @brief Rakentaja.
      * @post Alussa pistetilasto on nollattu.
      */
    tilasto();
    
    /**
      * @brief Purkaja.
      */
    ~tilasto();

    /**
     * @brief annaParkkihallit palauttaa parkkihallien määrän pelissä.
     * @pre -
     * @return parkkihallien määrä pelissä
     * @post Poikkeustakuu: nothrow
     */
    unsigned int annaParkkihallit() const;
    
    /**
     * @brief annaPisteet palauttaa pelaajan pistemäärän.
     * @param bool, jonka arvo on true, jos käsitellään väliaikaisia pisteitä.
     * Muuten false.
     * @return pistemäärä
     * @post Poikkeustakuu: nothrow
     */
    // onkoVA on true, jos kyseessä väliaikaiset pisteet. Muuten false.
    int annaPisteet(bool onkoVA) const;

    /**
     * @brief annaRaha palauttaa pelaajan rahamäärän.
     * @param bool, jonka arvo on true, jos käsitellään väliaikaisia pisteitä.
     * Muuten false.
     * @return rahamäärä
     * @post Poikkeustakuu: nothrow
     */
    int annaRaha(bool onkoVA) const;

    /**
     * @brief annaTuhotutParkkihallit palauttaa tuhottujen parkkihallien määrän.
     * @return tuhotut parkkihallit lkm
     * @post Poikkeustakuu: nothrow
     */
    unsigned int annaTuhotutParkkihallit() const;

    /**
     * @brief annaTuhotutViholliset palauttaa tuhottujen vihollisten määrän.
     * @param bool, jonka arvo on true, jos käsitellään väliaikaisia pisteitä.
     * Muuten false.
     * @return tuhotut viholliset lkm
     * @post Poikkeustakuu: nothrow
     */
    int annaTuhotutViholliset(bool onkoVA) const;

    /**
     * @brief nollaaValiaikaiset nollaa väliaikaiset muuttujat..
     * @post Väliaikaiset muuttujat on nollattu.
     * Poikkeustakuu: nothrow
     */
    void nollaaValiaikaiset();

    /**
     * @brief parkkihalliTuhoutui ilmoittaa, että parkkihalli on tuhottu. Lisää pelaajan
     * pisteitä ja rahamäärää.
     * @pre -
     * @post Piste- ja rahamäärä on kasvanut. Poikkeustakuu: vahva
     */
    void parkkihalliTuhoutui();

    /**
     * @brief vihollinenTuhoutui ilmoittaa, että vihollinen on tuhottu. Lisää pelaajan pisteitä.
     * @param kokonaislukuna tuhoutuneiden vihollisten määrä.bool, jonka arvo
     * on true, jos käsitellään väliaikaisia pisteitä.Muuten false.
     * @post Vihollisen/vihollisten tuhoutuminen on tilastoitu.
     * Poikkeustakuu: nothrow.
     */
    void vihollinenTuhoutui(int maara,bool onkoVA);

    /**
     * @brief asetaParkkihallienMaara asettaa parkkihallien lukumäärän
     * private-muuttujaan.
     * @param parkkihallien määrä kokonaislukuna.
     * @post Parkkihallien määrä on asetettu.
     * Poikkeustakuu: nothrow
     */
    void asetaParkkihallienMaara(int parkkihallinenMaara);

    /**
     * @brief paivitaPisteet päivittää pisteiden määrän.
     * @param pisteet, jotka lisätään aikaisempiin pisteisiin. bool, jonka arvo
     * on true, jos käsitellään väliaikaisia pisteitä.Muuten false.
     * @post Pisteet ovat päivitetty.
     * Poikkeustakuu: nothrow
     */
    void paivitaPisteet(int pisteet, bool onkoVA);

    /**
     * @brief paivitaRahat päivittää rahan määrän.
     * @param rahamäärä, joka lisätään aikaisempaan rahamäärään. bool, jonka
     * arvo on true, jos käsitellään väliaikaisia pisteitä. Muuten false.
     * @post Raha on päivitetty.
     * Poikkeustakuu: nothrow
     */
    void paivitaRahat(int rahat, bool onkoVA);

private:
    unsigned int parkkihalleja_;
    unsigned int pisteet_;
    unsigned int raha_;
    unsigned int tuhotutParkkihallit_;
    unsigned int tuhotutViholliset_;
    // Valiaikaiset muuttujat, joita kaytetaan parkkihallissa.
    int vaPisteet_;
    int vaRaha_;
    int vaTuhotutViholliset_;
};


#endif // TILASTO_H
