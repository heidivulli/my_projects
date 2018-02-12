#include "ohjeet.h"
#include "ui_ohjeet.h"

Ohjeet::Ohjeet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Ohjeet)
{
    ui->setupUi(this);

    QObject::connect(ui->suljeNappi,SIGNAL(clicked()),this,SLOT(close()));
}

Ohjeet::~Ohjeet()
{
    delete ui;
}
