#include "kauppaikkuna.h"
#include "ui_kauppaikkuna.h"

KauppaIkkuna::KauppaIkkuna(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::KauppaIkkuna)
{
    ui->setupUi(this);

    QObject::connect(ui->ostaKilpi,SIGNAL(clicked()),this,SLOT(kilpiNappi()));
    QObject::connect(ui->ostaHaulikko,SIGNAL(clicked()),this,SLOT(haulikkoNappi()));
    QObject::connect(ui->ostaKivaari,SIGNAL(clicked()),this,SLOT(kivaariNappi()));
    QObject::connect(ui->palaaNappi,SIGNAL(clicked()),this,SLOT(suljeKauppa()));

}

KauppaIkkuna::~KauppaIkkuna()
{
    delete ui;
}

void KauppaIkkuna::rahanMaara(int rahat)
{
    //asetetaan käytössä oleva raha kauppaIkkunaan näkyville
    ui->rahaNaytto->setProperty("value", rahat);
}

void KauppaIkkuna::mitaVoiOstaa(int rahat)
{
    //rahaa ostaa mikä tahansa tuote kaupasta
    if (rahat >= 2000) {
        ui->ostaKilpi->setEnabled(true);
        ui->ostaHaulikko->setEnabled(true);
        ui->ostaKivaari->setEnabled(true);
    }
    //rahaa ostaa kilpi tai haulikko
    else if (rahat >= 1000) {
        ui->ostaKilpi->setEnabled(true);
        ui->ostaHaulikko->setEnabled(true);
        ui->ostaKivaari->setEnabled(false);

    }
    //rahaa ostaa pelkkä kilpi
    else if (rahat >= 500) {
        ui->ostaKilpi->setEnabled(true);
        ui->ostaHaulikko->setEnabled(false);
        ui->ostaKivaari->setEnabled(false);

    }
    //ei ole varaa ostaa mitään
    else {
        ui->ostaKilpi->setEnabled(false);
        ui->ostaHaulikko->setEnabled(false);
        ui->ostaKivaari->setEnabled(false);

    }

}

void KauppaIkkuna::mitaOstettu(int ase, bool kilpi)
{
    //Lauralla on jo kilpi
    if (kilpi){
        ui->ostaKilpi->setEnabled(false);
    }
    //Lauralla kivaari, ei voi ostaa samaa tai huonompaa asetta
    if (ase == 2) {
        ui->ostaHaulikko->setEnabled(false);
        ui->ostaKivaari->setEnabled(false);
    }
    //Lauralla haulikko, ei voi ostaa samaa asetta
    if (ase == 1) {
        ui->ostaHaulikko->setEnabled(false);
    }
}

void KauppaIkkuna::kilpiNappi()
{

    emit kilpiNappiPainettu();
}

void KauppaIkkuna::haulikkoNappi()
{

    emit haulikkoNappiPainettu();
}

void KauppaIkkuna::kivaariNappi()
{

    emit kivaariNappiPainettu();
}

void KauppaIkkuna::suljeKauppa()
{
    this->close();

    //palautetaan jäljelle jääneet rahat kaupungille
    int loputRahat = ui->rahaNaytto->value();
    emit kauppaSuljettu(loputRahat);
}
