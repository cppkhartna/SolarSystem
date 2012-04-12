#include <iostream>
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

    double X();
    double Y();
    double Z();

private:
    /* data */
    double coords[3];
};

class Matrix
{
public:
    Matrix();
    Matrix(const Vector& e_1, const Vector& e_2, const Vector& e_3);
    virtual ~Matrix();
    

private:
    /* data */
    double Mat[3][3];  
};
