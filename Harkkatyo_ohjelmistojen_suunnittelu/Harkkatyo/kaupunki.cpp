#include "kaupunki.h"
#include "kaupunkiikkuna.h"
#include "laura.h"
#include "lataatiedosto.h"
#include "mainwindow.h"
#include "parkkihalliikkuna.h"
#include "pelinlopetusikkuna.h"
#include "sijainti.h"
#include "virheikkuna.h"
#include "xmlparkkihallireader.h"

#include <cmath>
#include <QGraphicsPixmapItem>
#include <QObject>





kaupunki::kaupunki(std::shared_ptr<kaupunkiIkkuna> kIkkuna):
    kaupunkiIkkuna_{kIkkuna},lahellaOlevaParkkihalli_{nullptr},peliAlustustilassa_{true},
    phalliIkkuna_{new parkkihalliIkkuna}, kauppaIkkuna_{new KauppaIkkuna}
{

    QObject::connect(kaupunkiIkkuna_.get(),SIGNAL(phalliNappiPainettu()),this,SLOT(siirryParkkihalliin()));

    //Nyt phalliIkkuna antaa signaalin kaupungille
    QObject::connect(phalliIkkuna_.get(),SIGNAL(phalliLoppunut()),this,SLOT(avaaKikkunaUudestaan()));
    //kaupunkiIkkunassa painettiin kauppa-nappia
    QObject::connect(kaupunkiIkkuna_.get(),SIGNAL(kauppaNappiPainettu()),this,SLOT(siirryKauppaan()));
    //kauppaIkkunassa painattiin palaa-nappia
    QObject::connect(kauppaIkkuna_.get(),SIGNAL(kauppaSuljettu(int)),this, SLOT(palaaKaupasta(int)));
    QObject::connect(kaupunkiIkkuna_.get(),SIGNAL(lopetaNappiPainettu()),this,SLOT(lopetaPeli()));
}

kaupunki::~kaupunki()
{

}

void kaupunki::onkoParkkihalliLahella(sijainti sij)
{
    int lauranX = sij.annaX() + 42;
    int lauranY = sij.annaY() + 33;

    //käydään läpi kaikki parkkihallit
    //verrataan niiden sijaintia lauran sijaintiin
    for(unsigned int i = 0; i < parkkihallit_->size(); ++i){
        sijainti pSijainti = parkkihallit_->at(i)->annaSijainti();
        int x = pSijainti.annaX();
        int y = pSijainti.annaY();

        //lasketaan parkkihallin x-suuntainen etäisyys laurasta
        int matkaX = std::abs(lauranX - x);
        if (matkaX < 10) {

            //lasketaan parkkihallin y-suuntainen etäisyys laurasta
            int matkaY = std::abs(lauranY -y);
            if (matkaY < 10) {

                //laura on tarpeeksi lähellä parkkihallia,
                //aktivoidaan menePhalliin-nappi
                if(!(parkkihallit_->at(i))->onkoTuhottu()){
                    kaupunkiIkkuna_->phalliNapinTila(true);
                }

                lahellaOlevaParkkihalli_ = parkkihallit_->at(i);
                kaupunkiIkkuna_ ->paivitaParkkihallinTiedot(lahellaOlevaParkkihalli_);
                return;
            }
        }


    }
    //mikään parkkihalli ei ollut tarpeeksi lähellä lauraa
    kaupunkiIkkuna_->phalliNapinTila(false);
    if(lahellaOlevaParkkihalli_ != nullptr){
        lahellaOlevaParkkihalli_ = nullptr;
        kaupunkiIkkuna_ ->paivitaParkkihallinTiedot(lahellaOlevaParkkihalli_);
    }

}

void kaupunki::siirryParkkihalliin() {


    //tarkasetaan että lähellä oleva parkkihalli on tallennettu ja parkkihalli ei ole
    //tuhottu
    if (lahellaOlevaParkkihalli_ != nullptr &&
            !lahellaOlevaParkkihalli_->onkoTuhottu()){
        int ase{std::dynamic_pointer_cast<laura> (laura_)->annaAse()};
        int kilpi{std::dynamic_pointer_cast<laura> (laura_)->onkoKilpi()};
        std::shared_ptr<phalliLogiikka> phallilogiikka{
            new phalliLogiikka(ase,kilpi,phalliIkkuna_,lahellaOlevaParkkihalli_,
                               tilasto_)};
        phallilogiikka_ = phallilogiikka;


        QImage hallikartta(":/new/prefix1/Kuvat/parkkihalliTausta.png");

        phallilogiikka_->asetaRuudukko();

        if(!phallilogiikka_->lueEsteet()){
                return;
        }

        // asetaTausta on pakko tehdä ennen toimijoiden asetusta!!!
        phallilogiikka_->asetaTausta(hallikartta);
        phallilogiikka_->asetaToimijat();
        phallilogiikka_->asetaEsteet();

        phallilogiikka_->phalliPeliAlkaa();
    }
    else{
        //tapahtui jokin virhe
    }

}


void kaupunki::asetaTausta(QImage &taustakuva){
    QGraphicsPixmapItem *item =
            new QGraphicsPixmapItem(QPixmap::fromImage(taustakuva));
    kaupunkiIkkuna_->asetaTausta(item);

}

void kaupunki::asetaParkkihalli()
{

    //käydään kaikki vektorin alkiot läpi
    unsigned int indeksi {0};
    while(indeksi < parkkihallit_->size()){
        kaupunkiIkkuna_->asetaParkkihalli(parkkihallit_->at(indeksi));
        ++ indeksi;
    }
}

void kaupunki::lopetaPeli()
{
    std::shared_ptr<pelinLopetusIkkuna>
            lopetusIkkuna{new pelinLopetusIkkuna};
    lopetusIkkuna->lopetaPeli(onkoPeliLoppunut(),tilasto_->annaPisteet(false),
                              tilasto_->annaTuhotutParkkihallit());
}



bool kaupunki::haeParkkihallit(const QString & tiedostoString)
{

    //tänne päädytään jos haetaan parkkihallit ensimmäistä kertaa
    if(parkkihallit_ == nullptr){
        std::shared_ptr<std::vector <std::shared_ptr<parkkihalli>>>phalli
        {new std::vector<std::shared_ptr<parkkihalli>>};
        parkkihallit_ = phalli;
    }
    xmlParkkihalliReader xmlReader(parkkihallit_);
    std::shared_ptr<QFile> tiedosto {new QFile(tiedostoString)};
    //Jos annettua tiedostoa ei ole valmiiksi, luetaan tiedot API-rajapinnasta.
    if(!tiedosto->exists()){
        lataaTiedosto lataaja;

        std::shared_ptr<QFile> uusiTiedosto {new QFile("./parkkihalliDataApi.xml")};
        if(!uusiTiedosto->exists()){
            std::shared_ptr<virheIkkuna> uusiVirheIkkuna {new virheIkkuna()};
            uusiVirheIkkuna->virheTapahtui(
                        "Tiedostoa parkkihalliDataApi.xml ei löydy hakemistosta!");
            return false;
        }
        tiedosto = uusiTiedosto;
        lataaja.lataa(tiedosto);
    }


    if(!tiedosto->open(QFile::ReadOnly)){
        std::shared_ptr<virheIkkuna> uusiVirheIkkuna {new virheIkkuna()};
        uusiVirheIkkuna->virheTapahtui("XML-tiedosto ei avaudu!");
        return false;
    }

   if (!xmlReader.read(tiedosto.get())){
        std::shared_ptr<virheIkkuna> uusiVirheIkkuna {new virheIkkuna()};
        uusiVirheIkkuna->virheTapahtui(
                    "XML-tiedostossa on virhe, eikä sitä voida lukea!");
        return false;

    }
    //palauttaa truen jos kaikki onnistuu
   return true;
}




void kaupunki::asetaTilasto(std::shared_ptr<tilasto> uusiTilasto)
{
    tilasto_ = uusiTilasto;
    tilasto_->asetaParkkihallienMaara(parkkihallit_->size());

}


void kaupunki::peliAlkaa(){
    peliAlustustilassa_ = false;
    kaupunkiIkkuna_ ->showFullScreen();

}

bool kaupunki::onkoPeliLoppunut() const
{
    if(tilasto_->annaTuhotutParkkihallit() ==
            parkkihallit_->size()){
        return true;
    }
    return false;


}


void kaupunki::avaaKikkunaUudestaan() {
    tilasto_->nollaaValiaikaiset();
    kaupunkiIkkuna_->paivitaRahat(tilasto_->annaRaha(false));
    kaupunkiIkkuna_->paivitaPisteet(tilasto_->annaPisteet(false));
    std::dynamic_pointer_cast<laura> (laura_)->nollaaKilpi();

    if(onkoPeliLoppunut()) {
        lopetaPeli();
        return;
    } else {
        phallilogiikka_ = nullptr;

        //haetaan API-rajapinnasta uudet tiedot
        haeParkkihallit("");
        //asetetaan muuttunueet vaikeusaste kuvat/tuhoutuneet kuvat
        unsigned int indeksi {0};
        while(indeksi < parkkihallit_->size()){
           kaupunkiIkkuna_->paivitaParkkihallinKuva(parkkihallit_->at(indeksi));
            ++ indeksi;
        }
        //päivitetään tiedot
        kaupunkiIkkuna_ ->paivitaParkkihallinTiedot(lahellaOlevaParkkihalli_);
        //laitetaan nappula falseksi
        if(lahellaOlevaParkkihalli_->onkoTuhottu()){
            kaupunkiIkkuna_->phalliNapinTila(false);
        }
        else{
            kaupunkiIkkuna_->phalliNapinTila(true);
        }
        kaupunkiIkkuna_->showFullScreen();
    }

}

void kaupunki::siirryKauppaan()
{
    //annetaan kaupalle pelaajan rahat
    int rahat = tilasto_->annaRaha(false);
    std::shared_ptr<Kauppa> uusiKauppa{new Kauppa(kauppaIkkuna_, rahat, laura_)};
    kauppa_ = uusiKauppa;

    kauppa_->kauppaAukeaa();

}

void kaupunki::palaaKaupasta(int loputRahat)
{
    kaupunkiIkkuna_->showFullScreen();
    kauppa_ = nullptr;

    //päivitetään rahatiedot
    int rahaaEnnenOstoksia = tilasto_->annaRaha(false);
    int rahanMuutos = loputRahat - rahaaEnnenOstoksia;
    tilasto_->paivitaRahat(rahanMuutos,false);

    kaupunkiIkkuna_->paivitaRahat(tilasto_->annaRaha(false));
}

void kaupunki::asetaLaura(std::shared_ptr<toimijaRP> uusiLaura)
{
    //asetetaan lauran sijainti
    sijainti lauranSijainti;
    lauranSijainti.asetaXY(100, 100);
    uusiLaura->asetaSijainti(lauranSijainti);

    laura_ = uusiLaura;

    kaupunkiIkkuna_->asetaLauranKuva(uusiLaura);

}

void kaupunki::asetaKaupanSijainti()
{
    //asetetaan kaupan sijainti kartalla
    sijainti kaupanSijainti;
    kaupanSijainti.asetaXY(600, 180);
    kaupanSijainti_ = kaupanSijainti;

    kaupunkiIkkuna_->asetaKaupanKuva(kaupanSijainti);
}

void kaupunki::onkoKauppaLahella(sijainti sij)
{
    //lauran sijainti
    int lauranX = sij.annaX() + 42;
    int lauranY = sij.annaY() + 33;

    //kaupan sijainti
    sijainti kaupanSijainti = kaupanSijainti_;
    int kaupanX = kaupanSijainti.annaX();
    int kaupanY = kaupanSijainti.annaY();

    //tarkistetaan, onko Laura tarpeeksi lähellä kauppaa
    int matkaX = std::abs(lauranX - kaupanX);
    if ( matkaX < 20) {

        int matkaY = std::abs(lauranY - kaupanY);
        if (matkaY < 20) {
            //kauppa oli tarpeeksi lähellä
            kaupunkiIkkuna_->kauppaNapinTila(true);
            return;
        }
    }
    //kauppa ei ollut tarpeeksi lähellä
    kaupunkiIkkuna_->kauppaNapinTila(false);


}






