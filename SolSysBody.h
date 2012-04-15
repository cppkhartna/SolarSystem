#include "CelestialBody.h"
const double kGauss    = 0.01720209895;  // gravitational constant
const double GM_Sun    = kGauss*kGauss;  // [AU^3/d^2]
const double Rad       = M_PI / 180.0;

class SolSysBody: public CelestialBody
{
public:
    SolSysBody(double a, double e, double M0, double n, double O, double i, double w);
    virtual ~SolSysBody (){};
    Vector State(double T);
    Vector Ellip(double GM, double M, double a, double e);
    virtual Vector getPos(double T);

private:
    /* data */
    double a, e, M0, O, i, w, n;
    Vector pos;
    double T_last;
};

double EccAnom (double M, double e);

class Satellite: public SolSysBody
{
public:
    Satellite (double a, double e, double M0, double n, double O, double i, double w): SolSysBody (a, e, M0, n, O, i, w) {};
    virtual ~Satellite () {};
    virtual Vector getPos(double T);

private:
    /* data */
    SolSysBody* link;
};
