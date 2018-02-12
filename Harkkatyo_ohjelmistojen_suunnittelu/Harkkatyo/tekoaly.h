#ifndef TEKOALY_H
#define TEKOALY_H

#include "phallilogiikka.h"
#include "ruutu.h"
#include "vihollinen.h"

#include <algorithm>
#include <map>
#include <memory>
#include <QObject>
#include <utility>

/**
  * @brief tekoaly on logiikka vihollisten liikkumisen ja ampumisen takana.
  * Se vastaa siis vihollisten liikuttamisesta ja niiden ampumisesta ja
  * tekee sen järkevästi.
  */

class tekoaly: public QObject{
Q_OBJECT

public:
    /**
      * @brief Rakentaja
      */
    tekoaly(std::shared_ptr<phalliLogiikka> pLogiikka);

    /**
      * @brief Purkaja
      */
    ~tekoaly();

    /**
     * @brief liiku vastaa vihollisten liikuttamisesta.
     * @return true, jos liikkuminen onnistui. false, jos liikkuminen epäonnistui.
     * Poikkeustakuu: vahva.
     */
    bool liiku();

    /**
      * @brief ammu vastaa vihollisten ampumisesta.
      * @return true, jos ampuminen onnistui. false, jos ampuminen
      * epäonnistui.
      * Poikkeustakuu: vahva.
      */
    bool ammu();

    /**
      * @brief aloitaTekoaly pyörittää tekoälyä ja kutsuu muita metodeja.
      * @param viholliset, joita tekoäly liikuttaa/laittaa ampumaan. laura,
      * jonka viholliset pyrkivät tuhoamaan. kyborgit, joita viholliset pyrkivät
      * tuhoamaan.
      * @post vihollisia on liikutetta ja niillä on ammuttu, jos vain pystyy.
      * Poikkeustakuu: heikko.
      */
    void aloitaTekoaly(std::vector<std::shared_ptr<vihollinen>>& viholliset,
                       std::shared_ptr<toimijaRP>& laura,
                       std::vector<std::shared_ptr<toimijaRP>> &kyborgit);


private:
    std::shared_ptr<vihollinen> aktiivinenVihollinen_;
    std::shared_ptr<toimijaRP> kohde_;
    std::map<std::pair<int,int>,std::shared_ptr<ruutu>> ruudukko_;

    std::shared_ptr<phalliLogiikka> parkkihalliLogiikka_;
};

#endif // TEKOALY_H
