#include "CelestialBody.h"
CelestialBody::~CelestialBody()
{
    seq.clear();
}

void CelestialBody::Draw()
{
    text->setText(name);
    text->setScale(1.0/16.0);
    std::list< Drawable* >::iterator it;
    for (it = seq.begin(); it != seq.end(); ++it)
    {
        (*it)->Draw();
    }
    remove();
    text->setScale(1.0);
    text->setPos(Vector());
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
    //std::cout << name << ": " << pos << std::endl;
    add(text);
    std::list< Drawable* >::iterator it;
    for (it = seq.begin(); it != seq.end(); ++it)
    {
        (*it)->setScale(getScale());
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

double CelestialBody::getScale() const
{
    return scale;
}

void CelestialBody::setScale(double scale)
{
    this->scale = scale;
}
