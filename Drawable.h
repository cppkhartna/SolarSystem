#include "Math.h"
#include "main.h"

class Drawable
{
public:
    Drawable (): axis(1, 1, 1), position(0, 0, 0), angle(0, 0, 0), scale(1, 1, 1), 
    w(0.02, 0.02, 0.02)
    {};
    virtual ~Drawable (){};
    void Draw();
    virtual void DrawObject(){};

private:
	Vector axis, position, angle, scale, w;
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
