#include "Drawable.h"
#include <list>

class CelestialBody
{
public:
    CelestialBody () {};
    virtual ~CelestialBody (){};
    void Draw();
    void add(Drawable *object);
    void nextFrame(double T);
    virtual Vector getPos(double T);

private:
    /* data */
    std::list< Drawable* > seq;
};

double EccAnom (double M, double e);
