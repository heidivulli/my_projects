#include "kaupunkiikkuna.h"
#include "ui_kaupunkiikkuna.h"
#include "laura.h"
#include "sijainti.h"

kaupunkiIkkuna::kaupunkiIkkuna(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::kaupunkiIkkuna)
{
    scene_ = new QGraphicsScene(this);
    ui->setupUi(this);

    QObject::connect(ui->phalliNappi,SIGNAL(clicked()),this,SLOT(avaaPhalliPeli()));
    QObject::connect(ui->lopetaNappi,SIGNAL(clicked()),this,SLOT(lopetaPeli()));
    QObject::connect(ui->kauppaNappi, SIGNAL(clicked()),this, SLOT(avaaKauppa()));

    ui->phalliNappi->setEnabled(false);
    ui->kauppaNappi->setEnabled(false);

    ui->parkkihallinTiedot->append("PARKKIHALLIN TIEDOT:");
    ui->parkkihallinTiedot->append("Parkkihalleja ei ole Lauran lähellä");

}

kaupunkiIkkuna::~kaupunkiIkkuna()
{
    delete ui;
}

void kaupunkiIkkuna::asetaTausta(QGraphicsPixmapItem *item)
{
    scene_->addItem(item);
    ui->peliKartta->setScene(scene_);

}

void kaupunkiIkkuna::asetaLauranKuva(std::shared_ptr<toimijaRP> uusiLaura) {

    //asetetaan Lauran kuva näkymään kartalle
    QImage lauranKuva(":/new/prefix1/Kuvat/laura.png");

    std::dynamic_pointer_cast<laura> (uusiLaura)->setPixmap(QPixmap::fromImage(lauranKuva));
    std::dynamic_pointer_cast<laura> (uusiLaura)->setPos(100,100);
    scene_->addItem( std::dynamic_pointer_cast<laura>(uusiLaura).get());


    std::dynamic_pointer_cast<laura> (uusiLaura)->setFlag(QGraphicsItem::ItemIsFocusable);
    std::dynamic_pointer_cast<laura> (uusiLaura)->setFocus();

    //asetetaan kuvan kääntymistä varten sen keskikohta
    qreal x = 42;
    qreal y = 33;
    std::dynamic_pointer_cast<laura> (uusiLaura)->setTransformOriginPoint(x, y);


}

void kaupunkiIkkuna::asetaParkkihalli(std::shared_ptr<parkkihalli> phalli)
{
    //scene_->removeItem(phalli.get());
    QString teksti;
    if(phalli->onkoTuhottu()){
        teksti = "tuhottuPhalli.png";
    }

    else if (phalli->annaVaikeus() == "Helppo") {
        teksti = "phalli.png";
    }
    else if (phalli->annaVaikeus() == "Kohtalainen") {
        teksti = "phalliKeskivaikea.png";
    }
    else {
        teksti = "phalliVaikea.png";
    }

    QImage parkkihallinKuva(":/new/prefix1/Kuvat/" + teksti);

    phalli->setPixmap(QPixmap::fromImage(parkkihallinKuva));

    sijainti parkkihallinSijainti = phalli->annaSijainti();
    int xSij = parkkihallinSijainti.annaX();
    int ySij = parkkihallinSijainti.annaY();

    //otetaan huomioon kuvan koko myös
    phalli->setPos(xSij-14,ySij-14);

    scene_->addItem(phalli.get());

}

void kaupunkiIkkuna::phalliNapinTila(bool tila)
{
    if (tila == true) {
        ui->phalliNappi->setEnabled(true);
    }
    else {
        ui->phalliNappi->setEnabled(false);
    }


}

void kaupunkiIkkuna::asetaKaupanKuva(sijainti &sij)
{
    //asetetaan kaupan kuva kartalle
    QGraphicsPixmapItem *kaupanKuva = ui->peliKartta->scene()->addPixmap(QPixmap(":/new/prefix1/Kuvat/kauppa.png"));

    //Laitetaan paikka kohdalleen
    qreal x = sij.annaX() - 35;
    qreal y = sij.annaY() - 35;
    kaupanKuva->setPos(x, y);

}

void kaupunkiIkkuna::kauppaNapinTila(bool tila)
{
    if (tila == true) {
        ui->kauppaNappi->setEnabled(true);
    }
    else {
        ui->kauppaNappi->setEnabled(false);
    }
}

void kaupunkiIkkuna::paivitaParkkihallinTiedot(std::shared_ptr<parkkihalli> phalli){
    if(phalli == nullptr){
        ui->parkkihallinTiedot->clear();

        ui->parkkihallinTiedot->append("PARKKIHALLIN TIEDOT:");
        ui->parkkihallinTiedot->append("Parkkihalleja ei ole Lauran lähellä");
    }
    else if(!phalli->onkoTuhottu()){
        ui->parkkihallinTiedot->clear();
        ui->parkkihallinTiedot->append("PARKKIHALLIN TIEDOT:");

        ui->parkkihallinTiedot->append("ID: "+ phalli->annaID());
        ui->parkkihallinTiedot->append("Koko: " +phalli->annaKokoString());
        ui->parkkihallinTiedot->append("Vaikeus: " +phalli->annaVaikeus());

    }
    else{
        ui->parkkihallinTiedot->clear();
        ui->parkkihallinTiedot->append("PARKKIHALLIN TIEDOT:");
        ui->parkkihallinTiedot->append("Parkkihalli on tuhottu!");
    }

}

void kaupunkiIkkuna::paivitaRahat(int rahat)
{
    ui->rahaNaytto->setProperty("value", rahat);
}

void kaupunkiIkkuna::paivitaPisteet(int pisteet)
{
    ui->pisteNaytto->setProperty("value", pisteet);
}

void kaupunkiIkkuna::paivitaParkkihallinKuva(std::shared_ptr<parkkihalli> phalli)
{
    QString teksti;
    if(phalli->onkoTuhottu()){
        teksti = "tuhottuPhalli.png";
    }

    //asetetan kartalle eri värinen parkkihalli-kuva riippuen siitä,
    //kuinka vaikea parkkihalli on
    else if (phalli->annaVaikeus() == "Helppo") {
        teksti = "phalli.png";
    }
    else if (phalli->annaVaikeus() == "Kohtalainen") {
        teksti = "phalliKeskivaikea.png";
    }
    else {
        teksti = "phalliVaikea.png";
    }

    QImage parkkihallinKuva(":/new/prefix1/Kuvat/" + teksti);

    phalli->setPixmap(QPixmap::fromImage(parkkihallinKuva));
}

void kaupunkiIkkuna::avaaPhalliPeli() {
    this->hide();
    emit phalliNappiPainettu();
}

void kaupunkiIkkuna::avaaKauppa()
{
    this->hide();
    emit kauppaNappiPainettu();
}

void kaupunkiIkkuna::lopetaPeli()
{
    this->close();
    emit lopetaNappiPainettu();
}







