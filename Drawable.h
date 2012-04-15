#include "Math.h"
#include "main.h"

class Drawable
{
public:
    Drawable (): axis(1, 1, 1), position(0, 0, 0), incl(45, 45, 0), scale(1, 1, 1), 
    w(0.2), angle(0)
    {};
    virtual ~Drawable (){};
    void Draw();
    void setPos(Vector pos);
    virtual void DrawObject(){};

private:
	Vector axis, position, incl, scale;
    double angle, w;
};

class Body: public Drawable
{
public:
    Body (){};
    void init (double R, GLuint texture);
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
    Rings (){};
    void init (double R1, double R2, GLuint texture);
    virtual ~Rings (){};
    void DrawObject();

private:
    /* data */
    double R1, R2;
    GLuint texture;
};
