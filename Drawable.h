#include "Math.h"
#include "main.h"

class Drawable
{
public:
    Drawable (): axis(1, 1, 1), position(0, 0, 0), incl(0, 0, 0), scale(1), angle(0.0f), w(0) {};
    virtual ~Drawable (){};
    void Draw();
    virtual void DrawObject(){};
    void setPos(Vector pos);
    void setScale(double scale);

private:
    /* data */
	Vector axis, position, incl;
    double scale, angle, w;
};

class Body: public Drawable
{
public:
    Body (double R, GLuint texture);
    virtual ~Body (){};
    void DrawObject();

private:
    /* data */
    GLUquadricObj *sphere;
    double R;
    GLuint texture;
};

class Rings: public Drawable
{
public:
    Rings (double R1, double R2, GLuint texture);
    virtual ~Rings (){};
    void DrawObject();

private:
    /* data */
    double R1, R2;
    GLuint texture;
};
