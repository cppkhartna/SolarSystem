#include "main.h"
#include <iostream>
#include <map>
#include <fstream> 
#include <stdexcept>

#ifdef assert
#undef assert
#define assert(exp, msg) if (!(exp)) throw std::runtime_error(msg);
#endif
using namespace std;

class Image
{
public:
    Image ();
    virtual ~Image ();
    void loadBMP(string filename);
    void setSize(int sizeX, int sizeY, int bits = 3);
    int X() const;
    int Y() const;
    unsigned char* Data() const;
    void addAlpha(const Image& src, const Image& alpha);

private:
    /* data */
    int sizeX;
    int sizeY;
    unsigned char *data;
}; 

typedef std::map<string, GLuint> GLStorage;

class TextureManager
{
public:
    TextureManager(){};
    virtual ~TextureManager ();
    GLuint getTexture(string filename);
    GLuint addNewTexture(string filename);
    GLuint loadTexture(string filename);

private:
    GLStorage textures;
};
