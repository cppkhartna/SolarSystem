#include "TextureManager.h"
Image::Image () {};

Image::~Image ()
{
    if (data != NULL)
        delete[] data;
};

void Image::setSize(int sizeX, int sizeY, int bits)
{
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    unsigned long size = sizeX*sizeY*bits;
    data = new unsigned char[size];
    for (unsigned long i = 0; i < size; ++i)
    {
        data[i] = (unsigned char) 255;
    }
};

int Image::X() const
{
    return sizeX;
}

int Image::Y() const
{
    return sizeY;
}

unsigned char* Image::Data() const
{
    return data;
}

void Image::addAlpha(const Image& src, const Image& alpha)
{
    assert((src.sizeX == alpha.sizeX) && (src.sizeY == alpha.sizeY), "Wrong dimensions");
    setSize(src.sizeX, src.sizeY, 4);

    for (int j = 0; j < sizeX*sizeY; j++) 
    {
        data[4*j] = src.data[3*j];
        data[4*j + 1] = src.data[3*j + 1];
        data[4*j + 2] = src.data[3*j + 2];
        data[4*j + 3] = (unsigned char)(((int)alpha.data[3*j] + (int)alpha.data[3*j + 1] + (int)alpha.data[3*j + 2])/3);
        //std::cout << (int)data[4*j + 1] << std::endl;
    }
}

void Image::loadBMP(string filename) 
{
    unsigned long size;                 // size of the image in bytes.
    unsigned long i;                    // standard counter.
    unsigned short int planes;          // number of planes in image (must be 1) 
    unsigned short int bpp;             // number of bits per pixel (must be 24)
    char temp;                          // used to convert bgr to rgb color.

    ifstream file;      
    file.open(filename.c_str(), ios::in | ios::binary);
    assert(!file.fail(), "Can't open file");

	file.seekg(18, std::ios_base::beg); // skip to bmp header
    file.read(reinterpret_cast < char * > (&sizeX), 4);
    file.read(reinterpret_cast < char * > (&sizeY), 4);

	size = sizeX * sizeY * 3; // calculate the size (assuming 24 bpp)

    file.read((char*)&planes, 2); // read the planes
    assert(planes == 1, "planes != 1");

    file.read((char*)&bpp, 2); // read the bpp
    assert(bpp == 24, "bpp != 24");

	file.seekg(24, std::ios_base::cur); // seek past the rest of the bitmap header

    data = new unsigned char[size];
    assert(data != NULL, "Can't allocate memory for data");

    file.read(reinterpret_cast < char * > (data), size); //read the data

	// reverse all of the colours bgr => rgb)
	for (i = 0; i < size; i += 3) 
    {
		temp = data[i];
		data[i] = data[i+2];
		data[i+2] = temp;
	}

	file.close();
}

GLuint TextureManager::getTexture(string filename)
{
    GLStorage::iterator it;
    it = textures.find(filename);
    if (it == textures.end())
    {
        //std::cout << "Йо" << std::endl;
        return addNewTexture(filename); 
    }
    else
    {
        //std::cout << "ба" << std::endl;
        return it->second;
    }
};

GLuint TextureManager::addNewTexture(string filename)
{
    GLuint texture;
    try
    {
        texture = loadTexture(filename);
    }
    catch (exception& e)
    {
        cerr << filename << ": " << e.what() << std::endl;
        texture = (GLuint) 0;
    }

    textures[filename] = texture;
    return texture;
}

GLuint TextureManager::loadTexture(string filename) 
{
    Image source;
    source.loadBMP(filename);


    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);  
    glEnable(GL_TEXTURE_2D);

    // check if there is alpha channel bmp
    int pos = filename.find(".");
    filename.replace(pos, 20, "_alpha.bmp");

    Image alpha;
    try
    {
        alpha.loadBMP(filename);
    }
    catch (exception& e)
    {
        alpha.setSize(source.X(), source.Y());
    }

    Image image;
    image.addAlpha(source, alpha);

	// create texture (mipmapped scaling)
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.X(), image.Y(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.Data());
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image.X(), image.Y(), GL_RGBA, GL_UNSIGNED_BYTE, image.Data()); 

    return texture;
}

TextureManager::~TextureManager()
{
    GLStorage::iterator it;
    for (it = textures.begin(); it != textures.end(); it++)
    {
        glDeleteTextures(1, &it->second);
    }
    textures.clear();
}
