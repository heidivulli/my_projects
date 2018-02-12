#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ohjeet.h"

#include <QMainWindow>
#include <memory>



/**
 * @brief Määrittää aloitusIkkunan. Aloitusikkunasta pelaaja voi ainakin
 * aloittaa pelin, lukea ohjeet ja poistua pelistä.
 */

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Rakentaja
     */
    explicit MainWindow(QWidget *parent = 0);

    /**
     * @brief Purkaja
     */
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    std::shared_ptr<Ohjeet> pelinOhjeet_;

private slots:
    /**
     * @brief avaa, piilottaa tämän ikkunan ja kutsuu aloitapeliä
     * @post aloitapeli-metodia on kutsuttu, poikkeustakuu: vahva
     */
    void avaa();

    /**
     * @brief avaaOhjeet, luo ohjeet-olion ja avaa ohjeet
     * @post ohjeet aukeaa ikkunassa, poikkeustakuu: vahva
     */
    void avaaOhjeet();
};



#endif // MAINWINDOW_H
