#include "ammus.h"
#include "phallilogiikka.h"
#include "phallinapufunktiot.h"
#include "teekkarikyborgi.h"

#include <typeinfo>
#include <vector>
#include <QGraphicsScene>
#include <QTimer>
#include <QDebug>

ammus::ammus(std::shared_ptr<phalliLogiikka> pLogiikka, std::shared_ptr<toimijaRP> ampuja):
    ampuja_{ampuja}, pLogiikka_{pLogiikka}, suunta_{'y'}
{

    //Tehdään timer, joka liikuttaa ammusta
    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()),this, SLOT(liiku()));
    //timeri käy viiden millisekuntin välein
    timer->start(5);


}

ammus::~ammus()
{

}

void ammus::kaanny(char suunta) {
    if (suunta == suunta_) {
        return;
    }
    if (suunta == 'a') {
        setRotation(180);
    }
    else if (suunta == 'v') {
        setRotation(-90);
    }
    else if (suunta == 'y') {
        setRotation(0);
    }
    else {
        setRotation(90);
    }

    suunta_ = suunta;
}

//asettaa alkusijainnin ammukselle.
void ammus::asetaSijainti(int x, int y) {
    sij_.asetaXY(x,y);


}




void ammus::liiku() {
    //tarkistetaan onko ammuksen lähellä toimijjoita. Jos on, tuhotaan toimijat ja ammus
    sijainti vertailukelpoinen;
    vertailukelpoinen.asetaXY(sij_.annaX()-38,sij_.annaY());

    std::map<std::pair<int,int>,std::shared_ptr<ruutu>> ruudukko{pLogiikka_->annaRuudukko()};

    std::shared_ptr<ruutu> tarkasteltava{laskeSijainninRuutu(vertailukelpoinen,ruudukko)};
    // Ammutaan estettä päin
    if (tarkasteltava->annaEste() != nullptr) {
        delete this;
        return;
    // Jos ruudussa on toimija ja jos toimija ei ole itse ampuja.
    } else if (tarkasteltava->annaToimija() != nullptr and
               tarkasteltava->annaToimija() != ampuja_) {
        std::shared_ptr<teekkariKyborgi> sankari{std::dynamic_pointer_cast
                    <teekkariKyborgi>(tarkasteltava->annaToimija())};
        if (sankari) {
            pLogiikka_->sankariinOsui(tarkasteltava->annaToimija());
            delete this;
            return;
        } else {
            pLogiikka_->viholliseenOsui(std::dynamic_pointer_cast<vihollinen>
                                        (tarkasteltava->annaToimija()));
            delete this;
            return;
        }
    }

    int x{sij_.annaX()};
    int y{sij_.annaY()};
    //Riippuen ammuksen lähtöasennosta, liikutetaan ammusta eteenpäin.
    //ammuksen nopeus on 3.
    if(suunta_ == 'o'){
        x += 3;
        setPos(x, y);
        if (x > 750){
            delete this;
        }
    } else if(suunta_ == 'v'){
        x -= 3;
        setPos(x, y);
        if (x < 0){
            delete this;
        }
    } else if(suunta_ == 'y'){
        y -= 3;
        setPos(x, y);
        if (y < 0){
            delete this;
        }
    } else if(suunta_ == 'a'){
        y += 3;
        setPos(x, y);
        if (y > 525){
            delete this;
        }
    }
    //asetetaa uusi sijainti ammukselle
    sij_.asetaXY(x, y);
}


