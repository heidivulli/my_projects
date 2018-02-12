#include "kaupunki.h"
#include "parkkihalliikkuna.h"
#include "phallinapufunktiot.h"
#include "ruutu.h"
#include "ui_parkkihalliikkuna.h"
#include "parkkihallilopetusikkuna.h"


parkkihalliIkkuna::parkkihalliIkkuna(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::parkkihalliIkkuna),
    kyborgi1Kuollut_{false},
    kyborgi2Kuollut_{false}
{
    scene_ = new QGraphicsScene(this);
    ui->setupUi(this);

    QObject::connect(ui->lopetaNappi,SIGNAL(clicked()),this,SLOT(suljeNappiaPainettu()));
    QObject::connect(ui->laura, SIGNAL(clicked()), this, SLOT(asetaVuoroLauralle()));
    QObject::connect(ui->kyborgi1, SIGNAL(clicked()), this, SLOT(asetaVuoroKyborgi1()));
    QObject::connect(ui->kyborgi2, SIGNAL(clicked()), this, SLOT(asetaVuoroKyborgi2()));
    QObject::connect(ui->vuoronVaihto, SIGNAL(clicked()), this, SLOT(lopetaOmaVuoroNapista()));

    // Tämän avulla saatiin hahmojen liikuttaminen hallissa toimimaan.
    setFocusPolicy(Qt::StrongFocus);

}

parkkihalliIkkuna::~parkkihalliIkkuna() {
    delete ui;
}

void parkkihalliIkkuna::asetaTausta(QGraphicsPixmapItem *item) {
    scene_->addItem(item);
    ui->halliKartta->setScene(scene_);   
}

void parkkihalliIkkuna::asetaUImuut(int ase, bool kilpi) {
    // Asetetaan napit toimiviksi
    ui->kyborgi1->setEnabled(true);
    ui->kyborgi2->setEnabled(true);
    ui->laura->setEnabled(true);
    ui->lauraTP->display("3");
    ui->kyborgi1TP->display("3");
    ui->kyborgi2TP->display("3");

    //asetetaan käytettävä ase näkyville
    if (ase == 0) {
        ui->pistooli->setVisible(true);
        ui->haulikko->setVisible(false);
        ui->kivaari->setVisible(false);
    }
    else if (ase == 1) {
        ui->pistooli->setVisible(false);
        ui->haulikko->setVisible(true);
        ui->kivaari->setVisible(false);
    }
    else {
        ui->pistooli->setVisible(false);
        ui->haulikko->setVisible(false);
        ui->kivaari->setVisible(true);
    }
    if (kilpi == false) {
        ui->kilpi->setVisible(false);
    }
    else {
        ui->kilpi->setVisible(true);
    }
}

//---------------

void parkkihalliIkkuna::asetaKuvaLaura(std::shared_ptr<toimijaRP> & laura) {
    QImage kuva(":/new/prefix1/Kuvat/laura.png");
    std::dynamic_pointer_cast<teekkariKyborgi> (laura)->setPixmap(QPixmap::fromImage(kuva));
}

void parkkihalliIkkuna::asetaKuvaKyborgi1(std::shared_ptr<toimijaRP> &kyborgi1) {
    QImage kuva(":/new/prefix1/Kuvat/teekkariKyborgi.png");
    std::dynamic_pointer_cast<teekkariKyborgi> (kyborgi1)->setPixmap(QPixmap::fromImage(kuva));
}

void parkkihalliIkkuna::asetaKuvaKyborgi2(std::shared_ptr<toimijaRP> &kyborgi2) {
    QImage kuva(":/new/prefix1/Kuvat/teekkariKyborgi2.png");
    std::dynamic_pointer_cast<teekkariKyborgi> (kyborgi2)->setPixmap(QPixmap::fromImage(kuva));
}


//----------------


void parkkihalliIkkuna::asetaToimija(std::shared_ptr<toimijaRP> &toimija) {
    int x_sij{(toimija->annaSijainti()).annaX()};
    int y_sij{(toimija->annaSijainti()).annaY()};

    std::dynamic_pointer_cast<teekkariKyborgi> (toimija)->setPos(x_sij,y_sij);
    scene_->addItem( std::dynamic_pointer_cast<teekkariKyborgi>(toimija).get());

    std::dynamic_pointer_cast<teekkariKyborgi> (toimija)->setFlag(QGraphicsItem::ItemIsFocusable);
    std::dynamic_pointer_cast<teekkariKyborgi> (toimija)->setFocus();

    //asetetaan kuvan kääntymistä varten sen keskikohta
    qreal x = 42;
    qreal y = 33;
    std::dynamic_pointer_cast<teekkariKyborgi> (toimija)->setTransformOriginPoint(x, y);

    //aluksi toimijan suunta alaspäin
    char suunta = 'a';
    std::dynamic_pointer_cast<teekkariKyborgi> (toimija)->kaanny(suunta);

    std::dynamic_pointer_cast<teekkariKyborgi> (toimija)->setFlag(QGraphicsItem::ItemIsFocusable);
}



void parkkihalliIkkuna::asetaVihollinen(std::shared_ptr<vihollinen> & vihulainen) {
    QImage kuva(":/new/prefix1/Kuvat/vihollinen.png");
    vihulainen->setPixmap(QPixmap::fromImage(kuva));

    int x_sij{(vihulainen->annaSijainti()).annaX()};
    int y_sij{(vihulainen->annaSijainti()).annaY()};

    vihulainen->setPos(x_sij,y_sij);
    scene_->addItem(vihulainen.get());

    vihulainen->setFlag(QGraphicsItem::ItemIsFocusable);
    vihulainen->setFocus();

    //asetetaan kuvan kääntymistä varten sen keskikohta
    qreal x = 30;
    qreal y = 33;
    vihulainen->setTransformOriginPoint(x, y);

    //aluksi vihulaisen suunta alaspäin
    char suunta = 'a';
    vihulainen->kaanny(suunta);
}

void parkkihalliIkkuna::asetaEste(std::shared_ptr<ruutu> esteRuutu) {
    std::shared_ptr<este> piirrettavaEste = esteRuutu->annaEste();

    QImage kuva(":/new/prefix1/Kuvat/auto.png");
    piirrettavaEste->setPixmap(QPixmap::fromImage(kuva));

    int x_sij{(esteRuutu->annaSijainti())->annaX()};
    int y_sij{(esteRuutu->annaSijainti())->annaY()};

    piirrettavaEste->setPos(x_sij,y_sij);
    scene_->addItem(piirrettavaEste.get());
}

void parkkihalliIkkuna::asetaAmmus(QImage kuva, ammus *luoti, int xSijainti, int ySijainti, char suunta) {
    luoti->setPixmap(QPixmap::fromImage(kuva));

    luoti->setPos(xSijainti,ySijainti);
    luoti->asetaSijainti(xSijainti,ySijainti);

    scene_->addItem(luoti);

    //asetetaan kuvan kääntymistä varten sen keskikohta
    qreal x = 9;
    qreal y = 30;
    luoti->setTransformOriginPoint(x, y);
    luoti->kaanny(suunta);
}

// -------------------

// Palauttaa false, jos myös muilta sankareilta on loppunut toimintapisteet
bool parkkihalliIkkuna::lauraltaLoppuiToiminnot() {
    ui->lauraTP->display("0");
    ui->laura->setEnabled(false);
    ui->laura->setAutoFillBackground(false);
    if (ui->kyborgi1->isEnabled() == false and ui->kyborgi2->isEnabled() == false) {
        // vaihdetaan vuoro vastustajalle
        return false;
    }
    return true;
 }

bool parkkihalliIkkuna::kyborgi1LoppuiToiminnot() {
    ui->kyborgi1TP->display("0");
    ui->kyborgi1->setEnabled(false);
    ui->kyborgi1->setAutoFillBackground(false);
    if (ui->laura->isEnabled() == false and ui->kyborgi2->isEnabled() == false) {
        // vaihdetaan vuoro vastustajalle
        return false;
    }
    return true;
}

bool parkkihalliIkkuna::kyborgi2LoppuiToiminnot() {
    ui->kyborgi2TP->display("0");
    ui->kyborgi2->setEnabled(false);
    ui->kyborgi2->setAutoFillBackground(false);
    if (ui->laura->isEnabled() == false and ui->kyborgi1->isEnabled() == false) {
        // vaihdetaan vuoro vastustajalle
        return false;
    }
    return true;
}

void parkkihalliIkkuna::vaihdaSankariaNapista() {
    if (ui->laura->autoFillBackground() == true) {
        if (ui->kyborgi2->isEnabled() == true) {
            asetaVuoroKyborgi2();
        } else if (ui->kyborgi1->isEnabled() == true) {
            asetaVuoroKyborgi1();
        }
    } else if (ui->kyborgi2->autoFillBackground() == true) {
        if (ui->kyborgi1->isEnabled() == true) {
            asetaVuoroKyborgi1();
        } else if (ui->laura->isEnabled() == true) {
            asetaVuoroLauralle();
        }
    } else {
        if (ui->laura->isEnabled() == true) {
            asetaVuoroLauralle();
        } else if (ui->kyborgi2->isEnabled() == true) {
            asetaVuoroKyborgi2();
        } else if (ui->kyborgi1->isEnabled() == true) {
            asetaVuoroKyborgi1();
        }
    }
}

void parkkihalliIkkuna::asetaVuoroPelaajalle() {
    if (kyborgi1Kuollut_ == false) {
        ui->kyborgi1->setEnabled(true);
        ui->kyborgi1TP->display("3");
    }
    if (kyborgi2Kuollut_ == false) {
        ui->kyborgi2->setEnabled(true);
        ui->kyborgi2TP->display("3");
    }
    ui->laura->setEnabled(true);
    ui->lauraTP->display("3");
    ui->vuoronVaihto->setEnabled(true);
}

void parkkihalliIkkuna::tuhoaKyborgi(char kyborginNumero) {
    if (kyborginNumero == '1') {
        kyborgi1Kuollut_ = true;
        ui->kyborgi1->setEnabled(false);
        ui->kyborgi1->setAutoFillBackground(false);
        ui->kyborgi1TP->display("0");
    } else if (kyborginNumero == '2') {
        kyborgi2Kuollut_ = true;
        ui->kyborgi2->setEnabled(false);
        ui->kyborgi2->setAutoFillBackground(false);
        ui->kyborgi2TP->display("0");
    } else {
        if (kyborgi1Kuollut_ == true) {
            kyborgi2Kuollut_ = true;
            ui->kyborgi2->setEnabled(false);
            ui->kyborgi2->setAutoFillBackground(false);
            ui->kyborgi2TP->display("0");
        } else {
            kyborgi1Kuollut_ = true;
            ui->kyborgi1->setEnabled(false);
            ui->kyborgi1->setAutoFillBackground(false);
            ui->kyborgi1TP->display("0");
        }
    }
}

bool parkkihalliIkkuna::onkoKyborgi1Kuollut() {
    return kyborgi1Kuollut_;
}

void parkkihalliIkkuna::asetaToimintapisteetNaytolle(int TP) {
    if (ui->laura->autoFillBackground() == true) {
        ui->lauraTP->display(TP);
    } else if (ui->kyborgi1->autoFillBackground() == true) {
        ui->kyborgi1TP->display(TP);
    } else if (ui->kyborgi2->autoFillBackground() == true) {
        ui->kyborgi2TP->display(TP);
    }
}

void parkkihalliIkkuna::asetaRahaJaPisteetNaytolle(int raha, int pisteet) {
    ui->pisteNaytto->display(pisteet);
    ui->rahaNaytto->display(raha);
}

void parkkihalliIkkuna::asetaLauranElamatNaytolle(int elamat) {
    ui->lauraHP->display(elamat);
}

void parkkihalliIkkuna::asetaKyborgi1ElamatNaytolle(int elamat) {
    ui->kyborgi1HP->display(elamat);
}

void parkkihalliIkkuna::asetaKyborgi2ElamatNaytolle(int elamat) {
    ui->kyborgi2HP->display(elamat);
}



// -------------------

void parkkihalliIkkuna::avaaKikkuna() {
    this->close();
    kyborgi1Kuollut_ = false;
    kyborgi2Kuollut_ = false;
    emit phalliLoppunut();
}

// -------------------

void parkkihalliIkkuna::asetaVuoroLauralle() {
    ui->kyborgi1->setAutoFillBackground(false);
    ui->kyborgi2->setAutoFillBackground(false);

    ui->laura->setAutoFillBackground(true);
    ui->laura->setPalette(QPalette(Qt::red));
    emit vuoroLauralle();
}

void parkkihalliIkkuna::asetaVuoroKyborgi1() {
    if (kyborgi1Kuollut_ == false) {
        ui->kyborgi2->setAutoFillBackground(false);
        ui->laura->setAutoFillBackground(false);

        ui->kyborgi1->setAutoFillBackground(true);
        ui->kyborgi1->setPalette(QPalette(Qt::red));
        emit vuoroKyborgille1();
    }
}

void parkkihalliIkkuna::asetaVuoroKyborgi2() {
    if (kyborgi2Kuollut_ == false) {
        ui->kyborgi1->setAutoFillBackground(false);
        ui->laura->setAutoFillBackground(false);

        ui->kyborgi2->setAutoFillBackground(true);
        ui->kyborgi2->setPalette(QPalette(Qt::red));
        emit vuoroKyborgille2();
    }
}

// -------------------

// Tähän päästään, jos käyttäjä on painanut "lopeta oma vuoro"- nappia.
void parkkihalliIkkuna::lopetaOmaVuoroNapista() {
    if (ui->laura->isEnabled() == true) {
        ui->laura->setEnabled(false);
    }
    if (ui->kyborgi1->isEnabled() == true) {
        ui->kyborgi1->setEnabled(false);
    }
    if (ui->kyborgi2->isEnabled() == true) {
        ui->kyborgi2->setEnabled(false);
    }
    ui->lauraTP->display("0");
    ui->kyborgi1TP->display("0");
    ui->kyborgi2TP->display("0");
    vuoronVaihtoVastustajalle();
}

void parkkihalliIkkuna::suljeNappiaPainettu() {
    this->close();
    std::shared_ptr<parkkihalliLopetusIkkuna>
            uusiLopetusIkkuna(new parkkihalliLopetusIkkuna);
    uusiLopetusIkkuna->peliKeskeytetty();
    avaaKikkuna();
}


void parkkihalliIkkuna::keyPressEvent(QKeyEvent *event) {
    std::string nappain;
    if (event->key() == Qt::Key_Left) {
        nappain = "vasen";
        emit nappaintaPainettuLiiku(nappain);
    } else if (event->key() == Qt::Key_Right){
        nappain = "oikea";
        emit nappaintaPainettuLiiku(nappain);
    } else if (event->key() == Qt::Key_Up) {
        nappain = "ylos";
        emit nappaintaPainettuLiiku(nappain);
    } else if (event->key() == Qt::Key_Down) {
        nappain = "alas";
        emit nappaintaPainettuLiiku(nappain);
    } else if (event->key() == Qt::Key_Tab) {
        vaihdaSankariaNapista();
    } else if(event->key() == Qt::Key_Space) {
        emit nappaintaPainettuAmmu();
    } else if (event->key() == Qt::Key_Enter or
               event->key() == Qt::Key_Return) {
        lopetaOmaVuoroNapista();
    }

}


void parkkihalliIkkuna::vuoronVaihtoVastustajalle() {
    ui->laura->setAutoFillBackground(false);
    ui->kyborgi1->setAutoFillBackground(false);
    ui->kyborgi2->setAutoFillBackground(false);
    ui->vuoronVaihto->setEnabled(false);
    emit vuoroVaihtunut();
}





