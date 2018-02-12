#ifndef PARKKIHALLIIKKUNA_H
#define PARKKIHALLIIKKUNA_H

#include "ammus.h"
#include "este.h"
#include "teekkarikyborgi.h"
#include "toimijaRP.h"
#include "vihollinen.h"

#include <QMainWindow>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <memory>
#include <vector>


/**
 * @brief Määrittää parkkihalliIkkunan, mikä näyttää parkkihalli-näkymän
 * UI:n.
 */

namespace Ui {
class parkkihalliIkkuna;
}


class parkkihalliIkkuna : public QMainWindow
{
    Q_OBJECT

public:
    /**
      * @brief Rakentaja.
      */
    explicit parkkihalliIkkuna(QWidget *parent = 0);

    /**
      * @brief Purkaja.
      */
    ~parkkihalliIkkuna();

    /**
     * @brief asetaTausta asettaa parkkihalliin taustakuvan.
     * @param taustakuva, parkkihallin pelialueena käytettävä karttakuva.
     * @post Parkkihallin taustakuva on asetettu. Poikkeustakuu: vahva.
     */
    void asetaTausta(QGraphicsPixmapItem *item);

    /**
     * @brief asetaUImuut asettaa parkkihalliin aktiivisen aseen, kilven (jos
     * se on ostettu) ja kaikki napit aktiivisiksi.
     * @param ase, joka on aktiivinen (0 = pistooli, 1 = kivääri, 2 = haulikko),
     * sekä kilven (false = kilpeä ei ole, true = kilpi on ostettu).
     * @post Napit ovat aktiivisia ja ase, sekä kilpi on asetettu.
     * Poikkeustakuu: vahva.
     */
    void asetaUImuut(int ase, bool kilpi);

    /**
     * @brief asetaKuvaLaura asettaa parkkihalliin Lauran kuvan.
     * @param osoitin toimijaan Laura.
     * @post Lauran kuva on asetettu. Poikkeustakuu: vahva.
     */
    void asetaKuvaLaura(std::shared_ptr<toimijaRP> &laura);

    /**
     * @brief asetaKuvaKyborgi1 asettaa parkkihalliin kyborgi1:n kuvan.
     * @param osoitin toimijaan kyborgi1.
     * @post Kyborgi1:n kuva on asetettu. Poikkeustakuu: vahva.
     */
    void asetaKuvaKyborgi1(std::shared_ptr<toimijaRP> &kyborgi1);

    /**
     * @brief asetaKuvaKyborgi2 asettaa parkkihalliin kyborgi2:n kuvan.
     * @param osoitin toimijaan kyborgi2.
     * @post Kyborgi2:n kuva on asetettu. Poikkeustakuu: vahva.
     */
    void asetaKuvaKyborgi2(std::shared_ptr<toimijaRP> &kyborgi2);

    /**
     * @brief asetaToimija asettaa parkkihalliin sankarin (Laura ja kyborgit)
     * kerrallaan.
     * @param osoitin asetettavaan toimijaan.
     * @post Toimijan sijainti, fokus ja pyörimispiste on asetettu.
     * Toimija piirretty ui:seen.
     * Poikkeustakuu: vahva.
     */
    void asetaToimija(std::shared_ptr<toimijaRP> &toimija);

    /**
     * @brief asetaVihollinen asettaa parkkihalliin vihollisen kerrallaan.
     * @param osoitin asetettavaan viholliseen.
     * @post Vihollisen kuva, sijainti, fokus ja pyörimispiste on asetettu.
     * Vihollinen piirrettu ui:seen.
     * Poikkeustakuu: vahva.
     */
    void asetaVihollinen(std::shared_ptr<vihollinen> &vihollinen);

    /**
     * @brief asetaEste asettaa parkkihalliin esteen.
     * @param osoitin asetettavan esteen ruutuun.
     * @post Esteen kuva ja sijainti määritetty. Este piirretty ui:seen.
     * Poikkeustakuu: vahva.
     */
    void asetaEste(std::shared_ptr<ruutu> esteRuutu);

    /**
     * @brief asetaAmmus asettaa ammuksen parkkihalliIkkunan ui:seen.
     * @param ammuksen kuva, osoitin asetettavaan ammukseen, ammuksen sijainti
     * x- ja y-komponentteina, sekä ammuksen suunta.
     * @post Ammuksen kuva, sijainti, fokus ja pyörimispiste on asetettu.
     * Ammus on piirrettu ui:seen.
     * Poikkeustakuu: vahva.
     */
    void asetaAmmus(QImage kuva,ammus* luoti, int xSijainti, int ySijainti,
                    char suunta);

    /**
     * @brief lauraltaLoppuiToiminnot asettaa ui:ssa näkyvät toimintapisteet
     * nollaksi, tekee Lauran napin ei-klikattavaksi ja vaihtaa taustavärin
     * pois. Palauttaa true, jos jollain sankarilla on toimintapisteitä jäljellä,
     * muuten palauttaa false.
     * @post Lauraa ei voi liikutta phalliIkkunassa.
     * Poikkeustakuu: vahva.
     */
    bool lauraltaLoppuiToiminnot();

    /**
     * @brief kyborgi1LoppuiToiminnot asettaa ui:ssa näkyvät toimintapisteet
     * nollaksi, tekee kybogi1:n napin ei-klikattavaksi ja vaihtaa taustavärin
     * pois. Palauttaa true, jos jollain sankarilla on toimintapisteitä jäljellä,
     * muuten palauttaa false.
     * @post Kyborgi1:sta ei voi liikutta phalliIkkunassa.
     * Poikkeustakuu: vahva.
     */
    bool kyborgi1LoppuiToiminnot();

    /**
     * @brief kyborgi2LoppuiToiminnot asettaa ui:ssa näkyvät toimintapisteet
     * nollaksi, tekee kyborgi2:n napin ei-klikattavaksi ja vaihtaa taustavärin
     * pois. Palauttaa true, jos jollain sankarilla on toimintapisteitä jäljellä,
     * muuten palauttaa false.
     * @post Kybrogi2:sta ei voi liikutta phalliIkkunassa.
     * Poikkeustakuu: vahva.
     */
    bool kyborgi2LoppuiToiminnot();

    /**
     * @brief vaihdaSankariaNapista vaihtaa aktiivisen toimijan sankarista
     * toiseen, jos kohdesankarilla on toimintapisteitä jäljellä.
     * @post sankari on vaihdettu, jos muilla sankareilla on vielä toiminta-
     * pisteitä.
     * Poikkeustakuu: vahva.
     */
    void vaihdaSankariaNapista();

    /**
     * @brief asetaVuoroPelaajalle asettaa vuoron viholliselta takaisin
     * pelaajalle.
     * @pre ui:n napit on asetettu.
     * @post ui:n napit on muutettu takaisin klikattaviksi.
     * Poikkeustakuu: nothrow.
     */
    void asetaVuoroPelaajalle();

    /**
     * @brief tuhoaKyborgi tuhoaa kyborgin ui:sta ja asettaa kyborgiin
     * liittyvät napit ei-klikattaviksi.
     * @param annetaan kyborgin numero (0 = kyborgi1, 1 = kyborgi2, 2 = se
     * kumpaa ei ole vielä tuhottu).
     * @post kyborgin kuva poistettu ui:sta ja kyborgiin liittyvät napit
     * ei-klikattavaksi.
     * Poikkeustakuu: vahva.
     */
    void tuhoaKyborgi(char kyborginNumero);

    /**
     * @brief onkoKyborgi1Kuollut kertoo, onko kyborgi1 elossa vai ei.
     * Palauttaa true, jos kyborgi1 on kuollut. Muuten palauttaa false.
     * Poikkeustakuu: nothrow.
     */
    bool onkoKyborgi1Kuollut();

    /**
     * @brief asetaToimintapisteetNaytolle asettaa toimintapisteet ui:n
     * näytölle.
     * @param kyborgin toimintapisteet.
     * @post toimintapisteet on asetettu ui:n näytölle.
     * Poikkeustakuu: nothrow.
     */
    void asetaToimintapisteetNaytolle(int TP);

    /**
     * @brief asetaRahaJaPisteetNaytolle asettaa rahat ja pisteet ui:n
     * näytölle.
     * @param raha ja pisteet, jotka halutaan laittaa näytölle.
     * @post rahat ja pisteet on asetettu ui:n näytölle.
     * Poikkeustakuu: nothrow.
     */
    void asetaRahaJaPisteetNaytolle(int raha, int pisteet);

    /**
     * @brief asetaLauranElamatNaytolle asettaa Lauran elämäpisteet ui:n
     * näytölle.
     * @param elämät, jotka Lauralle halutaan asettaa.
     * @post Lauran elämäpisteet on asetettu ui:n näytölle.
     * Poikkeustakuu: nothrow.
     */
    void asetaLauranElamatNaytolle(int elamat);

    /**
     * @brief asetaKyborgi1ElamatNaytolle asettaa kyborgi1 elämäpisteet ui:n
     * näytölle.
     * @param elämät, jotka Kyborgi1:lle halutaan asettaa.
     * @post Kybrogi1:n elämäpisteet on asetettu ui:n näytölle.
     * Poikkeustakuu: nothrow.
     */
    void asetaKyborgi1ElamatNaytolle(int elamat);

    /**
     * @brief asetaKyborgi2ElamatNaytolle asettaa kybrogi2:n elämäpisteet ui:n
     * näytölle.
     * @param elämät, jotka kyborgi2:lle halutaan asettaa.
     * @post Kybrogi2:n elämäpisteet on asetettu ui:n näytölle.
     * Poikkeustakuu: nothrow.
     */
    void asetaKyborgi2ElamatNaytolle(int elamat);

public slots:  
    /**
     * @brief avaaKikkuna lähettää signaalin phalliLoppunut, jonka avulla
     * avataan kaupunkiIkkuna uudestaan.
     * @post signaali on lähetetty
     * Poikkeustakuu: vahva.
     */
    void avaaKikkuna();

    /**
     * @brief asetaVuoroLauralle muuttaa Lauran taustan punaiseksi ja muiden
     * sankarien taustat normaaleiksi. Lähettää signaalin vuoroLauralle.
     * @post Taustavärit on asetettu ja signaali on lähetetty.
     * Poikkeustakuu: vahva.
     */
    void asetaVuoroLauralle();

    /**
     * @brief asetaVuoroKyborgi1:lle muuttaa Kyborgi1:n taustan punaiseksi ja muiden
     * sankarien taustat normaaleiksi. Lähettää signaalin vuoroKybrogi1lle.
     * @post Taustavärit on asetettu ja signaali on lähetetty.
     * Poikkeustakuu: vahva.
     */
    void asetaVuoroKyborgi1();

    /**
     * @brief asetaVuoroKyborgi2:lle muuttaa Kyborgi2:n taustan punaiseksi ja muiden
     * sankarien taustat normaaleiksi. Lähettää signaalin vuoroKybrogi2lle.
     * @post Taustavärit on asetettu ja signaali on lähetetty.
     * Poikkeustakuu: vahva.
     */
    void asetaVuoroKyborgi2();

    /**
     * @brief lopetaOmaVuoroNapista lopettaa käyttäjän vuoron sen jälkeen,
     * kun nappia on painettu ui:ssa.
     * @post Napit on asetettu ei-klikattaviksi ja toimintapisteet on asetettu
     * nollaksi.
     * Poikkeustakuu: vahva.
     */
    void lopetaOmaVuoroNapista();

    /**
     * @brief suljeNappiaPainettu
     * @post
     * Poikkeustakuu:
     */
    void suljeNappiaPainettu();

    /**
     * @brief keyPressEvent hallinnoi näippäimistöstä saatavia signaleja.
     * @param näppäin, jota käyttäjä on painanut pelatessaan peliä.
     * @pre käyttäjä on painanut näppäimistön näppäintä (nuolinäppäimet,
     * enter, return, tab tai välilyönti).
     * @post kutsuu metodia, johon näppäimen painaminen johtaa.
     * Poikkeustakuu: vahva.
     */
    void keyPressEvent(QKeyEvent *event);

    /**
     * @brief vuoronVaihtoVastustajalle vaihtaa vuoron vastustajalle. Lähettää
     * signaalin vuoroVaihtunut.
     * @post Sankarien tausta UI:ssa on asetettu ei-punaisiksi ja vuoronvaihto-
     * nappi on asetettu ei-klikattavaksi. Lähettää signaalin.
     * Poikkeustakuu: vahva.
     */
    void vuoronVaihtoVastustajalle();


signals:
    /**
     * @brief phalliLoppunut on signaali, joka on lähetetty, kun parkkihallipeli
     * on loppunut. Napataan kaupungissa, jossa sen avulla avataan karttaikkuna
     * uudestaan.
     */
    void phalliLoppunut();

    /**
     * @brief nappaintaPainettuLiiku on signaali, joka on lähetetty, kun
     * käyttäjä painaa näppäimistöltännäppäintä. Tämän avulla liikutetaan
     * sankareita parkkihallissa.
     */
    void nappaintaPainettuLiiku(std::string nappain);

    /**
     * @brief nappaintaPainettuAmmu on signaali, joka on lähetetty, kun
     * käyttäjä on painanut välilyöntiä. Tämän avulla sankarit ampuvat.
     */
    void nappaintaPainettuAmmu();

    /**
     * @brief vuoroLauralle on signaali, joka lähetetään, kun käyttäjä vaihtaa
     * vuoron Lauralle.
     */
    void vuoroLauralle();

    /**
     * @brief vuoroKyborgille1 on signaali, joka lähetetään, kun käyttäjä vaihtaa
     * vuoron Kyborgi1:lle.
     */
    void vuoroKyborgille1();

    /**
     * @brief vuoroKyborgille2 on signaali, joka lähetetään, kun käyttäjä vaihtaa
     * vuoron Kyborgi2:lle.
     */
    void vuoroKyborgille2();

    /**
     * @brief vuoroVaihtunut on signaali, joka lähetetään, kun käyttäjä vaihtaa
     * vuoron vastustajalle.
     */
    void vuoroVaihtunut();
private:
    Ui::parkkihalliIkkuna *ui;
    QGraphicsScene *scene_;

    bool kyborgi1Kuollut_;
    bool kyborgi2Kuollut_;
};


#endif // PARKKIHALLIIKKUNA_H
