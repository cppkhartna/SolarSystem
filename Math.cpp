#include "Math.h"
using namespace std;

Vector::Vector()
{
    for (int i = 0; i < 3; i++)
        coords[i] = 0;
};

Vector::Vector(const double *arr)
{
    for (int i = 0; i < 3; i++)
        coords[i] = arr[i];
}
Vector::Vector(double x, double y, double z)
{
    coords[0] = x;
    coords[1] = y;
    coords[2] = z;
};

Vector::Vector (const Vector& vec)
{
    for (int i = 0; i < 3; i++)
        coords[i] = vec.coords[i];
};

Vector Vector::operator+(const Vector& vec)
{
    double aux[3];
    for (int i = 0; i < 3; i++)
        aux[i] = coords[i] + vec.coords[i];
    return Vector(aux);
}

Vector Vector::operator-(const Vector& vec)
{
    double aux[3];
    for (int i = 0; i < 3; i++)
        aux[i] = coords[i] - vec.coords[i];
    return Vector(aux);
}

Vector Vector::operator=(const Vector& vec)
{
    for (int i = 0; i < 3; i++)
        coords[i] = vec.coords[i];
    return *this;
}

Vector Vector::operator+=(const Vector& vec)
{
    for (int i = 0; i < 3; i++)
        coords[i] += vec.coords[i];
    return *this;
}

Vector Vector::operator-=(const Vector& vec)
{
    for (int i = 0; i < 3; i++)
        coords[i] -= vec.coords[i];
    return *this;
}

ostream& operator << (ostream& os, const Vector& vec)
{
    os << " (";
    for (int i = 0; i < 3; i++)
    {
        os << vec.coords[i];
        if (i != 2)
        {
            os << ',';
        }
    }
    os << ")" << endl;
    return os;
};

Vector operator*(double scalar, const Vector& vec)
{
    double aux[3];
    for (int i = 0; i < 3; i++)
        aux[i] = vec.coords[i] * scalar;
    return Vector(aux);
};

Vector operator*(const Vector& vec, double scalar)
{
    return scalar*vec;
};

Vector::operator double*() 
{
    return coords;
};

double Vector::X() 
{
    return coords[0];
};

double Vector::Y() 
{
    return coords[1];
};

double Vector::Z() 
{
    return coords[2];
};

Matrix::Matrix ()
{
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      m_Mat[i][j] = 0.0;
}

Matrix::Matrix (const Vector& e_1, const Vector& e_2, const Vector& e_3 )
{
  for (int i = 0; i < 3; i++) {
    m_Mat[i][0]=e_1.coords[i];
    m_Mat[i][1]=e_2.coords[i];
    m_Mat[i][2]=e_3.coords[i];
  }
}

Matrix id()
{
  Matrix Id;

  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      Id.m_Mat[i][j] = (i==j) ? 1 : 0;
   
  return Id;
}

Matrix R_x(double RotAngle)
{
  const double S = sin (RotAngle);
  const double C = cos (RotAngle);

  Matrix U;
  
  U.m_Mat[0][0] = 1.0;  U.m_Mat[0][1] = 0.0;  U.m_Mat[0][2] = 0.0;
  U.m_Mat[1][0] = 0.0;  U.m_Mat[1][1] =  +C;  U.m_Mat[1][2] =  +S;
  U.m_Mat[2][0] = 0.0;  U.m_Mat[2][1] =  -S;  U.m_Mat[2][2] =  +C;

  return U;
}

Matrix R_y(double RotAngle)
{
  const double S = sin (RotAngle);
  const double C = cos (RotAngle);

  Matrix U;
  
  U.m_Mat[0][0] =  +C;  U.m_Mat[0][1] = 0.0;  U.m_Mat[0][2] =  -S;
  U.m_Mat[1][0] = 0.0;  U.m_Mat[1][1] = 1.0;  U.m_Mat[1][2] = 0.0;
  U.m_Mat[2][0] =  +S;  U.m_Mat[2][1] = 0.0;  U.m_Mat[2][2] =  +C;

  return U;
}

Matrix R_z(double RotAngle)
{
  const double S = sin (RotAngle);
  const double C = cos (RotAngle);

  Matrix U;

  U.m_Mat[0][0] =  +C;  U.m_Mat[0][1] =  +S;  U.m_Mat[0][2] = 0.0;
  U.m_Mat[1][0] =  -S;  U.m_Mat[1][1] =  +C;  U.m_Mat[1][2] = 0.0;
  U.m_Mat[2][0] = 0.0;  U.m_Mat[2][1] = 0.0;  U.m_Mat[2][2] = 1.0;

  return U;
}

Matrix Transp(const Matrix& Mat)
{
  Matrix T;

  for ( int i = 0; i < 3; i++ )
    for ( int j = 0; j < 3; j++ )
      T.m_Mat[i][j] = Mat.m_Mat[j][i];
    
  return T;
}


Matrix operator*(double fScalar, const Matrix& Mat)
{
  Matrix Result;

  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      Result.m_Mat[i][j] = fScalar*Mat.m_Mat[i][j];

  return Result;
}

Matrix operator*(const Matrix& Mat, double fScalar)
{
  return fScalar * Mat;
}

Matrix operator/(const Matrix& Mat, double fScalar)
{
  Matrix Result;

  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      Result.m_Mat[i][j] = Mat.m_Mat[i][j]/fScalar;
  
  return Result;
}

Vector operator*(const Matrix& Mat, const Vector& Vec)
{
  Vector Result;

  for (int i = 0; i < 3; i++) {
    double Scalp = 0.0;
    for (int j = 0; j < 3; j++)
      Scalp += Mat.m_Mat[i][j] * Vec.coords[j];
    Result.coords[i] = Scalp;
  }

  return Result;
}

Vector operator*(const Vector& Vec, const Matrix& Mat)
{
  Vector Result;

  for (int j = 0; j < 3; j++) {
    double Scalp = 0.0;
    for (int i = 0; i < 3; i++)
      Scalp += Vec.coords[i] * Mat.m_Mat[i][j] ;
    Result.coords[j] = Scalp;
  }

  return Result;
}

Matrix operator-(const Matrix& Mat)
{
  Matrix Result;

  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      Result.m_Mat[i][j] = -Mat.m_Mat[i][j];

  return Result;
}

Matrix operator+(const Matrix& left, const Matrix& right)
{
  Matrix Result;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      Result.m_Mat[i][j] = left.m_Mat[i][j] + right.m_Mat[i][j];
    }
  }
    
  return Result;
}

Matrix operator-(const Matrix& left, const Matrix& right)
{
  Matrix Result;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      Result.m_Mat[i][j] = left.m_Mat[i][j] - right.m_Mat[i][j];
    }
  }
    
  return Result;
}

Matrix operator*(const Matrix& left, const Matrix& right)
{
  Matrix Result;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      double Scalp = 0.0;
      for (int k = 0; k < 3; k++)
        Scalp += left.m_Mat[i][k] * right.m_Mat[k][j];
      Result.m_Mat[i][j] = Scalp;
    }
  }
    
  return Result;
}

ostream& operator << (ostream& os, const Matrix& Mat)
{
  int w = os.width();

  for (int i=0; i<3; i++) {
    os << " (";
    os << Mat.m_Mat[i][0] << ",";
    os << Mat.m_Mat[i][1] << ",";
    os << Mat.m_Mat[i][2];
    os << ")" << endl;
  }

  return os;
}

double Frac (double x)
{
   return x-floor(x);
}

double Modulo (double x, double y)
{
   return y*Frac(x/y);
}
