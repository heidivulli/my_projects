#ifndef VIRHEIKKUNA_H
#define VIRHEIKKUNA_H

#include <QDialog>

/**
 * @brief virheIkkuna luokka avaa virheikkunan, johon
 * käyttäjä voi itse määrittää virheilmoituksen parametrina.
 */

namespace Ui {
class virheIkkuna;
}

class virheIkkuna : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Rakentaja
     */
    explicit virheIkkuna(QWidget *parent = 0);

    /**
     * @brief Purkaja
     */
    ~virheIkkuna();

    /**
     * @brief virheTapahtui avaa virheIkkunan.
     * @param selite, miksi virhe tapahtui.
     */
    void virheTapahtui(QString selite);

private:
    Ui::virheIkkuna *ui;
};

#endif // VIRHEIKKUNA_H
