#include "peli_ikkuna.h"
#include "ui_peli_ikkuna.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QImage>

peli_ikkuna::peli_ikkuna(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::peli_ikkuna)
{
    ui->setupUi(this);
    //Tehdään scene. Scene on myös privatessa
    scene = new QGraphicsScene(this);

    //Muutetaan väriä
    this->setStyleSheet("background-color: lightblue;");

    //Tehdään kartan kuvasta QGraphicsPixmapItem osoitin
    QImage pkartta(":/new/prefix1/kartta_pieni_500x500.png");
    pkartta.setOffset(QPoint(0,0));
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap::fromImage(pkartta));
    //asetetaan kartta sceneen
    scene ->addItem(item);
    //asetetaan scene pelikartalle
    ui->pelikartta->setScene(scene);

    //Lopetusnappi sulkee ohjelman
    QObject::connect(ui->lopetaNappi,SIGNAL(clicked()),this,SLOT(close()));
}

peli_ikkuna::~peli_ikkuna()
{
    delete ui;
}
