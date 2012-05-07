#include "CelestialBody.h"
CelestialBody::~CelestialBody()
{
    seq.clear();
}

void CelestialBody::Draw()
{
    std::list< Drawable* >::iterator it;
    for (it = seq.begin(); it != seq.end(); ++it)
    {
        (*it)->Draw();
    }
}

void CelestialBody::add(Drawable *object)
{
    seq.push_back(object);
}

void CelestialBody::remove()
{
    seq.pop_back();
}

void CelestialBody::nextFrame(double T)
{
    Vector pos = getPos(T);
    std::list< Drawable* >::iterator it;
    for (it = seq.begin(); it != seq.end(); ++it)
    {
        (*it)->setPos(pos);
    }
}

Vector CelestialBody::getPos(double T)
{
    return Vector();
}

double CelestialBody::getA()
{
    return 0.387099;
}
