#include "CelestialBody.h"
const double kGauss    = 0.01720209895;  // gravitational constant
const double GM_Sun    = kGauss*kGauss;  // [AU^3/d^2]
const double Rad       = M_PI / 180.0;
const double AU        = 149597870.691;

class SolSysBody: public CelestialBody
{
public:
    SolSysBody(double a, double e, double M0, double n, double O, double i, double w);
    virtual ~SolSysBody (){};
    Vector State(double T);
    virtual void Kepler(double GM, double M, double T, double a, double e);
    void Ellip(double GM, double M, double a, double e);
    virtual Vector getPos(double T);
    virtual double getA();
    Vector setPos(Vector vec);
    Vector getVel() const;

private:
    /* data */
    double a, e, M0, O, i, w, n;
    Vector pos;
    Vector r, v; // temp vectors
    double T_last;
};

double EccAnom (double M, double e);

class Satellite: public SolSysBody
{
public:
    Satellite (double a, double e, double M0, double n, double O, double i, double w): SolSysBody (a, e, M0, n, O, i, w) {};
    virtual ~Satellite () {};
    virtual Vector getPos(double T);
    void setPlanet(SolSysBody* planet);

private:
    /* data */
    SolSysBody* planet;
};
