#include "aloitapeli.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->aloita,SIGNAL(clicked()),this,SLOT(avaa()));
    QObject::connect(ui->ohjeetNappi,SIGNAL(clicked()),this,SLOT(avaaOhjeet()));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::avaa() {
    // kutsuu aloitapeli()
    this->hide();
    aloitapeli();
}

void MainWindow::avaaOhjeet()
{
    std::shared_ptr<Ohjeet> pelinOhjeet{new Ohjeet};
    pelinOhjeet_ = pelinOhjeet;
    pelinOhjeet->show();
}





