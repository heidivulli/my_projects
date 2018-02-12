#include "virheikkuna.h"
#include "ui_virheikkuna.h"

virheIkkuna::virheIkkuna(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::virheIkkuna)
{
    ui->setupUi(this);
    QObject::connect(ui->lopetaNappi,SIGNAL(clicked()),this,SLOT(close()));



}

virheIkkuna::~virheIkkuna()
{
    delete ui;
}

void virheIkkuna::virheTapahtui(QString selite)
{
    ui->selite->setText("Syy: "+ selite);

    this->show();

    QEventLoop eventLoop;
    QObject::connect(ui->lopetaNappi,SIGNAL(clicked()),
                                           &eventLoop, SLOT(quit()));
    eventLoop.exec();
    return;
}
