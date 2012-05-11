#include "Comet.h"
void Comet::Kepler(double GM, double T0, double T, double q, double e)
{
  const double M0  = 0.1; // [rad]
  const double eps = 0.1;

  double M, delta, tau, invax;

  delta = fabs(1.0-e);

  invax = delta / q;

  tau   = sqrt(GM)*(T-T0);
  M     = tau * sqrt(invax*invax*invax);

  if ( (M < M0) && (delta < eps) )
    //Parab (GM, T0, T, q, e);
    {}
  else if ( e < 1.0 )
    Ellip (GM, M, 1.0/invax, e);
  //else
    //Hyperb (GM, T0, T, 1.0/invax, e);
}

void Comet::addTail(Tail *tail_new)
{
    tail = tail_new;
    add(tail);
}
