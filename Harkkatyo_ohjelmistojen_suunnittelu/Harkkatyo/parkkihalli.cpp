#include "parkkihalli.h"

#include <QDebug>
#include <cmath>


parkkihalli::parkkihalli():
koko_{-1},onkoTuhottu_{false},varattujenPaikkojenMaara_ {-1}
{
}

parkkihalli::~parkkihalli()
{

}

QString parkkihalli::annaID() const
{
    return id_;

}

QString parkkihalli::annaVaikeus() const
{
    return vaikeusAste_;

}

sijainti parkkihalli::annaSijainti() const
{
    return sijainti_;

}

QString parkkihalli::annaKokoString() const
{
    return kokoString_;

}

bool parkkihalli::onkoTuhottu() const
{
    return onkoTuhottu_;

}


void parkkihalli::asetaID(QString id)
{
    id_ = id;
    
}


//voi olla turha
void parkkihalli::asetaNimi(QString nimi)
{
    nimi_ = nimi;
}

bool parkkihalli::asetaSijainti(QString latitude,
                                QString longitude)
{
    double nollaKulmaLatitude{61.506052};
    double nollaKulmaLongitude{23.750419};
    double lat = latitude.toDouble();
    double lot = longitude.toDouble();

    if(lat <= nollaKulmaLatitude && lat >= 61.491451 &&
            lot >= nollaKulmaLongitude && lot <= 23.786481){

        //Muutetaan longitude/latitude asteet kartan pikseligrafiikaksi.
        double kuvanPituusAsteina{0.014601};
        double kuvanLeveysAsteina{0.035062};
        double kuvanLeveysPikseleina{819};
        double kuvanPituusPikseleina{716};


        double xSijainti = std::abs(nollaKulmaLongitude-lot)*
                (kuvanLeveysPikseleina/kuvanLeveysAsteina);
        double ySijainti = std::abs(nollaKulmaLatitude-lat)*
                (kuvanPituusPikseleina/kuvanPituusAsteina);
        int x = (double)(xSijainti);
        int y = (double)(ySijainti);
        sijainti_.asetaXY(x,y);
        return true;

    }
    else{
        return false;
    }

    
}

void parkkihalli::asetaMaksimiKoko(QString koko)
{
    koko_ = koko.toDouble();
    if(koko_<= 300){
        kokoString_ = "Pieni";
    }
    else if(koko_ <500){
        kokoString_ = "Keskisuuri";
    }
    else{
        kokoString_ = "Iso";
    }
    
}

void parkkihalli::asetaVaratutPaikkojenMaara(QString varatutPaikat)
{
    varattujenPaikkojenMaara_ = varatutPaikat.toDouble();
}

void parkkihalli::tuhoa()
{
    onkoTuhottu_ = true;
}

void parkkihalli::asetaVaikeus()
{
    if(varattujenPaikkojenMaara_ <0 || koko_ <0){
        qDebug()<<"Virhe! Parkkihallin vaikeuden asettaminen epäonnistui";
    }
    //vaikeusaste määräytyy varattujenPaikkojenMaaran ja koon mukaan.
    double vaikeusaste = varattujenPaikkojenMaara_/koko_;

    if(vaikeusaste < 0.2){
        vaikeusAste_ = "Helppo";
    }
    else if(vaikeusaste < 0.5){
        vaikeusAste_ = "Kohtalainen";
    }
    else{
        vaikeusAste_ = "Vaikea";
    }
}




