#ifndef KAUPPAIKKUNA_H
#define KAUPPAIKKUNA_H

#include <QMainWindow>

/**
 *@brief KauppaIkkuna-luokka esittää pelaajalle kaupan grafiikan,
 * sekä pitää huolen siitä, mitä pelaaja voi ostaa.
 */
namespace Ui {
class KauppaIkkuna;
}

class KauppaIkkuna : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief KauppaIkkuna, rakentaja
     * @param parent
     */
    explicit KauppaIkkuna(QWidget *parent = 0);
    /**
     * @brief purkaja
     */
    ~KauppaIkkuna();
    
    /**
     * @brief rahanMaara asettaa rahan näkyville kauppaIkkunan rahaNaytolle
     * @param rahat, sen hetkiset pelaajan voittamat rahat
     * @pre parametrina annetaan pelaajan sen hetkiset rahat, 
     * rahaNaytto löytyy kauppaIkkunasta
     * @post rahat näkyvät kauppaIkkunassa, poikkeustakuu: nothrow
     */
    void rahanMaara(int rahat);
    
    /**
     * @brief mitaVoiOstaa päivittää kauppaIkkunan osta-nappien aktiivisuuden niin,
     * että pelaaja voi ostaa vain tuotteita joihin hänen rahansa riittävät
     * @param rahat, pelaajan sen hetkiset rahat
     * @pre parametrina annetaan pelaajan sen hetkiset rahat,
     * kaikki osta napit löytyvät kauppaIkkunasta
     * @post osta-napit aktivoitu oikein, poikkeustakuu: nothrow
     */
    void mitaVoiOstaa(int rahat);
    
    /**
     * @brief mitaOstettu päivittää kauppaikkunan osta-nappien aktiivisuuden niin,
     * että pelaaja voi ostaa vain tuotteita mitä Lauralla ei vielä ole
     * @param ase, kertoo mikä ase Lauralla on
     * @param kilpi, kertoo onko Lauralla jo kilpeä
     * @pre ase ja kilpi arvot annettu oikein, 
     * kaikki osta napit löytyvät kauppaIkkunasta
     * @post osta-napit aktivoitu oikein, poikkeustakuu: nothrow
     */
    void mitaOstettu(int ase, bool kilpi);

public slots:
    /**
     * @brief kilpiNappi, ostaKilpi-nappia painettu,
     * lähettää kilpiNappiPainettu()-signaalin
     */
    void kilpiNappi();
    /**
     * @brief haulikkoNappi, ostaHaulikko-nappia painettu,
     * lähettää haulikkoNappiPainettu()-signaalin
     */
    void haulikkoNappi();
    /**
     * @brief kivaariNappi, ostaKivaari-nappia painettu,
     * lähettää kivaariNappiPainettu()-signaalin
     */
    void kivaariNappi();
    /**
     * @brief suljeKauppa, palaaNappi-painettu,
     * lähettää kauppaSuljettu(loputRahat)-signaalin,
     * jonka parametrina on jäljelle jääneet rahat
     */
    void suljeKauppa();

signals:
    /**
     * @brief kilpiNappiPainettu on signaali,
     * joka lähetetään kun pelaaja ostaa kilven.
     * se napataan Kauppa-luokassa
     */
    void kilpiNappiPainettu();
    /**
     * @brief haulikkoNappiPainettu on signaali,
     * joka lähetetään kun pelaaja ostaa haulikon.
     * se napataan Kauppa-luokassa
     */
    void haulikkoNappiPainettu();
    /**
     * @brief kivaariNappiPainettu on signaali,
     * joka lähetetään kun pelaaja ostaa kivaarin.
     * se napataan Kauppa-luokassa
     */
    void kivaariNappiPainettu();
    /**
     * @brief kauppaSuljettu on signaali,
     * joka lähetetään kun pelaaja painaa Palaa-nappia.
     * se napataan Kaupunki-luokassa
     * @param loputRahat, ostosten jälkeen jäljelle jääneet rahat
     */
    void kauppaSuljettu(int loputRahat);

private:
    Ui::KauppaIkkuna *ui;
};

#endif // KAUPPAIKKUNA_H
