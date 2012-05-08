#include "Drawable.h"
#include <list>

class CelestialBody
{
public:
    CelestialBody () {};
    virtual ~CelestialBody ();
    void Draw();
    void add(Drawable *object);
    void remove();
    void nextFrame(double T);
    virtual Vector getPos(double T);
    virtual double getA();
    std::string name;

private:
    /* data */
    std::list< Drawable* > seq;
};
