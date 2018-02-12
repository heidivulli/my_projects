#include "pelinlopetusikkuna.h"
#include "ui_pelinlopetusikkuna.h"

pelinLopetusIkkuna::pelinLopetusIkkuna(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pelinLopetusIkkuna)
{
    ui->setupUi(this);

    QObject::connect(ui->lopeta, SIGNAL(clicked()),this, SLOT(close()));
}

pelinLopetusIkkuna::~pelinLopetusIkkuna()
{
    delete ui;
}

void pelinLopetusIkkuna::lopetaPeli(bool peliVoitettu,unsigned int pisteet,
                                    unsigned int tuhotutParkkihallit)
{
    QFont font("Arial",20);
    if(!peliVoitettu){
        ui->otsikko->setText("Lopetit pelin!");
        ui->otsikko->setFont(font);
        ui->otsikko->setAlignment(Qt::AlignCenter);
    }
    ui->parkkihalleja->setText("Tuhosit parkkihalleja: " + QString::number(tuhotutParkkihallit));
    ui->pisteet->setText("Keräsit pisteitä: " + QString::number(pisteet));

    this->show();

    QEventLoop eventLoop;
    QObject::connect(ui->lopeta,SIGNAL(clicked()),
                                           &eventLoop, SLOT(quit()));
    eventLoop.exec();
    return;
}
