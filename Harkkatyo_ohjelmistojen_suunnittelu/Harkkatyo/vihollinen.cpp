#include "phallinapufunktiot.h"
#include "vihollinen.h"


vihollinen::vihollinen(std::map<std::pair<int, int>,
                       std::shared_ptr<ruutu> > &ruudukko, int elamat, int pisteet, int raha):
    elamat_{elamat},
    ruudukko_{ruudukko},
    saatavaRaha_{raha},
    saatavatPisteet_{pisteet},
    suunta_{'a'},
    toimintaPisteet_{3}
{    
}

vihollinen::~vihollinen() {
}

int vihollinen::annaSaatavaRaha() {
    return saatavaRaha_;
}

int vihollinen::annaSaatavatPisteet() {
    return saatavatPisteet_;
}

char vihollinen::annaSuunta(){
    return suunta_;
}

bool vihollinen::onkoToimintapisteita() {
    if (toimintaPisteet_ == 0) {
        return false;
    }
    return true;
}

void vihollinen::palautaToimintapisteet() {
    toimintaPisteet_ = 3;
}


//------ Ampumiseen liittyvät funktiot ------//

// Palauttaa true, jos ampuminen onnistuu. Muuten palauttaa falsen.
bool vihollinen::voikoAmpua(std::shared_ptr<ruutu> tarkisteltava, char ampumisSuunta) {
    if (tarkisteltava->annaEste() != nullptr) {
        // Ei voi ampua, tiellä on este
        return false;
    } else if (tarkisteltava->annaToimija() != nullptr) {
        if (std::dynamic_pointer_cast<vihollinen> (tarkisteltava->annaToimija())) {
            // Ei voi ampua, koska tiellä on vihollinen
            return false;
        } else {
            // Ammu ja palauta true
            kaanny(ampumisSuunta);
            toimintaPisteet_ -= 1;
            return true;
        }
    }

    return false;
}


//------ Likkumiseen liittyvät funktiot ------//


void vihollinen::kaanny(char suunta) {
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
bool vihollinen::voikoLiikkua(sijainti sij) {
    if (sij.annaX() > 825 or sij.annaX() < 0 or
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
bool vihollinen::liikuVasemmalle(int matka) {
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

bool vihollinen::liikuOikealle(int matka) {
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

bool vihollinen::liikuAlas(int matka) {
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

bool vihollinen::liikuYlos(int matka) {
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

// Palauttaa true, jos liikkuminen onnistuu
bool vihollinen::liiku(char liikkumisSuunta) {
    this->setFocus();
    int matka = 75;
    if (toimintaPisteet_ != 0) {
        //vasenta nuolinappia painetaan
        if (liikkumisSuunta == 'V') {
            if (suunta_ != 'v'){
                kaanny('v');
            }
            if (liikuVasemmalle(matka) == false) {
                return false;
            }
        } else if (liikkumisSuunta == 'Y') {
            if (suunta_ != 'y') {
                kaanny('y');
            }
            if (liikuYlos(matka) == false) {
                return false;
            }
        } else if (liikkumisSuunta == 'O') {
            if (suunta_ != 'o') {
                kaanny('o');
            }
            if (liikuOikealle(matka) == false) {
                return false;
            }
        } else if (liikkumisSuunta == 'A') {
            if (suunta_ != 'a') {
                kaanny('a');
            }
            if (liikuAlas(matka) == false) {
                return false;
            }
        }
    } else {
        return false;
    }

    toimintaPisteet_ -= 1;
    return true;
}

bool vihollinen::vahennaElamia(int maara) {
    elamat_ -= maara;
    if (elamat_ <= 0) {
        std::shared_ptr<ruutu> vihollisenRuutu{
            laskeSijainninRuutu(this->annaSijainti(),ruudukko_)};
        vihollisenRuutu->poistaKomponentti();
        return false;
    }
    return true;

}

