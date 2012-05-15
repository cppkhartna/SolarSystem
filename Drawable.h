#include "Math.h"
#include "main.h"
#define MAX_PARTICLES   1000

class Drawable
{
public:
    Drawable (): axis(1, 1, 1), position(0, 0, 0), incl(0, 0, 0), scale(1), angle(0.0f), w(0) {};
    virtual ~Drawable (){};
    void Draw();
    virtual void DrawObject(){};
    void setPos(Vector pos);
    void setScale(double scale);
    void setIncl(Vector incl);

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
    GLuint list;
};

class Text: public Drawable
{
public:
    Text(GLuint texture);
    virtual ~Text ();
    void DrawObject();
    void setText(std::string new_text);
    void print(int x, int y, std::string _text, int W, int H);
    void setWScale(double WScale);
private:
    /* data */
    std::string text;
    GLuint texture;
    GLuint list;
    double WScale;
};

typedef struct
{
    bool active;
    float life;
    float fade;
    Vector color, position, direction, gravity;
}
particle;

class Tail: public Drawable
{
public:
    Tail(GLuint texture);
    virtual ~Tail (){};
    void DrawObject();
    void setVel(Vector v){};
private:
    /* data */
    particle particles[MAX_PARTICLES];
    Vector velocity;
    GLuint texture;
    GLuint list;
};
