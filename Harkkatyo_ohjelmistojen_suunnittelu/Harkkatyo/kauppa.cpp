#include "kauppa.h"
#include "laura.h"

Kauppa::Kauppa(std::shared_ptr<KauppaIkkuna> kauppaIkkuna, int rahat,
               std::shared_ptr<toimijaRP> kaupanLaura): kaupanIkkuna_{kauppaIkkuna},
               rahat_{rahat}, laura_{kaupanLaura}
{
    QObject::connect(kaupanIkkuna_.get(),SIGNAL(kilpiNappiPainettu()),this,SLOT(ostaKilpi()));
    QObject::connect(kaupanIkkuna_.get(),SIGNAL(haulikkoNappiPainettu()),this,SLOT(ostaHaulikko()));
    QObject::connect(kaupanIkkuna_.get(),SIGNAL(kivaariNappiPainettu()),this,SLOT(ostaKivaari()));
}

Kauppa::~Kauppa()
{

}

void Kauppa::kauppaAukeaa()
{

    //asetetaan kauppaikkunaan näkyviin käytettävissä oleva raha
    kaupanIkkuna_->rahanMaara(rahat_);

    //sekä mitä pystyy rahalla ostamaan
    kaupanIkkuna_->mitaVoiOstaa(rahat_);

    //ei myöskään voi ostaa sitä, mitä Lauralla jo on
    int lauranAse = std::dynamic_pointer_cast<laura> (laura_)->annaAse();
    bool kilpi = std::dynamic_pointer_cast<laura> (laura_)->onkoKilpi();
    kaupanIkkuna_->mitaOstettu(lauranAse, kilpi);

    kaupanIkkuna_->show();

}

void Kauppa::ostaKilpi()
{
    std::dynamic_pointer_cast<laura> (laura_)->kilpiOstettu();
    //päivitetään rahat
    rahat_ -= 500;

    //päivitetään kauppaikkunan rahamaara
    kaupanIkkuna_->rahanMaara(rahat_);

    //sekä mitä voidaan rahalla ostaa
    kaupanIkkuna_->mitaVoiOstaa(rahat_);

    //lauralle kilpi
    int lauranAse = std::dynamic_pointer_cast<laura> (laura_)->annaAse();
    bool kilpi = true;
    //kilpeä ei voi enää ostaa tällä kertaa
    kaupanIkkuna_->mitaOstettu(lauranAse, kilpi);
}

void Kauppa::ostaHaulikko()
{
    std::dynamic_pointer_cast<laura> (laura_)->uusiAse(1);
    //päivitetään rahat
    rahat_ -= 1000;

    //päivitetään kauppaikkunan rahamaara
    kaupanIkkuna_->rahanMaara(rahat_);

    //sekä mitä voidaan rahalla ostaa
    kaupanIkkuna_->mitaVoiOstaa(rahat_);

    //lauralle haulikko
    int lauranAse = 1;
    bool kilpi = std::dynamic_pointer_cast<laura> (laura_)->onkoKilpi();
    //haulikkoa ei voi enää ostaa
    kaupanIkkuna_->mitaOstettu(lauranAse, kilpi);
}

void Kauppa::ostaKivaari()
{
    std::dynamic_pointer_cast<laura> (laura_)->uusiAse(2);
    //päivitetään rahat
    rahat_ -= 2000;

    //päivitetään kauppaikkunan rahamaara
    kaupanIkkuna_->rahanMaara(rahat_);

    //sekä mitä voidaan rahalla ostaa
    kaupanIkkuna_->mitaVoiOstaa(rahat_);

    //lauralle kivaari
    int lauranAse = 2;
    bool kilpi = std::dynamic_pointer_cast<laura> (laura_)->onkoKilpi();
    //kivaaria ei voi enää ostaa
    kaupanIkkuna_->mitaOstettu(lauranAse, kilpi);
}
