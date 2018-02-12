#ifndef XMLPARKKIHALLIREADER_H
#define XMLPARKKIHALLIREADER_H

#include "parkkihalli.h"

#include <memory>
#include <QXmlStreamReader>

/**
 * @brief xmlParkkihalliReader lukee annetun xml.tiedoston
 * ja päivittää parkkihallien tiedot tiedoston mukaisiksi.
 */

class xmlParkkihalliReader
{

public:
    /**
     * @brief Rakentaja
     */
    xmlParkkihalliReader(std::shared_ptr<std::vector<std::shared_ptr<parkkihalli>>> phalliVektori);

    /**
     * @brief Purkaja
     */
    ~xmlParkkihalliReader();

    /**
     * @brief read aloittaa XML-tiedoston lukemisen. Määrittää tarvitaanko
     * staattisia tietoja, eli ollaanko tiedostoa lukemassa ensimmäistä kertaa.
     * Kutsuu tarpeen mukaan lueParkkihalliStatic() funktiota.
     * @param tiedosto, jota luetaan
     * @return truen, jos lukemin onnistuu. False jos lukeminen epäonnistuu
     */
    bool read(QIODevice *device);

private:
    std::shared_ptr<std::vector<std::shared_ptr<parkkihalli>>> phalliVektori_;
    QXmlStreamReader reader_;


    /**
     * @brief lueParkkihalliStatic lukee XML-tiedoston staattiset tiedot
     * (id, parkkihallin nimi, koko ja koordinaatit). Tallennetaan parkkihallit vektoriin.
     * Kaikki streetParking-tyyppiset parkkihallit ohitetaan.
     * @pre -
     * @return true, jos lukeminen onnistui, false jos epäonnistui.
     * @post phalliVektori_:iin on tallennettu kaikki parkkihallit, jotka ovat
     * kartan kokoalueella. Parkkihalleihin tallennettu id, nimi, koko ja koordinaatit
     */
    bool lueParkkihalliStatic();

    /**
     * @brief lueParkkihalliStatus lukee muuttuvat tiedot eli varattujen paikkojen määrän.
     * Asettaa myös parkkihallin vaikeuden.
     * @pre -
     * @return  true, jos lukeminen onnistuu. False jos epäonnistuu
     * @post parkkihalliin on asetettu varattujen paikkojen määrä ja vaikeusaste.
     */
    bool lueParkkihalliStatus();

};


#endif // XMLPARKKIHALLIREADER_H
