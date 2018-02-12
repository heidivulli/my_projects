#ifndef PARKKIHALLILOPETUSIKKUNA_H
#define PARKKIHALLILOPETUSIKKUNA_H

#include <QDialog>
/**
 * @brief parkkihallinLopetusIkkuna avaa ikkunan
 * parkkihallipelin loputtuessa. Käyttäjällä näytettävä
 * teksti riippuu, onko pelaaja hävinnyt, voittanut vai
 * keskeyttänyt pelin.
 */

namespace Ui {
class parkkihalliLopetusIkkuna;
}

class parkkihalliLopetusIkkuna : public QDialog
{
    Q_OBJECT

public:
    explicit parkkihalliLopetusIkkuna(QWidget *parent = 0);
    ~parkkihalliLopetusIkkuna();
    /**
     * @brief peliHavittu avaa ikkuna siinä tilanteessa, että
     * peli on hävitty.
     * @post parkkihallin lopetus-ikkuna on avattu.
     * @poikkeustakuu perus.
     */

    void peliHavittu();

    /**
     * @brief peliVoitettu avaa ikkunan siinä tapauksessa,
     * että peli on voitettu
     * @param vihollistenLukumaara: tuhottujen vihollisten
     * lukumaara.
     * @param pisteita: saatujen pisteiden lukumäärä.
     * @param rahaa: ansaittujen rahan lukumäärä.
     * @param teekkarikyborgejaElossa: elossa olevien
     * teekkarikyborgien lukumäärä.
     * @post parkkihallin lopetus-ikkuna on avattu.
     * @poikkeustakuu perus.
     */
    void peliVoitettu(int vihollistenLukumaara, int pisteita,
                      int rahaa, int teekkarikyborgejaElossa);
    /**
     * @brief peliKeskeytetty avaa ikkunan siinä tapauksessa,
     * että käyttäjä lopettaa pelin kesken.
     * @post parkkihallin lopetus-ikkuna on avattu
     * @poikkeustakuu perus.
     */
    void peliKeskeytetty();




private:
    Ui::parkkihalliLopetusIkkuna *ui;
};

#endif // PARKKIHALLILOPETUSIKKUNA_H
