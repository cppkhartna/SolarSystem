#include "Drawable.h"
#include <list>

class CelestialBody
{
public:
    CelestialBody (): scale(0) {};
    virtual ~CelestialBody ();
    void Draw();
    void add(Drawable *object);
    void remove();
    void nextFrame(double T);
    virtual Vector getPos(double T);
    virtual double getA();
    double getScale() const;
    void setScale(double scale);
    std::string name;

private:
    /* data */
    std::list< Drawable* > seq;
    double scale;
};
