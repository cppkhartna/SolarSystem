#include "Drawable.h"
#include <list>
const double kGauss    = 0.01720209895;  // gravitational constant
const double GM_Sun    = kGauss*kGauss;  // [AU^3/d^2]
const double Rad       = M_PI / 180.0;

class CelestialBody
{
public:
    CelestialBody (double, double, double, double, double, double, double);
    virtual ~CelestialBody (){};
    Vector State(double T);
    Vector Ellip(double GM, double M, double a, double e);
    void Draw();
    void add(Drawable *object);
    void nextFrame(double T);

private:
    /* data */
    double a, e, M0, O, i, w, n;
    Vector pos;
    std::list< Drawable* > seq;
};

double EccAnom (double M, double e);
