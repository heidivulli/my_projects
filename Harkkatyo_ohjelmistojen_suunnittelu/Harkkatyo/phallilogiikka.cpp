#include "ammus.h"
#include "phallilogiikka.h"
#include "phallinapufunktiot.h"
#include "sijainti.h"
#include "tekoaly.h"
#include "virheikkuna.h"
#include "parkkihallilopetusikkuna.h"

#include <string>
#include <vector>
#include <QEventLoop>
#include <QtDebug>

phalliLogiikka::phalliLogiikka(int ase, bool kilpi,
                               std::shared_ptr<parkkihalliIkkuna> phalliIkkuna,
                               std::shared_ptr<parkkihalli> phalli,
                               std::shared_ptr<tilasto> til):
    aktiivinenAse_{ase},
    onkoKilpi_{kilpi},
    parkkihalli_{phalli},
    parkkihalliIkkuna_{phalliIkkuna},
    tilasto_{til}
{
    // Näppäimistä seuraaviin toimintoihin liittyvät SIGNAL-SLOTIT
    QObject::connect(parkkihalliIkkuna_.get(), SIGNAL(vuoroVaihtunut()),
                     this,SLOT(vaihdaVuoroVastustajalle()));
    QObject::connect(parkkihalliIkkuna_.get(),
                     SIGNAL(nappaintaPainettuLiiku(std::string)),
                     this,SLOT(nappainPainettunaLiiku(std::string)));
    QObject::connect(parkkihalliIkkuna_.get(), SIGNAL(nappaintaPainettuAmmu()),
                     this,SLOT(nappainPainettunaAmmu()));

    QObject::connect(parkkihalliIkkuna_.get(),
                     SIGNAL(toimintapisteetLoppuivat()),this,SLOT());

    // Sankarin vaihtamiseen liittyvät SIGNAL-SLOTIT
    QObject::connect(parkkihalliIkkuna_.get(), SIGNAL(vuoroLauralle()),
                     this,SLOT(lauranVuoro()));
    QObject::connect(parkkihalliIkkuna_.get(), SIGNAL(vuoroKyborgille1()),
                     this,SLOT(kyborgi1Vuoro()));
    QObject::connect(parkkihalliIkkuna_.get(), SIGNAL(vuoroKyborgille2()),
                     this,SLOT(kyborgi2Vuoro()));



}

phalliLogiikka::~phalliLogiikka() {

}

//-----Tekoalya ja ammusta varten
std::shared_ptr<toimijaRP> phalliLogiikka::annaAktiivinenToimija(){
    return aktiivinenToimija_;
}

std::map<std::pair<int, int>, std::shared_ptr<ruutu> > phalliLogiikka::annaRuudukko() {
    return ruudukko_;
}



//------

// Asetetaan ruudut ruudukko_-mappiin. Ruutu on 75x75. Koordinaatit ruudun
// vasempaan ylänurkkaan. Tämä asettaa nyt 88 ruutua ruudukkoon (tarkistettu).
// Ruutujen sijainnit alkavat 0:sta.
void phalliLogiikka::asetaRuudukko() {
    int m{0};
    int n;
    // Pystysuunnan ruudun numero
    while (m < 8) {
        // Tähän eka vaaka, sitten pysty
        std::pair<int,int> sijaintiNumeroina;
        n = 0;
        // Vaakasuunnan ruudun numero
        while (n < 11) {
            //sijainti sij;
            std::shared_ptr<ruutu> asetettavaRuutu{new ruutu};
            std::shared_ptr<sijainti> sijaintiKoordinaatteina{new sijainti};
            // Nollakohta on vasemmassa yläkulmassa, sen takia n-1
            //HUOM! Ruudun sijainti on nyt asetettuna sen oikeeseen alanurkkaan!
            sijaintiKoordinaatteina->asetaXY(75*(n),75*(m));
            asetettavaRuutu->asetaSijainti(sijaintiKoordinaatteina,m,n);
            sijaintiNumeroina = std::make_pair(n,m);
            ruudukko_.insert({sijaintiNumeroina,asetettavaRuutu});
            ++ n;
        }
        ++ m;
    }
}


void phalliLogiikka::asetaTausta(QImage &taustakuva) {
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap::fromImage(taustakuva));
    parkkihalliIkkuna_->asetaTausta(item);
    parkkihalliIkkuna_->asetaUImuut(aktiivinenAse_,onkoKilpi_);
}

void phalliLogiikka::asetaEsteet() {
    std::map<std::pair<int,int>,std::shared_ptr<ruutu>>::iterator iterRuutu;
    iterRuutu = ruudukko_.begin();

    while(iterRuutu != ruudukko_.end()){
        if(iterRuutu->second->annaEste() != nullptr){
            parkkihalliIkkuna_-> asetaEste(iterRuutu->second);
        }
        ++iterRuutu;
    }

}

bool phalliLogiikka::lueEsteet() {


    QString tiedosto(":/tekstiTiedostot/esteKonffi.txt");
    QString esteQString = avaaEsteTiedosto(tiedosto);
    if(esteQString == ""){
        std::shared_ptr<virheIkkuna> uusiVirheIkkuna {new virheIkkuna()};
        uusiVirheIkkuna->virheTapahtui("estenKonffi-tiedoston luku epäonnistui");
        return false;

    }

    std::vector<std::string> esteVektori = tarkistaString(esteQString);
    if(esteVektori.size() != 8){
        std::shared_ptr<virheIkkuna> uusiVirheIkkuna {new virheIkkuna()};
        uusiVirheIkkuna->virheTapahtui("esteKonffi-tiedoston formaatti väärä");
        return false;
    }

    std::string rivi;
    for(unsigned int i = 0; i <esteVektori.size();++i){
        rivi = esteVektori.at(i);
        for(unsigned int k = 0; k <rivi.length();++k){
            if(rivi.at(k) == '1'){
                std::map<std::pair<int,int>,std::shared_ptr<ruutu>>::iterator iterRuutu;
                std::pair<int,int> sijaintiNumeroina = std::make_pair((int) k,(int) i);
                iterRuutu = ruudukko_.find(sijaintiNumeroina);
                if(iterRuutu != ruudukko_.end()){
                    std::shared_ptr<este> esteOsoitin{new este()};
                    iterRuutu->second->asetaEste(esteOsoitin);
                }
                else{
                    qDebug()<<"Virhe: Ruudukko ei toimi oikein";
                    std::shared_ptr<virheIkkuna> uusiVirheIkkuna {new virheIkkuna()};
                    uusiVirheIkkuna->virheTapahtui("Esteiden asettaminen ruudukkoon epäonnistui");
                    return false;
                }
            }
        }
    }

    return true;

}

// Luodaan laura ja kaksi kyborgia. Kyborgien sijainnit asetetaan tässä, koska
// en ovat jokaiselle kyborgille hlökohtaiset. Asetetaan laura ja kyborgit
// ruudukkoon.
void phalliLogiikka::asetaToimijat() {
    int elamat{200};
    if (onkoKilpi_) {
        elamat = 300;
    }
    std::shared_ptr<toimijaRP> laura{new teekkariKyborgi(elamat,ruudukko_)};
    sijainti lauranSijainti;
    lauranSijainti.asetaXY(0, 525);
    laura->asetaSijainti(lauranSijainti);
    parkkihalliIkkuna_->asetaKuvaLaura(laura);
    parkkihalliIkkuna_->asetaToimija(laura);
    laskeSijainninRuutu(laura->annaSijainti(), ruudukko_)->asetaToimija(laura);
    phallinLaura_ = laura;
    parkkihalliIkkuna_->asetaLauranElamatNaytolle(elamat);

    std::shared_ptr<toimijaRP> kyborgi1{new teekkariKyborgi(200,ruudukko_)};
    sijainti kyborgi1Sij;
    kyborgi1Sij.asetaXY(0,450);
    kyborgi1->asetaSijainti(kyborgi1Sij);
    parkkihalliIkkuna_->asetaKuvaKyborgi1(kyborgi1);
    parkkihalliIkkuna_->asetaToimija(kyborgi1);
    laskeSijainninRuutu(kyborgi1->annaSijainti(), ruudukko_)
            ->asetaToimija(kyborgi1);
    kyborgit_.push_back(kyborgi1);
    parkkihalliIkkuna_->asetaKyborgi1ElamatNaytolle(200);

    std::shared_ptr<toimijaRP> kyborgi2{new teekkariKyborgi(200,ruudukko_)};
    sijainti kyborgi2Sij;
    kyborgi2Sij.asetaXY(75,525);
    kyborgi2->asetaSijainti(kyborgi2Sij);
    parkkihalliIkkuna_->asetaKuvaKyborgi2(kyborgi2);
    parkkihalliIkkuna_->asetaToimija(kyborgi2);
    laskeSijainninRuutu(kyborgi2->annaSijainti(), ruudukko_)
            ->asetaToimija(kyborgi2);
    kyborgit_.push_back(kyborgi2);
    parkkihalliIkkuna_->asetaKyborgi2ElamatNaytolle(200);

    //asetetaan viholliset!
    int indeksi{0};
    int vihollistenLukuMaara;
    //tarvitaan määrittämään viholliselle paikka
    int ySijainti{0};

    //tallennetaan parkkihallin vaikeus ja koko muuttujaan
    QString parkkihallinVaikeus = parkkihalli_->annaVaikeus();
    QString parkkihallinKoko = parkkihalli_->annaKokoString();

    if (parkkihallinKoko == "Pieni"){
        vihollistenLukuMaara = 3;
    } else if (parkkihallinKoko == "Keskisuuri"){
        vihollistenLukuMaara = 4;
    } else {
        vihollistenLukuMaara = 5;
    }
    while(indeksi < vihollistenLukuMaara){

        //määritetään vastustajan elämät vaikeusasteen mukaan
        int elamat{0};
        int pisteet;
        int raha;
        if (parkkihallinVaikeus == "Helppo"){
            elamat = 100;
            pisteet = 100;
            raha = 50;
        } else if (parkkihallinVaikeus == "Kohtalainen"){
            elamat = 150;
            pisteet = 150;
            raha = 100;
        } else {
            elamat = 200;
            pisteet = 200;
            raha = 150;
        }

        std::shared_ptr<vihollinen> uusiVihollinen{new vihollinen(ruudukko_,elamat,pisteet,raha)};
        sijainti vihollinenSij;
        vihollinenSij.asetaXY(750,ySijainti);
        uusiVihollinen->asetaSijainti(vihollinenSij);
        parkkihalliIkkuna_->asetaVihollinen(uusiVihollinen);
        // Asetetaan toimija ruutuun.
        laskeSijainninRuutu(uusiVihollinen->annaSijainti(), ruudukko_)
                ->asetaToimija(std::dynamic_pointer_cast<toimijaRP> (uusiVihollinen));
        viholliset_.push_back(uusiVihollinen);

        ++indeksi;
        ySijainti = ySijainti + 75;
    }



}

void phalliLogiikka::asetaAktiivinenToimija(std::shared_ptr<toimijaRP> toimija) {
    aktiivinenToimija_ = toimija;
}

void phalliLogiikka::asetaAmmus() {
    std::shared_ptr<teekkariKyborgi> sankari{std::dynamic_pointer_cast<teekkariKyborgi> (aktiivinenToimija_)};
    char suunta;
    if (sankari) {
        suunta = sankari->annaSuunta();
    } else {
        suunta = std::dynamic_pointer_cast<vihollinen> (aktiivinenToimija_)->annaSuunta();
    }

    ammus* luoti{new ammus(shared_from_this(), aktiivinenToimija_)};
    sijainti lahtoKohta{aktiivinenToimija_->annaSijainti()};
    int xSij{lahtoKohta.annaX() + 38};
    int ySij{lahtoKohta.annaY()};
    QImage kuva{":/new/prefix1/Kuvat/luoti.png"};
    if (std::dynamic_pointer_cast<teekkariKyborgi> (aktiivinenToimija_)) {
        if (aktiivinenAse_ == 1) {
            kuva = QImage(":/new/prefix1/Kuvat/luoti2.png");
        } else if (aktiivinenAse_ == 2) {
            kuva = QImage(":/new/prefix1/Kuvat/luoti3.png");
        }
    }
    parkkihalliIkkuna_->asetaAmmus(kuva,luoti,xSij,ySij,suunta);
//    int odotusaika{1};
//    clock_t odota;
//    odota = clock() + odotusaika*CLOCKS_PER_SEC;
//    while(clock() < odota) {
//    }
}


void phalliLogiikka::lopeta() {
    //peli on hävitty
    if (phallinLaura_ == nullptr) {
        std::shared_ptr<parkkihalliLopetusIkkuna>
                uusiLopetusIkkuna(new parkkihalliLopetusIkkuna);
        parkkihalliIkkuna_->close();
        uusiLopetusIkkuna->peliHavittu();

    //peli on voitettu
    } else if(viholliset_.size() == 0) {
        tilasto_->parkkihalliTuhoutui();
        int tuhotutViholliset{tilasto_->annaTuhotutViholliset(true)};
        int pisteita{tilasto_->annaPisteet(true)};
        int rahaa{tilasto_->annaRaha(true)};
        int teekkarikyborgejaElossa;
        //tuhotaan parkkihalli missä oltiin
        parkkihalli_->tuhoa();
        parkkihalliIkkuna_->close();
        teekkarikyborgejaElossa = kyborgit_.size();
        std::shared_ptr<parkkihalliLopetusIkkuna>
                uusiLopetusIkkuna(new parkkihalliLopetusIkkuna);
        uusiLopetusIkkuna->peliVoitettu(tuhotutViholliset, pisteita,
                                        rahaa, teekkarikyborgejaElossa);
        tilasto_->paivitaPisteet(teekkarikyborgejaElossa*200,true);
        tilasto_->paivitaPisteet(tilasto_->annaPisteet(true),false);
        tilasto_->paivitaRahat(tilasto_->annaRaha(true),false);
        tilasto_->vihollinenTuhoutui(tilasto_->annaTuhotutViholliset(true),false);
        parkkihalliIkkuna_->avaaKikkuna();
    }
    else{
        std::shared_ptr<parkkihalliLopetusIkkuna>
                uusiLopetusIkkuna(new parkkihalliLopetusIkkuna);
        uusiLopetusIkkuna->peliVoitettu(0,0,0,0);
        parkkihalliIkkuna_->avaaKikkuna();
    }

}



void phalliLogiikka::phalliPeliAlkaa() {
    parkkihalliIkkuna_->showFullScreen();
}



void phalliLogiikka::vaihdaVuoroPelaajalle() {
    std::dynamic_pointer_cast<teekkariKyborgi> (phallinLaura_)->palautaToimintapisteet();
    std::vector<std::shared_ptr<toimijaRP>>::iterator iter;
    iter = kyborgit_.begin();
    while (iter != kyborgit_.end()) {
        std::dynamic_pointer_cast<teekkariKyborgi> (*iter)->palautaToimintapisteet();
        ++ iter;
    }
    aktiivinenToimija_ = nullptr;
    parkkihalliIkkuna_->asetaVuoroPelaajalle();
}


//------ Ampumisen seurauksena tapahtuvat funktiot -----//
// Näissä toimijat poistetaan phalliLogiikan privatemuuttujista.

void phalliLogiikka::sankariinOsui(std::shared_ptr<toimijaRP> toimija) {
    std::shared_ptr<teekkariKyborgi> sankari{std::dynamic_pointer_cast<teekkariKyborgi>(toimija)};
    std::map<std::pair<int,int>,std::shared_ptr<ruutu>>::iterator mapiter;
    mapiter = ruudukko_.begin();
    if (sankari->vahennaElamia() == false) {
        while (mapiter != ruudukko_.end()) {
            if(((*mapiter).second)->annaToimija() == toimija) {
                ((*mapiter).second)->poistaKomponentti();
            }
            ++mapiter;
        }
        if (sankari == phallinLaura_) {
            phallinLaura_ = nullptr;
            lopeta();
        } else if (kyborgit_.size() == 1) {
            parkkihalliIkkuna_->asetaKyborgi1ElamatNaytolle(0);
            parkkihalliIkkuna_->asetaKyborgi2ElamatNaytolle(0);
            kyborgit_.clear();
            parkkihalliIkkuna_->tuhoaKyborgi('3');
        } else if (kyborgit_.size() == 2) {
            if (sankari == kyborgit_.at(0)) {
                parkkihalliIkkuna_->asetaKyborgi1ElamatNaytolle(0);
                std::shared_ptr<toimijaRP> kyborgi2{kyborgit_.at(1)};
                kyborgit_.clear();
                kyborgit_.push_back(kyborgi2);
                parkkihalliIkkuna_->tuhoaKyborgi('1');
            } else {
                parkkihalliIkkuna_->asetaKyborgi2ElamatNaytolle(0);
                kyborgit_.pop_back();
                parkkihalliIkkuna_->tuhoaKyborgi('2');
            }
        }
    } else {
        if (sankari == phallinLaura_) {
            parkkihalliIkkuna_->asetaLauranElamatNaytolle(sankari->annaElamat());
        // Mennään tähän, jos Laura ei ole aktiivinen. Eli silloin tämä kyborgi on.
        } else if (kyborgit_.size() == 1){
            if (parkkihalliIkkuna_->onkoKyborgi1Kuollut()) {
                parkkihalliIkkuna_->asetaKyborgi2ElamatNaytolle(sankari->annaElamat());
            } else {
                parkkihalliIkkuna_->asetaKyborgi1ElamatNaytolle(sankari->annaElamat());
            }
        // Kyborgeja on kaksi
        } else {
           if (sankari == kyborgit_.at(0)) {
               parkkihalliIkkuna_->asetaKyborgi1ElamatNaytolle(sankari->annaElamat());
           } else {
               parkkihalliIkkuna_->asetaKyborgi2ElamatNaytolle(sankari->annaElamat());
           }
        }
    }
}

void phalliLogiikka::viholliseenOsui(std::shared_ptr<vihollinen> vihulainen) {
    int maara;
    if (aktiivinenAse_ == 0) {
        maara = 35;
    } else if (aktiivinenAse_ == 1) {
        maara = 50;
    } else {
        maara = 100;
    }

    std::vector<std::shared_ptr<vihollinen>>::iterator iter;
    std::vector<std::shared_ptr<vihollinen>> valiaikainenViholliset;
    iter = viholliset_.begin();
    while (iter != viholliset_.end()) {
        if (*iter == vihulainen) {
            if((*iter)->vahennaElamia(maara) != false) {
                valiaikainenViholliset.push_back(*iter);
            // Poistetaan toimija privatesta ja ruudukosta
            } else {
                std::map<std::pair<int,int>,std::shared_ptr<ruutu>>::iterator mapiter;
                mapiter = ruudukko_.begin();
                int pisteet{(*iter)->annaSaatavatPisteet()};
                tilasto_->paivitaPisteet(pisteet,true);
                int raha{(*iter)->annaSaatavaRaha()};
                tilasto_->paivitaRahat(raha,true);
                tilasto_->vihollinenTuhoutui(1,true);
                parkkihalliIkkuna_->asetaRahaJaPisteetNaytolle(raha,pisteet);
                while (mapiter != ruudukko_.end()) {
                    if(((*mapiter).second)->annaToimija() == vihulainen) {
                        ((*mapiter).second)->poistaKomponentti();
                    }
                    ++mapiter;
                }
            }
        } else {
            valiaikainenViholliset.push_back(*iter);
        }
        ++ iter;
    }
    viholliset_ = valiaikainenViholliset;
    if (viholliset_.size() == 0) {
        lopeta();
    }
}

//------

void phalliLogiikka::nappainPainettunaLiiku(std::string nappain) {
    if (aktiivinenToimija_ == phallinLaura_) {
        if (std::dynamic_pointer_cast<teekkariKyborgi>
                (phallinLaura_)->liiku(nappain) == false) {
            if (parkkihalliIkkuna_->lauraltaLoppuiToiminnot() == false) {
                // Vaihda vuoro vastustajalle.
                parkkihalliIkkuna_->vuoronVaihtoVastustajalle();
            }
        } else {
            int TP{std::dynamic_pointer_cast<teekkariKyborgi>
                        (phallinLaura_)->annaToimintapisteet()};
            parkkihalliIkkuna_->asetaToimintapisteetNaytolle(TP);
        }
    // Jos kyborgeja on yksi tai kaksi
    } else if (kyborgit_.size() > 0) {
        // Jos kyborgi1 on kuollut
        if(aktiivinenToimija_ == kyborgit_.at(0) and
                parkkihalliIkkuna_->onkoKyborgi1Kuollut()) {
            if (std::dynamic_pointer_cast<teekkariKyborgi>
                    (kyborgit_.at(0))->liiku(nappain) == false) {
                if (parkkihalliIkkuna_->kyborgi2LoppuiToiminnot() == false) {
                    // Vaihda vuoro vastustajalle.
                    parkkihalliIkkuna_->vuoronVaihtoVastustajalle();
                }
            } else {
                int TP{std::dynamic_pointer_cast<teekkariKyborgi>
                            (kyborgit_.at(0))->annaToimintapisteet()};
                parkkihalliIkkuna_->asetaToimintapisteetNaytolle(TP);
            }
        // Kyborgeja on yksi tai kaksi
        } else if (aktiivinenToimija_ == kyborgit_.at(0)) {
            if (std::dynamic_pointer_cast<teekkariKyborgi>
                    (kyborgit_.at(0))->liiku(nappain) == false) {
                if (parkkihalliIkkuna_->kyborgi1LoppuiToiminnot() == false) {
                    // Vaihda vuoro vastustajalle.
                    parkkihalliIkkuna_->vuoronVaihtoVastustajalle();
                }
            } else {
                int TP{std::dynamic_pointer_cast<teekkariKyborgi>
                            (kyborgit_.at(0))->annaToimintapisteet()};
                parkkihalliIkkuna_->asetaToimintapisteetNaytolle(TP);
            }
        }
    // Kyborgeja on kaksi
    }
    if(kyborgit_.size() == 2) {
        if (aktiivinenToimija_ == kyborgit_.at(1)) {
            if (std::dynamic_pointer_cast<teekkariKyborgi>
                    (kyborgit_.at(1))->liiku(nappain) == false) {
                if (parkkihalliIkkuna_->kyborgi2LoppuiToiminnot() == false) {
                    // Vaihda vuoro vastustajalle.
                    parkkihalliIkkuna_->vuoronVaihtoVastustajalle();
                }
            } else {
                int TP{std::dynamic_pointer_cast<teekkariKyborgi>
                            (kyborgit_.at(1))->annaToimintapisteet()};
                parkkihalliIkkuna_->asetaToimintapisteetNaytolle(TP);
            }
        }
    }
}

void phalliLogiikka::nappainPainettunaAmmu() {    
    if (aktiivinenToimija_ == phallinLaura_) {
        if (std::dynamic_pointer_cast<teekkariKyborgi> (phallinLaura_)->ammu() == false) {
            // Ampuminen ei onnistunut
            parkkihalliIkkuna_->lauraltaLoppuiToiminnot();
        } else {
            int TP{std::dynamic_pointer_cast<teekkariKyborgi>
                        (phallinLaura_)->annaToimintapisteet()};
            parkkihalliIkkuna_->asetaToimintapisteetNaytolle(TP);
            asetaAmmus();
        }

    } else if (kyborgit_.size() > 0) {
        if (aktiivinenToimija_ == kyborgit_.at(0) and
                parkkihalliIkkuna_->onkoKyborgi1Kuollut()) {
            if (std::dynamic_pointer_cast<teekkariKyborgi>
                    (kyborgit_.at(0))->ammu() == false) {
                parkkihalliIkkuna_->kyborgi2LoppuiToiminnot();
            } else {
                int TP{std::dynamic_pointer_cast<teekkariKyborgi>
                            (kyborgit_.at(0))->annaToimintapisteet()};
                parkkihalliIkkuna_->asetaToimintapisteetNaytolle(TP);
                asetaAmmus();
            }
        } else if (aktiivinenToimija_ == kyborgit_.at(0)) {
                if (std::dynamic_pointer_cast<teekkariKyborgi>
                        (kyborgit_.at(0))->ammu() == false) {
                    parkkihalliIkkuna_->kyborgi1LoppuiToiminnot();
                } else {
                    int TP{std::dynamic_pointer_cast<teekkariKyborgi>
                                (kyborgit_.at(0))->annaToimintapisteet()};
                    parkkihalliIkkuna_->asetaToimintapisteetNaytolle(TP);
                    asetaAmmus();
                }
        }
    }
    if(kyborgit_.size() == 2) {
        if(aktiivinenToimija_ == kyborgit_.at(1)) {
            if (std::dynamic_pointer_cast<teekkariKyborgi>
                    (kyborgit_.at(1))->ammu() == false) {
                parkkihalliIkkuna_->kyborgi2LoppuiToiminnot();
            } else {
                int TP{std::dynamic_pointer_cast<teekkariKyborgi>
                            (kyborgit_.at(1))->annaToimintapisteet()};
                parkkihalliIkkuna_->asetaToimintapisteetNaytolle(TP);
                asetaAmmus();
            }
        }
    }
}



void phalliLogiikka::lauranVuoro() {
    aktiivinenToimija_ = phallinLaura_;
}

void phalliLogiikka::kyborgi1Vuoro() {
    aktiivinenToimija_ = kyborgit_.at(0);
}

void phalliLogiikka::kyborgi2Vuoro() {
    if (kyborgit_.size() == 1) {
        aktiivinenToimija_ = kyborgit_.at(0);
    } else {
        aktiivinenToimija_ = kyborgit_.at(1);
    }

}


void phalliLogiikka::vaihdaVuoroVastustajalle() {
    std::vector<std::shared_ptr<vihollinen>>::iterator veciter{viholliset_.begin()};
    while (veciter != viholliset_.end()) {
        (*veciter)->palautaToimintapisteet();
        ++ veciter;
    }
    std::shared_ptr<tekoaly> uusiTekoaly{new tekoaly(shared_from_this())};
    uusiTekoaly->aloitaTekoaly(viholliset_,phallinLaura_,kyborgit_);
}
