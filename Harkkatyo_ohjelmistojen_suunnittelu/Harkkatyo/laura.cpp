#include "laura.h"

laura::laura(): suunta_{'a'}, kilpi_{false}, ase_{0}
{
}

laura::~laura()
{

}

void laura::asetaKaupunki(std::shared_ptr<kaupunki> lauranKaupunki)
{
    kaupunki_ = lauranKaupunki;
}

void laura::kaanny(char suunta)
{
    if (suunta == suunta_) {
        return;
    }
    if (suunta == 'a') {
        setRotation(0);
    }
    else if (suunta == 'v') {
        setRotation(90);
    }
    else if (suunta == 'y') {
        setRotation(180);
    }
    else {
        setRotation(-90);
    }

    suunta_ = suunta;
}

char laura::annaSuunta()
{
    return suunta_;
}

void laura::liikuVasemmalle(int matka)
{
    sijainti nykyinenSijainta = annaSijainti();

    int x = nykyinenSijainta.annaX();
    int y = nykyinenSijainta.annaY();

    if ((x - matka) <= 0) {
        x = 0;
    }
    else {
        x -= matka;
    }

    setPos(x, y);

    sijainti uusiSijainti;
    uusiSijainti.asetaXY(x, y);
    asetaSijainti(uusiSijainti);
}

void laura::liikuOikealle(int matka)
{
    sijainti nykyinenSijainta = annaSijainti();

    int x = nykyinenSijainta.annaX();
    int y = nykyinenSijainta.annaY();

    if ((x + matka) >= 735) {
        x = 735;
    }
    else {
        x += matka;
    }

    setPos(x, y);

    sijainti uusiSijainti;
    uusiSijainti.asetaXY(x, y);
    asetaSijainti(uusiSijainti);

}

void laura::liikuAlas(int matka)
{
    sijainti nykyinenSijainta = annaSijainti();

    int x = nykyinenSijainta.annaX();
    int y = nykyinenSijainta.annaY();

    if ((y + matka) >= 649) {
        y = 649;
    }
    else {
        y += matka;
    }

    setPos(x, y);

    sijainti uusiSijainti;
    uusiSijainti.asetaXY(x, y);
    asetaSijainti(uusiSijainti);

}

void laura::liikuYlos(int matka)
{
    sijainti nykyinenSijainta = annaSijainti();

    int x = nykyinenSijainta.annaX();
    int y = nykyinenSijainta.annaY();

    if ((y - matka) <= 0) {
        y = 0;
    }
    else {
        y -= matka;
    }

    setPos(x, y);

    sijainti uusiSijainti;
    uusiSijainti.asetaXY(x, y);
    asetaSijainti(uusiSijainti);

}

bool laura::onkoKilpi()
{
    return kilpi_;
}

void laura::kilpiOstettu()
{
    kilpi_ = true;
}

void laura::nollaaKilpi()
{
    kilpi_ = false;
}


int laura::annaAse()
{
    return ase_;
}

void laura::uusiAse(int ase)
{
    ase_ = ase;
}

void laura::keyPressEvent(QKeyEvent *event)
{
    //matka, jonka laura liikkuu
    int matka = 10;

    //vasen-nuolinappia painetaan
    if (event->key() == Qt::Key_Left) {
        //lauran suunta on vasemmalle, liikutaan
        if (suunta_ == 'v'){
            liikuVasemmalle(matka);
        }
        //lauran suunta ei ole vasemmalle, käännytään
        else {
            kaanny('v');
            return;
        }
    }
    //ylös-nuolinappia painetaan
    else if (event->key() == Qt::Key_Up) {
        //lauran suunta on ylös, liikutaan
        if (suunta_ == 'y') {
            liikuYlos(matka);
        }
        //lauran suunta ei ole ylös, käännytään
        else {
            kaanny('y');
            return;
        }
    }
    //oikea-nuolinappia painetaan
    else if (event->key() == Qt::Key_Right) {
        //lauran suunta on oikealle, liikutaan
        if (suunta_ == 'o') {
            liikuOikealle(matka);
        }
        //lauran suunta ei ole oikealle, käännytään
        else {
            kaanny('o');
            return;
        }
    }
    //alas-nuolinappia painetaan
    else if (event->key() == Qt::Key_Down) {
        //lauran suunta on alas, liikutaan
        if (suunta_ == 'a') {
            liikuAlas(matka);
        }
        //lauran suunta ei ole alas, käännytään
        else {
            kaanny('a');
            return;
        }
    }
    //jotain muuta näppäimistön nappia painettu
    else {
        return;
    }

    //tarkistetaan, ollaanko lähellä parkkihallia tai kauppaa
    kaupunki_->onkoParkkihalliLahella(annaSijainti());
    kaupunki_->onkoKauppaLahella(annaSijainti());
}

