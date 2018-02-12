
#include "xmlparkkihallireader.h"

#include <QDebug>
#include <iostream>
#include <QEventLoop>
#include <QNetworkRequest>

#include <string>


xmlParkkihalliReader::xmlParkkihalliReader(std::shared_ptr<std::vector<std::shared_ptr<parkkihalli>>> phalliVektori):
    phalliVektori_(phalliVektori)
{
}


xmlParkkihalliReader::~xmlParkkihalliReader()
{

}

bool xmlParkkihalliReader::read(QIODevice *device){
    reader_.setDevice(device);

    //tänne mennään jos luetaan tiedosto ensimmäistä kertaa
    //tällöin tarvitsee tallentaa myös staattiset tiedot.
    if(phalliVektori_->size() == 0){

        //Hypätään turhien rivien yli
        while(reader_.name() != "parkingFacility"){

            reader_.readNext();
            if(reader_.atEnd()){
                return false;
            }
        }

        if(reader_.name() == "parkingFacility"){
             return lueParkkihalliStatic();

        }
        else{
            //vääränlainen tiedosto
            return false;
        }

    }
    else{

        while(reader_.name() != "parkingFacilityStatus") {
            reader_.readNext();
            if(reader_.atEnd()){
                return false;
            }
        }

        return lueParkkihalliStatus();

    }

}


bool xmlParkkihalliReader::lueParkkihalliStatic()
{
    //muodostetaan osoitin parkkihalliosottimeen
    std::shared_ptr<parkkihalli> phalli {new parkkihalli};
    QStringRef nimi;

    //otetaan ID talteen
    phalli ->asetaID(reader_.attributes().value("id").toString());

    reader_.readNext();

    QString latitude = "";
    QString longitude = "";
    QString layout;
    //luetaan while-loopin avulla kaikki teidot
    while(reader_.name() != "parkingFacility"){

        if(reader_.isStartElement()){
            if(reader_.name() == "parkingFacilityName"){
                 phalli->asetaNimi(reader_.readElementText());

            }

            else if (reader_.name() == "totalParkingCapacity"){
                phalli->asetaMaksimiKoko(reader_.readElementText());

            }
            else if (reader_.name() == "latitude"){
                latitude = reader_.readElementText();


            }
            else if(reader_.name() == "parkingFacilityLayout"){
                layout = reader_.readElementText();
            }
            else if(reader_.name() == "longitude"){
                longitude = reader_.readElementText();


            }
            //jos on luettu dokumentin loppuun, palautetaan false.
            else if(reader_.atEnd()){
                return false;
            }

        }
        reader_.readNext();
    }

    //ollaan päästy yhden parkkihallin tietojen loppuun
    if(latitude != "" && longitude != ""){
        phalli->asetaSijainti(latitude, longitude);
    }
    else{
        qDebug()<<"Virhe! Parkkihalline sijainti luettu väärin";
        return false;
    }

    reader_.readNextStartElement();

    //jos on tiedostossa on seuraavaksi parkinFacility, ajetaan uudestaan
    //lueParkkihalliStatic funktio.
    if(reader_.name() == "parkingFacility"){

        //lisätään parkkihalli vektoriin vain jos ei ole
        //streetParking tai outDoorArea luokkaa ja
        //latitude ja longitude ovat kartan sisällä
        if(phalli->asetaSijainti(latitude, longitude) &&
                layout != "streetParking"&& layout != "openOutdoorArea"){
            phalliVektori_->push_back(phalli);
        }

        return lueParkkihalliStatic();
    }
    //jos ollaan saavutettu staattisten tiedostojen loppu, siirrytään
    //lukemaan status-tietoja lueParkkihalliStatus-funktioon.
    else{
        while(reader_.name() != "parkingFacilityStatus"){
            nimi = reader_.name();
            reader_.readNext();
            if(reader_.atEnd()){
                return false;
            }
        }
        return lueParkkihalliStatus();

    }
}



bool xmlParkkihalliReader::lueParkkihalliStatus()
{
    QStringRef nimi = reader_.name();
    std::shared_ptr<parkkihalli> phalli{nullptr};

    while(true){
        reader_.readNext();
        nimi = reader_.name();

        //tarkistetaanko onko viimeinen parkinFacilityStatus
        //vaiko vain keskellä oleva
        if(nimi == "parkingFacilityStatus"){
            reader_.readNext();
            reader_.readNext();
            if(reader_.isStartElement()){
                break;
            }
            //ollaan saavutettu loppu
            else if(reader_.name() ==
                    "parkingFacilityTableStatusPublication"){
                break;
            }

        }
        if(nimi =="parkingFacilityReference" && reader_.isStartElement()){
            QString id = reader_.attributes().value("id").toString();

            //etsitään id:tä vastaava parkkihalli phalliVektorista
            for(unsigned int indeksi = 0; indeksi < phalliVektori_->size();++indeksi ){
                QString id2 = phalliVektori_->at(indeksi)->annaID();
                //jos luettu id on sama kuin vektoriin tallennetun parkkihalllin id

                if(id2 == id){
                    phalli = phalliVektori_->at(indeksi);
                    break;
                }
            }
            //Jos phalli on nullptr, ei tarkasteltavaa parkkihallia ole vektorissa
            if(phalli == nullptr){
                break;
            }
        }
        else if(nimi == "totalNumberOfOccupiedParkingSpaces" && phalli != nullptr){
            phalli->asetaVaratutPaikkojenMaara(reader_.readElementText());
            //Parkkihalliin on nyt tallnnettu varattujen paikkojen määärä
            //voidaan määrittää parkkihallin vaikeus.
            phalli->asetaVaikeus();

        }
        else if(reader_.atEnd()){
            return false;
        }

    }
    //ollaan saavutettu tiedoston loppu
    if(reader_.name() == "parkingFacilityTableStatusPublication"){
        return true;

    }
    //jos tieodost on muuttunut, lopettaa kuitenkin loopin
    else if(reader_.atEnd()){
        return true;
    }
    //tieodosto ei ole vielä loppunut, joten luetaan status tiedot
    //seuraavalle.
    else{
        return lueParkkihalliStatus();

    }

}


