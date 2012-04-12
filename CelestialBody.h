#include "main.h"
class CelestialBody
{
public:
    CelestialBody ();
    virtual ~CelestialBody ();
    //void Draw(int mask);
    //void addDrawable(Drawable *object);

private:
    /* data */
    std::list< Drawable* > seq;
};
