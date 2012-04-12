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

//int main(int argc, char const *argv[])
//{
    //Vector a(1, 2, 3);
    //Vector b(2, 3, 4);
    //std::cout << a+b;
    //a -= b;
    //std::cout << a-b;
    //return 0;
//}
