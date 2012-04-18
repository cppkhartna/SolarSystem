#include "SolSysBody.h"
//#include <float.h>
#include <cmath>
class Comet: public SolSysBody
{
public:
    Comet (double a, double e, double M0, double n, double O, double i, double w): SolSysBody (a, e, M0, n, O, i, w) {};
    virtual ~Comet (){};
    void Kepler(double GM, double T0, double T, double q, double e);
    void Parab(double GM, double M, double a, double e){};
    void Hyperb(double GM, double M, double a, double e){};

private:
    /* data */
};
