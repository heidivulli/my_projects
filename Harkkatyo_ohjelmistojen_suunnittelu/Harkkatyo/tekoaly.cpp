#include "tekoaly.h"
#include "phallinapufunktiot.h"

#include <cmath>


namespace {

double annaEtaisyys(sijainti sankarinSij, sijainti vihollisenSij) {
    int vx {vihollisenSij.annaX()};
    int vy {vihollisenSij.annaY()};
    int sx {sankarinSij.annaX()};
    int sy {sankarinSij.annaY()};

    return std::sqrt((vx-sx)*(vx-sx) + (vy-sy)*(vy-sy));
}

// Laskee vihollisen ja toimijan välisen etäisyyden
std::shared_ptr<toimijaRP> laskeKohde(std::shared_ptr<toimijaRP> vihollinen,
                                      std::shared_ptr<toimijaRP> &laura,
                                      std::vector<std::shared_ptr<toimijaRP>>
                                      &kyborgit) {

    sijainti lauranSij{laura->annaSijainti()};
    sijainti vihollisenSij{vihollinen->annaSijainti()};
    double etaisyysL{annaEtaisyys(lauranSij, vihollisenSij)};

    if (kyborgit.size() == 0) {
        return laura;

    } else if (kyborgit.size() >= 1) {
        sijainti kyborgi1Sij{kyborgit.at(0)->annaSijainti()};
        double etaisyysK1{annaEtaisyys(kyborgi1Sij, vihollisenSij)};

        if (etaisyysK1 < etaisyysL) {
            return kyborgit.at(0);
        } else {
            return laura;
        }
    } else {
        sijainti kyborgi1Sij{kyborgit.at(0)->annaSijainti()};
        double etaisyysK1{annaEtaisyys(kyborgi1Sij, vihollisenSij)};

        sijainti kyborgi2Sij{kyborgit.at(1)->annaSijainti()};
        double etaisyysK2{annaEtaisyys(kyborgi2Sij, vihollisenSij)};

        // Etäisyys Lauraan on pienin
        if (etaisyysL < etaisyysK1 and etaisyysL < etaisyysK2) {
            return laura;
        // Etäisyys kyborgi1 on pienin
        } else if (etaisyysK1 < etaisyysL and etaisyysK1 < etaisyysK2) {
            return kyborgit.at(0);
        // Etäisyys kyborgi2 on pienin
        } else if (etaisyysK2 < etaisyysL and etaisyysK2 < etaisyysK1) {
            return kyborgit.at(1);
        // Kaksi yhtä suurta etäisyyttä. Hyökätään ensin Lauraa kohti.
        } else if (etaisyysL == etaisyysK1 or etaisyysL == etaisyysK2) {
            return laura;
        // Kyborhien etäisyydet yhtä suuret. Hyökätään kyborgi1 kohti.
        } else {
            return kyborgit.at(0);
        }
    }

}


}




tekoaly::tekoaly(std::shared_ptr<phalliLogiikka> pLogiikka):
    parkkihalliLogiikka_{pLogiikka}
{

}

tekoaly::~tekoaly() {
}



// Palauttaa falsen, jos ei pystytä liikkumaan.
bool tekoaly::liiku() {
    sijainti kohteenSij{kohde_->annaSijainti()};
    std::shared_ptr<ruutu> kohteenRuutu{laskeSijainninRuutu
                (kohteenSij,ruudukko_)};
    sijainti vihollisenSij{aktiivinenVihollinen_->annaSijainti()};
    std::shared_ptr<ruutu> vihollisenRuutu{laskeSijainninRuutu
                (vihollisenSij,ruudukko_)};

    // Ei pitäisi mennä negatiiviseksi, koska -1 on absin ulkopuolella
    int pystyRuutujaValissa{abs(kohteenRuutu->annaPystyNumero() -
                vihollisenRuutu->annaPystyNumero()) -1};
    int vaakaRuutujaValissa{abs(kohteenRuutu->annaVaakaNumero() -
                           vihollisenRuutu->annaVaakaNumero()) -1};

    // Liikutaan pystysuunnassa
    if (pystyRuutujaValissa > vaakaRuutujaValissa) {
        // Liikutaan ylos ensin
        if (kohteenRuutu->annaPystyNumero() < vihollisenRuutu->annaPystyNumero()) {
            if (aktiivinenVihollinen_->liiku('Y') == true) {
                return true;
            } else if (aktiivinenVihollinen_->liiku('V') == true) {
                return true;
            } else if (aktiivinenVihollinen_->liiku('O') == true) {
                return true;
            } else if (aktiivinenVihollinen_->liiku('A') == true) {
                return true;
            }
        } else {
            if (aktiivinenVihollinen_->liiku('A') == true) {
                return true;
            } else if (aktiivinenVihollinen_->liiku('V') == true) {
                return true;
            } else if (aktiivinenVihollinen_->liiku('O') == true) {
                return true;
            } else if (aktiivinenVihollinen_->liiku('Y') == true) {
                return true;
            }
        }
    // Liikutaan vaakasuunnassa. Myös tilanne jos väliin jääviä ruutujua on
    // pystyssä ja vaa'assa saman verran.
    } else  {
        // Liikutaan vasemmalle ensin
        if (kohteenRuutu->annaVaakaNumero() < vihollisenRuutu->annaVaakaNumero()) {
            if (aktiivinenVihollinen_->liiku('V') == true) {
                return true;
            } else if (aktiivinenVihollinen_->liiku('A') == true) {
                return true;
            } else if (aktiivinenVihollinen_->liiku('Y') == true) {
                return true;
            } else if (aktiivinenVihollinen_->liiku('O') == true) {
                return true;
            }
        } else {
            if (aktiivinenVihollinen_->liiku('O') == true) {
                return true;
            } else if (aktiivinenVihollinen_->liiku('A') == true) {
                return true;
            } else if (aktiivinenVihollinen_->liiku('Y') == true) {
                return true;
            } else if (aktiivinenVihollinen_->liiku('V') == true) {
                return true;
            }
        }


    }
    return false;
}

bool tekoaly::ammu() {
    std::shared_ptr<toimijaRP> kohde;

    sijainti vihollisenSij{aktiivinenVihollinen_->annaSijainti()};
    std::shared_ptr<ruutu> vihollisenRuutu{laskeSijainninRuutu
                (vihollisenSij,ruudukko_)};
    int pystyNumero{vihollisenRuutu->annaPystyNumero()};
    int vaakaNumero{vihollisenRuutu->annaVaakaNumero()};

    int apuNumero;
    std::pair<int,int> pari;

    std::shared_ptr<ruutu> tarkisteltava;


    // Katsotaan pystyrivi paloissa. Ensin ylhäältä viholliseen (ampumissuunta ylos)
    apuNumero = pystyNumero - 1;
    while (apuNumero >= 0) {
        pari = std::make_pair(vaakaNumero,apuNumero);
        tarkisteltava = ruudukko_.at(pari);
        if (aktiivinenVihollinen_->voikoAmpua(tarkisteltava,'y') == false) {
            // Tässä on jo tarkistettu, että ruudussa oleva toimija ei voi olla kyborgi
            if (tarkisteltava->annaEste() != nullptr or tarkisteltava->annaToimija() != nullptr) {
                // Este on tiellä tai vihollinen
                break;
            }
        } else {
            // Ammutaan


            return true;
        }
        --apuNumero;
    }

    apuNumero = pystyNumero + 1;
    // Tässä katsotaan pystyrivi vihollisesta alas (ampumissuunta alas)
    while(apuNumero < 8) {
        pari = std::make_pair(vaakaNumero,apuNumero);
        tarkisteltava = ruudukko_.at(pari);
        if (aktiivinenVihollinen_->voikoAmpua(tarkisteltava,'a') == false) {
            // Tässä on jo tarkistettu, että ruudussa oleva toimija ei voi olla kyborgi
            if (tarkisteltava->annaEste() != nullptr or tarkisteltava->annaToimija() != nullptr) {
                // Este on tiellä tai vihollinen
                break;
            }
        } else {
            // Ammutaan
            return true;
        }
        ++apuNumero;
    }

    apuNumero = vaakaNumero - 1;
    // Ampumissuunta vasemmalle
    while (apuNumero >= 0) {
        pari = std::make_pair(apuNumero,pystyNumero);
        tarkisteltava = ruudukko_.at(pari);
        if (aktiivinenVihollinen_->voikoAmpua(tarkisteltava,'v') == false) {
            // Tässä on jo tarkistettu, että ruudussa oleva toimija ei voi olla kyborgi
            if (tarkisteltava->annaEste() != nullptr or tarkisteltava->annaToimija() != nullptr) {
                // Este on tiellä tai vihollinen
                break;
            }
        } else {
            // Ammutaan
            return true;
        }
        --apuNumero;
    }

    apuNumero = vaakaNumero + 1;
    // Ampumissuunta oikealle
    while (apuNumero < 11) {
        pari = std::make_pair(apuNumero,pystyNumero);
        tarkisteltava = ruudukko_.at(pari);
        if (aktiivinenVihollinen_->voikoAmpua(tarkisteltava,'o') == false) {
            // Tässä on jo tarkistettu, että ruudussa oleva toimija ei voi olla kyborgi
            if (tarkisteltava->annaEste() != nullptr or tarkisteltava->annaToimija() != nullptr) {
                // Este on tiellä tai vihollinen
                break;
            }
        } else {
            // Ammutaan
            return true;
        }
        ++apuNumero;
    }
    return false;
}


void tekoaly::aloitaTekoaly(std::vector<std::shared_ptr<vihollinen>> &viholliset,
                            std::shared_ptr<toimijaRP> &laura,
                            std::vector<std::shared_ptr<toimijaRP>> &kyborgit) {
    ruudukko_ = parkkihalliLogiikka_->annaRuudukko();
    std::vector<std::shared_ptr<vihollinen>>::iterator veciter;
    veciter = viholliset.begin();
    int kertoja{0};
    // Käydään läpi vain kolme kertaa, jotta vältytään ikuiselta silmukalta.
    while (kertoja < 3) {
        while (veciter != viholliset.end()) {
            int kerrat{0};
            aktiivinenVihollinen_ = *veciter;
            parkkihalliLogiikka_->asetaAktiivinenToimija
                    (std::dynamic_pointer_cast<toimijaRP>
                     (aktiivinenVihollinen_));
            // Jos ei voi liikkua ja jos on aiemmalla kierroksella käytetty osa tpisteistä.
            while (aktiivinenVihollinen_->onkoToimintapisteita() == true
                   and kerrat < 3) {
                kohde_ = laskeKohde(aktiivinenVihollinen_,laura,kyborgit);
                if (ammu() == true) {
                    // Kyborgiin osutaan
                    parkkihalliLogiikka_->asetaAmmus();


                } else if(liiku() == false) {
                    break;
                }
                ++ kerrat;
            }
            ++ veciter;
        }
        veciter = viholliset.begin();
        ++ kertoja;
    }
    // Vaihda vuoroa
    parkkihalliLogiikka_->vaihdaVuoroPelaajalle();

}


