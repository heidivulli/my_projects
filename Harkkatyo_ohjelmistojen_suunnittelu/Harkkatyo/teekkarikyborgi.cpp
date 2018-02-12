#include "phallinapufunktiot.h"
#include "teekkarikyborgi.h"


teekkariKyborgi::teekkariKyborgi(int elamat, std::map<std::pair<int, int>,
                                 std::shared_ptr<ruutu>> & ruudukko):
     suunta_{'a'}, ruudukko_{ruudukko}, toimintaPisteet_{3}, elamat_{elamat}
{
}

teekkariKyborgi::~teekkariKyborgi()
{

}

int teekkariKyborgi::annaElamat() {
    return elamat_;
}

char teekkariKyborgi::annaSuunta() {
    return suunta_;
}

int teekkariKyborgi::annaToimintapisteet() {
    return toimintaPisteet_;
}

void teekkariKyborgi::kaanny(char suunta) {
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

// Tässä katsotaan, onko uudessa ruudussa jo jokin muu toimija/este.
// Tarkistetaan myös, että ei mennä ruudukon yli. Maksimi sijainnit ovat
// x = 750, y = 525 (ruutukoolla 75x75). Jos ruutuun liikkuminen onnistuu, niin
// lisätään uuteen ruutuun toimija.
bool teekkariKyborgi::voikoLiikkua(sijainti sij) {
    if (sij.annaX() > 750 or sij.annaX() < 0 or
            sij.annaY() > 525 or sij.annaY() < 0) {
        return false;
    }
    std::shared_ptr<ruutu> tutkittavaRuutu{laskeSijainninRuutu(sij,ruudukko_)};
    if (tutkittavaRuutu->annaToimija() == nullptr and
            tutkittavaRuutu->annaEste() == nullptr) {
        tutkittavaRuutu->asetaToimija(shared_from_this());
        return true;
    }
    return false;
}

// Jos voikoLiikkua palauttaa true, poistetaan toimija vanhasta ruudusta.
bool teekkariKyborgi::liikuVasemmalle(int matka) {
    sijainti sij = annaSijainti();

    int x = sij.annaX();
    int y = sij.annaY();

    x -= matka;

    sijainti uusiSijainti;
    uusiSijainti.asetaXY(x, y);

    if (voikoLiikkua(uusiSijainti)) {
        std::shared_ptr<ruutu> vanhaRuutu{laskeSijainninRuutu(sij,ruudukko_)};
        vanhaRuutu->poistaKomponentti();
        setPos(x, y);
        asetaSijainti(uusiSijainti);
        return true;
    }
    return false;
}

bool teekkariKyborgi::liikuOikealle(int matka) {
    sijainti sij = annaSijainti();

    int x = sij.annaX();
    int y = sij.annaY();

    x += matka;

    sijainti uusiSijainti;
    uusiSijainti.asetaXY(x, y);

    if (voikoLiikkua(uusiSijainti)) {
        std::shared_ptr<ruutu> vanhaRuutu{laskeSijainninRuutu(sij,ruudukko_)};
        vanhaRuutu->poistaKomponentti();
        setPos(x, y);
        asetaSijainti(uusiSijainti);
        return true;
    }
    return false;

}

bool teekkariKyborgi::liikuAlas(int matka) {
    sijainti sij = annaSijainti();

    int x = sij.annaX();
    int y = sij.annaY();

    y += matka;

    sijainti uusiSijainti;
    uusiSijainti.asetaXY(x, y);

    if (voikoLiikkua(uusiSijainti)) {
        std::shared_ptr<ruutu> vanhaRuutu{laskeSijainninRuutu(sij,ruudukko_)};
        vanhaRuutu->poistaKomponentti();
        setPos(x, y);
        asetaSijainti(uusiSijainti);
        return true;
    }
    return false;

}

bool teekkariKyborgi::liikuYlos(int matka) {
    sijainti sij = annaSijainti();

    int x = sij.annaX();
    int y = sij.annaY();

    y -= matka;

    sijainti uusiSijainti;
    uusiSijainti.asetaXY(x, y);

    if (voikoLiikkua(uusiSijainti)) {
        std::shared_ptr<ruutu> vanhaRuutu{laskeSijainninRuutu(sij,ruudukko_)};
        vanhaRuutu->poistaKomponentti();
        setPos(x, y);
        asetaSijainti(uusiSijainti);
        return true;
    }
    return false;

}


// Palauttaa falsen, jos hahmolla ei ole toimintaPisteitä jäljellä.
bool teekkariKyborgi::liiku(std::string nappain) {
    this->setFocus();
    int matka = 75;
    if (toimintaPisteet_ != 0) {
        //vasenta nuolinappia painetaan
        if (nappain == "vasen") {
            if (suunta_ == 'v'){
                    if (liikuVasemmalle(matka) == false) {
                        // Tulisiko käyttäjälle ilmoitus, että ei onnistunut?
                    } else {
                        toimintaPisteet_ -= 1;

                    }
            }
            else {
                kaanny('v');
            }
        }
        else if (nappain == "ylos") {
            if (suunta_ == 'y') {
                if (liikuYlos(matka) == false) {
                    // Tulisiko käyttäjälle ilmoitus, että ei onnistunut?
                } else {
                    toimintaPisteet_ -= 1;
                }
            }
            else {
                kaanny('y');
            }
        }
        else if (nappain == "oikea") {
            if (suunta_ == 'o') {
                    if (liikuOikealle(matka) == false) {
                        // Tulisiko käyttäjälle ilmoitus, että ei onnistunut?
                    } else {
                        toimintaPisteet_ -= 1;
                    }
            }
            else {
                kaanny('o');
            }
        }
        else if (nappain == "alas") {
            if (suunta_ == 'a') {
                if (liikuAlas(matka) == false) {
                    // Tulisiko käyttäjälle ilmoitus, että ei onnistunut?
                } else {
                    toimintaPisteet_ -= 1;
                }
            }
            else {
                kaanny('a');
            }
        }
    }
    if (toimintaPisteet_ == 0){
        // "Hahmolla ei ole toimintapisteitä jäljellä tälle kierrokselle."
        kaanny('a');
        return false;
    }

    return true;
}

bool teekkariKyborgi::ammu() {
    if (toimintaPisteet_ != 0) {
        toimintaPisteet_ -= 1;
    } else if (toimintaPisteet_ == 0) {
        // Hahmolla ei ole toimintapisteitä
        return false;
    }
    return true;

}

// Vähennetään elämiä yhden osuman verran
bool teekkariKyborgi::vahennaElamia() {
    elamat_ -= 25;
    if (elamat_ <= 0) {
        elamat_ = 0;
        return false;
    }
    return true;
}

void teekkariKyborgi::palautaToimintapisteet() {
    toimintaPisteet_ = 3;
}




