#include "este.h"

este::este()

{
}

este::~este()
{

}

std::shared_ptr<sijainti> este::annaSijainti() const
{
    return sijainti_;
}
