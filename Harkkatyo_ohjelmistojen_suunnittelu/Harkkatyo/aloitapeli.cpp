#include "aloitapeli.h"
#include "lataatiedosto.h"
#include "kauppa.h"
#include "kaupunki.h"
#include "kaupunkiikkuna.h"
#include "laura.h"
#include "parkkihalliikkuna.h"

#include <iostream>
#include <memory>
#include <QDebug>
#include <QFile>

void aloitapeli() {
    //tehdään uusi kaupunkiIkkuna
    std::shared_ptr<kaupunkiIkkuna> kIkkuna{new kaupunkiIkkuna};

    //tehdään uusi kaupunki, jolle annetaan kaupunkiIkkuna
    std::shared_ptr<kaupunki> uusiKaupunki{new kaupunki(kIkkuna)};

    //pistetään QImage taustakuvaksi
    QImage pkartta(":/new/prefix1/Kuvat/karttakuva.png");
    pkartta.setOffset(QPoint(0,0));

    uusiKaupunki->asetaTausta(pkartta);

    //ensimmäinen tiedosto on vain parkkihallin esimerkkitieodosto. Jos tämä laitetaan
    //haeParkkihallit parametriksi, ei käytetä API-rajapintaa
   // QString tiedosto(":/new/prefix1/parkkihalliData.xml");
    QString tiedosto2("");

    if(!uusiKaupunki->haeParkkihallit(tiedosto2)){
        //parkkihallien hakeminen epäonnistui ja peli loppuu
        return;
    }
    uusiKaupunki->asetaParkkihalli();

    //asetetaan kaupan sijainti kartalle
    uusiKaupunki->asetaKaupanSijainti();

    //luodaan tilasto
    std::shared_ptr<tilasto> uusiTilasto(new tilasto);
    uusiKaupunki->asetaTilasto(uusiTilasto);

    //tehdään uusi Laura
    std::shared_ptr<toimijaRP> uusiLaura(new laura);

    //annetaan lauralle kaupunki
    std::dynamic_pointer_cast<laura>(uusiLaura)->asetaKaupunki(uusiKaupunki);

    //annetaan Laura kaupungille
    uusiKaupunki->asetaLaura(uusiLaura);

    uusiKaupunki->peliAlkaa();


}
