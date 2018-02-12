#ifndef ESTE_H
#define ESTE_H

#include "sijainti.h"

#include <QObject>
#include <QGraphicsPixmapItem>
#include <memory>

/**
 * @brief Este-luokka kuvaa parkkihallissa olevia esteitä.
 * Tällä hetkellä ei ole paljon toteutusta, tätä on tarkoitust jatkaa
 * jatkokehityksessä.
 */

class este: public QObject, public QGraphicsPixmapItem{
        Q_OBJECT
public:
    este();
    ~este();

    std::shared_ptr<sijainti> annaSijainti() const;


private:
    std::shared_ptr<sijainti> sijainti_;
};

#endif // ESTE_H
