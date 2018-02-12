#include "sijainti.h"

sijainti::sijainti()
{
}


sijainti::~sijainti()
{

}

int sijainti::annaX()
{
    return x_;

}

int sijainti::annaY()
{
    return y_;

}

void sijainti::asetaXY(int x, int y)
{
    x_ = x;
    y_ = y;

}

