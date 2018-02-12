#ifndef PELI_IKKUNA_H
#define PELI_IKKUNA_H

#include <QDialog>
#include <QGraphicsScene>

namespace Ui {
class peli_ikkuna;
}

class peli_ikkuna : public QDialog
{
    Q_OBJECT

public:
    explicit peli_ikkuna(QWidget *parent = 0);
    ~peli_ikkuna();

private:
    Ui::peli_ikkuna *ui;
    //laitetaan scenestä osoitin privateen
    QGraphicsScene *scene;
};

#endif // PELI_IKKUNA_H
