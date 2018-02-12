#ifndef PELINLOPETUSIKKUNA_H
#define PELINLOPETUSIKKUNA_H

#include <QDialog>

/**
 * @brief pelinLopetusIkkuna käynnistää koko pelin lopetusikkuna,
 * johon näytetään pelaajan keräämät pisteet ja tuhoamat parkkihallit.
 */

namespace Ui {
class pelinLopetusIkkuna;
}

class pelinLopetusIkkuna : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Rakentaja
     */
    explicit pelinLopetusIkkuna(QWidget *parent = 0);

    /**
     * @brief Purkaja
     */
    ~pelinLopetusIkkuna();

    /**
     * @brief lopetaPeli avaa lopetusikkuna
     * @param bool peliVoitettu: true, jos peli voitettiin
     * false, jos peli keskeytettiin.
     * @param unsigned int pisteet: pisteet, jotka pelaaja keräsi pelin aikana
     * @param unsingend int tuhotutParkkihallit: tuhottujen parkkihallien
     * lukumäärä
     */
    void lopetaPeli(bool peliVoitettu,
                    unsigned int pisteet, unsigned int tuhotutParkkihallit);

private:
    Ui::pelinLopetusIkkuna *ui;
};

#endif // PELINLOPETUSIKKUNA_H
