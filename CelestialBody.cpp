#include "CelestialBody.h"
Matrix GaussVec(double Omega, double i, double omega)
{
  return R_z(-Omega) * R_x(-i) * R_z(-omega);
}

CelestialBody::CelestialBody (double a, double e, double M0, double n, double O, double i, double w): a(a), e(e), M0(M0), O(O), i(i), w(w), n(n) {};

Vector CelestialBody::State(double T)
{
  const double p = 1.3970;  

  double T0 = 0.0; // epoch J2000
  Matrix PQR;
  Vector r;

  r = Ellip(GM_Sun, Rad*(M0+n*(T-T0)), a, e); 
  PQR = GaussVec(Rad*(O+p*T), Rad*i, Rad*(w-O));
  r = PQR*r;                                       

  return r;
}

Vector CelestialBody::Ellip(double GM, double M, double a, double e)
{
  double k, E, cosE,sinE, fac, rho;

  k  = sqrt(GM/a);
  E  = EccAnom(M,e);   

  cosE = cos(E); 
  sinE = sin(E);

  fac = sqrt ( (1.0-e)*(1.0+e) );  

  rho = 1.0 - e*cosE;

  return Vector(a*(cosE-e), a*fac*sinE, 0.0);
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

void CelestialBody::Draw()
{
    std::list< Drawable* >::iterator it;
    for (it = seq.begin(); it != seq.end(); ++it)
    {
        (*it)->Draw();
    }
}

void CelestialBody::add(Drawable *object)
{
    seq.push_back(object);
}

void CelestialBody::nextFrame(double T)
{
    Vector pos = State(T);
    std::list< Drawable* >::iterator it;
    for (it = seq.begin(); it != seq.end(); ++it)
    {
        (*it)->setPos(pos);
    }
}
