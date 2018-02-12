#ifndef RUUTU_H
#define RUUTU_H

#include "este.h"
#include "sijainti.h"
#include "toimijaRP.h"

#include <memory>



/**
 * @brief ruutu pitää kirjaa yksittäisen ruudun sijainnista ja siitä, mitä
 * ruudussa on. Yhden ruudun koko on 75x75.
 */

class ruutu {
public:
    
    /**
     * @brief Rakentaja
     * @post Ruutu saa alussa sijaintinsa ruudukossa.
     */
    ruutu();

    /**
      * @brief Purkaja.
      */
    ~ruutu();

    /**
     * @brief annaToimija antaa ruudussa olevan toimijan.
     * @return palauttaa ruudussa olevan toimijan. Jos toimijaa ei ole,
     * palauttaa nullptr.
     * Poikkeustakuu: nothrow.
     */
    std::shared_ptr<toimijaRP> annaToimija() const;

    /**
     * @brief annaEste antaa ruudussa olevan esteen.
     * @return palauttaa ruudussa olevan esteen. Jos estettä ei ole,
     * palauttaa nullptr.
     * Poikkeustakuu: nothrow.
     */
    std::shared_ptr<este> annaEste() const;

    /**
     * @brief annaSijainti metodi palauttaa ruudun sijainnin
     * @return ruudun sijainti
     */
    std::shared_ptr<sijainti> annaSijainti() const;

    /**
     * @brief annaVaakaNumero antaa ruudun vaakanumeron.
     * @return palauttaa ruudun vaakanumeron.
     * Poikkeustakuu: nothrow.
     */
    int annaVaakaNumero() const;

    /**
     * @brief annaPystyNumero antaa ruudun pystynumeron.
     * @return palauttaa ruudun pystynumeron.
     * Poikkeustakuu: nothrow.
     */
    int annaPystyNumero() const;

    /**
     * @brief asetaEste asettaa esteen ruutuun.
     * @param este, joka halutaan asettaa
     * @post este on asetettu.
     * Poikkeustakuu: nothrow.
     */
    void asetaEste(std::shared_ptr<este> este);
    
    /**
     * @brief asetaToimija asettaa toimijan ruutuun
     * @pre ruudussa ei ole toimijaa
     * @post Toimija on ruudussa.
     * Poikkeustakuu: vahva.
     */
    void asetaToimija(std::shared_ptr<toimijaRP> toimija);

    /**
     * @brief asetaSijainti asettaa ruudun sijainnin.
     * @post
     * Poikkeustakuu: nothrow.
     */
    void asetaSijainti(std::shared_ptr<sijainti> sij, int pysty, int vaaka);


    /**
     * @brief poistaa toimijan ruudusta
     * @pre ruudussa on toimija.
     * @post Toimija on poistettu, tämän jälkeen onkoRuudussa() palauttaa
     * `false`. Poikkeustakuu: perus.
     */
    void poistaKomponentti();
    
    /**
     * @brief onkoRuudussa kertoo, onko ruudussa toimija. Käytetään
     * phalli-ikkunassa.
     * @pre -
     * @return 'true', jos ruudussa toimija, muuten 'false'.
     * @post Poikkeustakuu: nothrow.
     */
    bool onkoRuudussa() const;

private:
    std::shared_ptr<toimijaRP> toimija_;
    std::shared_ptr<este> este_;
    std::shared_ptr<sijainti> sijainti_;

    int vaakaNumero_;
    int pystyNumero_;
};


#endif // RUUTU_H
