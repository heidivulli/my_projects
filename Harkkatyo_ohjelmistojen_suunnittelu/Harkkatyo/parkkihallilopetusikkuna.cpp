#include "parkkihallilopetusikkuna.h"
#include "ui_parkkihallilopetusikkuna.h"

parkkihalliLopetusIkkuna::parkkihalliLopetusIkkuna(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::parkkihalliLopetusIkkuna)
{
    ui->setupUi(this);
    QObject::connect(ui->sulje,SIGNAL(clicked()),this,SLOT(close()));


}

parkkihalliLopetusIkkuna::~parkkihalliLopetusIkkuna()
{
    delete ui;
}

void parkkihalliLopetusIkkuna::peliHavittu()
{
    ui->tekstiKentta->append("HÄVISIT PELIN!");
    ui->tekstiKentta->append("Laura kuoli ja Tampereen parkkihallit ovat menetetty ikusiksi ajoiksi");
    ui->tekstiKentta->append("Kokeile uudestaan paremmalla onnella");

    this->show();
    QEventLoop eventLoop;
    QObject::connect(ui->sulje,SIGNAL(clicked()),
                                           &eventLoop, SLOT(quit()));


    eventLoop.exec();

    return;


}

void parkkihalliLopetusIkkuna::peliVoitettu(int vihollistenLukumaara, int pisteita, int rahaa, int teekkarikyborgejaElossa)
{
    ui->tekstiKentta->append("TUHOSIT PARKKIHALLIN!");
    ui->tekstiKentta->append("Vihollisia tuhosit: " + QString::number(vihollistenLukumaara)+ "kpl");
    ui->tekstiKentta->append("Teekkarikyborgeja selvisi hengissä: " + QString::number(teekkarikyborgejaElossa) + "kpl");
    ui->tekstiKentta->append("Rahaa tienasit: "+ QString::number(rahaa));
    ui->tekstiKentta->append("Pisteitä sait yhteensä: " + QString::number(pisteita + teekkarikyborgejaElossa*200));

    this->show();
    QEventLoop eventLoop;
    QObject::connect(ui->sulje,SIGNAL(clicked()),
                                           &eventLoop, SLOT(quit()));

    eventLoop.exec();

    return;

}

void parkkihalliLopetusIkkuna::peliKeskeytetty()
{
    ui->tekstiKentta->append("Lopetit pelin kesken!");
    ui->tekstiKentta->append("Saavutuksesi kyseisessä parkkihallissa on täten mitätöity");
    ui->tekstiKentta->append("Jatka pelaamista painamalla SULJE-nappia");

    this->show();
    QEventLoop eventLoop;
    QObject::connect(ui->sulje,SIGNAL(clicked()),
                                           &eventLoop, SLOT(quit()));

    eventLoop.exec();

    return;

}
