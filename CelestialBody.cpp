#include "CelestialBody.h"

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

int main(int argc, char const *argv[])
{
    return 0;
}
