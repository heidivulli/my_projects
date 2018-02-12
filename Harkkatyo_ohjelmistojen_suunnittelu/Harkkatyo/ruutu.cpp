#include "ruutu.h"

ruutu::ruutu():
    este_{nullptr}
{
}

ruutu::~ruutu()
{

}


// Palauttaa nullptr, jos ruudussa ei ole toimijaa.
std::shared_ptr<toimijaRP> ruutu::annaToimija() const {
    return toimija_;
}

// Palauttaa nullptr, jos ruudussa ei ole estettä.
std::shared_ptr<este> ruutu::annaEste() const {
    return este_;
}

std::shared_ptr<sijainti> ruutu::annaSijainti() const{
    return sijainti_;
}

int ruutu::annaVaakaNumero() const {
    return vaakaNumero_;
}

int ruutu::annaPystyNumero() const {
    return pystyNumero_;
}


// Ennen tänne tulemista on suoritettu funktio onkoRuudussa() ja tarkistettu,
// että ruutu on tyhjä.
void ruutu::asetaEste(std::shared_ptr<este> este) {
    este_ = este;

}

void ruutu::asetaSijainti(std::shared_ptr<sijainti> sij, int pysty, int vaaka) {
    sijainti_ = sij;
    vaakaNumero_ = vaaka;
    pystyNumero_ = pysty;
}

// Ennen tänne tulemista on suoritettu funktio onkoRuudussa() ja tarkistettu,
// että ruutu on tyhjä.
void ruutu::asetaToimija(std::shared_ptr<toimijaRP> toimija) {
    toimija_ = toimija;
}

void ruutu::poistaKomponentti() {
    if (toimija_ != nullptr) {
        toimija_.reset();
    } else if (este_ != nullptr){
        este_.reset();
    }
}

bool ruutu::onkoRuudussa() const {
    if (toimija_ != nullptr or este_ != nullptr) {
        return true;
    } else {
        return false;
    }
}





