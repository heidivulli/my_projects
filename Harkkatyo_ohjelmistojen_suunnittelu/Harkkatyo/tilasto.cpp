#include "tilasto.h"


tilasto::tilasto():
    parkkihalleja_{0},
    pisteet_{0},
    raha_{0},
    tuhotutParkkihallit_{0},
    tuhotutViholliset_{0},
    vaRaha_{0},
    vaPisteet_{0},
    vaTuhotutViholliset_{0}
{
}

tilasto::~tilasto()
{

}

unsigned int tilasto::annaParkkihallit() const {
    return parkkihalleja_;

}

int tilasto::annaPisteet(bool onkoVA) const {
    if (onkoVA) {
        return vaPisteet_;
    } else {
        return pisteet_;
    }
}

int tilasto::annaRaha(bool onkoVA) const {
    if (onkoVA) {
        return vaRaha_;
    } else {
        return raha_;
    }
}

unsigned int tilasto::annaTuhotutParkkihallit() const {
    return tuhotutParkkihallit_;

}

int tilasto::annaTuhotutViholliset(bool onkoVA) const {
    if (onkoVA) {
        return vaTuhotutViholliset_;
    } else {
        return tuhotutViholliset_;
    }
}

void tilasto::nollaaValiaikaiset() {
    vaRaha_ = 0;
    vaPisteet_ = 0;
    vaTuhotutViholliset_ = 0;
}

void tilasto::parkkihalliTuhoutui() {
    ++tuhotutParkkihallit_;

}

void tilasto::vihollinenTuhoutui(int maara, bool onkoVA) {
    if (onkoVA) {
        vaTuhotutViholliset_ += maara;
    } else {
        tuhotutViholliset_ += maara;
    }
}

void tilasto::asetaParkkihallienMaara(int parkkihallienMaara) {
   parkkihalleja_ = parkkihallienMaara;


}

void tilasto::paivitaPisteet(int pisteet, bool onkoVA) {
    if (onkoVA) {
        vaPisteet_ += pisteet;
    } else {
        pisteet_ += pisteet;
    }
}

void tilasto::paivitaRahat(int rahat, bool onkoVA) {
    if (onkoVA) {
        vaRaha_ += rahat;
    } else {
        raha_ += rahat;
    }
}

