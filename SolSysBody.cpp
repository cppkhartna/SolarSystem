#include "SolSysBody.h"

SolSysBody::SolSysBody (double a, double e, double M0, double n, double O, double i, double w): a(a), e(e), M0(M0), O(O), i(i), w(w), n(n) {};

Vector SolSysBody::State(double T)
{
  const double p = 1.3970;  

  double T0 = 0.0; // epoch J2000
  Matrix PQR;

  Kepler(GM_Sun, Rad*(M0+n*(T-T0)), T, a, e); 
  PQR = GaussVec(Rad*(O+p*T), Rad*i, Rad*(w-O));
  r = PQR*r;                                       
  v = PQR*v;                                       

  return r;
}

void SolSysBody::Kepler(double GM, double M, double T, double a, double e)
{
    Ellip(GM, M, a, e);
}

void SolSysBody::Ellip(double GM, double M, double a, double e)
{
  double k, E, cosE,sinE, fac, rho;

  k  = sqrt(GM/a);
  E  = EccAnom(M,e);   

  cosE = cos(E); 
  sinE = sin(E);

  fac = sqrt ((1.0-e)*(1.0+e));  

  rho = 1.0 - e*cosE;

  r = Vector(a*(cosE-e), a*fac*sinE, 0.0);
  v = Vector(-k*sinE/rho, k*fac*cosE/rho, 0.0); 
}

double EccAnom (double M, double e)
{
  const int maxit = 15;
  const double eps = 100.0*eps_mach;

  int    i=0;
  double E, f;

  M = Modulo(M, 2.0*M_PI);   
  if (e<0.8) E=M; else E=M_PI;

  do {
    f = E - e*sin(E) - M;
    E = E - f / ( 1.0 - e*cos(E) );
    ++i;
    if (i==maxit) {
        std::cerr << " Convergence problems in EccAnom" << std::endl;
      break;
    }
  }
  while (fabs(f) > eps);

  return E;
}

Vector SolSysBody::getVel() const
{
    return v;
}

Vector SolSysBody::setPos(Vector vec)
{
    pos = vec;
    return pos;
}

Vector SolSysBody::getPos(double T)
{
    if (T - T_last < eps_mach)
    {
        return pos;
    }
    else
    {
        T_last = T;
        return setPos(State(T));
    }
}

void Satellite::setPlanet(SolSysBody* planet)
{
    this->planet = planet;
}

Vector Satellite::getPos(double T)
{
    if (planet != NULL)
    {
        return setPos(planet->getPos(T) + State(T));
    }
    else 
    {
        return Vector();
    }
}
