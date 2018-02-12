#include "lataatiedosto.h"
#include "virheikkuna.h"

#include <QEventLoop>


lataaTiedosto::lataaTiedosto(QObject *parent) :
    QObject(parent)
{
}

void lataaTiedosto::lataa(std::shared_ptr<QFile> uusiTiedosto)
{
    mgr_ = new QNetworkAccessManager(this);
    QEventLoop eventLoop;

    QObject::connect(mgr_, SIGNAL(finished(QNetworkReply*)),
    &eventLoop, SLOT(quit()));

    QNetworkRequest req(QUrl(QString("http://parkingdata.finnpark.fi:8080/Datex2/ParkingFacilities") ) );
    QString encoded =
        QString("tut:E2ksnh").toLocal8Bit().toBase64();
    encoded = "Basic " + encoded;

    req.setRawHeader("Authorization", encoded.toLocal8Bit());

    QNetworkReply * reply = mgr_->get(req);

    eventLoop.exec();

    if(reply->error()){
        std::shared_ptr<virheIkkuna> uusiVirheIkkuna {new virheIkkuna()};
        uusiVirheIkkuna->virheTapahtui
                ("Yhteys parkkihallin API-rajapintaan epäonnistui");
        return;
    }
    else
    {



        if(!uusiTiedosto->resize(0)){
            std::shared_ptr<virheIkkuna> uusiVirheIkkuna {new virheIkkuna()};
            uusiVirheIkkuna->virheTapahtui
                    ("Tiedoston parkkihalliDataApi.xml tyhjentäminen ei onnistunut!");
            return;

        }

        if(uusiTiedosto->open(QIODevice::WriteOnly)){
            uusiTiedosto->write(reply->readAll());
        }
        else{

            std::shared_ptr<virheIkkuna> uusiVirheIkkuna {new virheIkkuna()};
            uusiVirheIkkuna->virheTapahtui
                    ("Tiedostoon parkkihalliDataApi.xml kirjoittaminen ei onnistunut!");
            return;
        }
        uusiTiedosto->close();

        reply->deleteLater();
    }

}




