#include <iostream>
#include <cmath>

#include <cfloat>
const double eps_mach = DBL_EPSILON;

class Matrix;
class Vector
{
public:
    //constructors
    Vector ();
    Vector (double x, double y, double z);
    Vector (const Vector& vec);
    Vector (const double *arr);
    //destructor
    virtual ~Vector (){};

    //operators
    Vector operator+(const Vector& vec);
    Vector operator-(const Vector& vec);
    Vector operator=(const Vector& vec);
    Vector operator+=(const Vector& vec);
    Vector operator-=(const Vector& vec);
    friend Vector operator*(double scalar, const Vector& vec);
    friend Vector operator*(const Vector& vec, double scalar);
    operator double*();
    friend std::ostream& operator << (std::ostream& os, const Vector& vec);

    friend Vector operator*(const Matrix& Mat, const Vector& Vec);
    friend Vector operator*(const Vector& Vec, const Matrix& Mat);

    double X();
    double Y();
    double Z();

    double norm();

    friend class Matrix;

private:
    /* data */
    double coords[3];
};

class Matrix
{
public:
    Matrix();
    Matrix(const Vector& e_1, const Vector& e_2, const Vector& e_3);
    ~Matrix(){};
    friend Matrix id();

    friend Matrix R_x(double RotAngle);
    friend Matrix R_y(double RotAngle);
    friend Matrix R_z(double RotAngle);
    friend Matrix Transp(const Matrix& Mat);

    friend Matrix operator*(double fScalar, const Matrix& Mat);
    friend Matrix operator*(const Matrix& Mat, double fScalar);
    friend Matrix operator/(const Matrix& Mat, double fScalar);
    friend Vector operator*(const Matrix& Mat, const Vector& Vec);
    friend Vector operator*(const Vector& Vec, const Matrix& Mat);
    friend Matrix operator-(const Matrix& Mat);
    friend Matrix operator+(const Matrix& left, const Matrix& right);
    friend Matrix operator-(const Matrix& left, const Matrix& right);    
    friend Matrix operator*(const Matrix& left, const Matrix& right);
    friend std::ostream& operator << (std::ostream& os, const Matrix& Mat);

private:
    /* data */
    double m_Mat[3][3];  
};

Matrix R_x(double RotAngle);
Matrix R_y(double RotAngle);
Matrix R_z(double RotAngle);
double Frac (double x);
double Modulo (double x, double y);
Matrix GaussVec(double Omega, double i, double omega);
