#ifndef LATAATIEDOSTO_H
#define LATAATIEDOSTO_H

#include <QFile>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <memory>

/**
 * @brief lataaTiedosto luokan avulla ladataan xml-tiedosto
 * API-rajapinnan kautta ja tallennetaan se
 * parkkihalliDataApi.xml- tiedostoon.
 */
class lataaTiedosto: public QObject
{
    Q_OBJECT

public:
    explicit lataaTiedosto(QObject *parent = 0);

    /**
     * @brief lataa-funktio lataa parkkihallidatan käyttäen
     * API-rajapintaa ja kirjoittaa se annettuun tiedostoon.
     * Avaa virheikkunan virheen tapahtuessa ja lopettaa pelin.
     * @param älykäs osoitin tiedostoon mihin halutaan kirjoittaa
     * API-rajapinnan antama data
     * @post tiedostoon on kirjoitettu API-rajapinnasta saatu
     * data.
     * @poikkeustakuu: heikko
     */
    void lataa(std::shared_ptr<QFile> uusiTiedosto);

private:
    QNetworkAccessManager *mgr_;
};

#endif // LATAATIEDOSTO_H
