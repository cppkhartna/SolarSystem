#include "Drawable.h"

void Drawable::Draw()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glPushMatrix();

    glTranslated(position.X(), position.Y(), position.Z());	

    //angle += w; //TODO: independent realisation

    glRotated(incl.X(), axis.X(), 0, 0);
    glRotated(incl.Y(), 0, axis.Y(), 0);
    glRotated(incl.Z(), 0, 0, axis.Z());

    glRotated(angle, 0, 0, 1); // rotate around self-z
    glRotated(angle, 0, 1, 1); // rotate around self-z
    glRotated(angle, 1, 0, 1); // rotate around self-z

    glScaled(scale, scale, scale);

    DrawObject();

    glPopMatrix();

    glDisable(GL_BLEND);
}

void Body::DrawObject()
{
    glBindTexture(GL_TEXTURE_2D, texture); 
    glEnable(GL_TEXTURE_2D);

    gluSphere(sphere,R,360,360);                // Draw A Sphere

    glDisable(GL_TEXTURE_2D);
}

Body::Body(double R, GLuint texture)
{
    this->R = R;
    this->texture = texture;

    sphere=gluNewQuadric();   
    gluQuadricNormals(sphere, GLU_SMOOTH); 
    gluQuadricTexture(sphere, GL_TRUE);
}

Rings::Rings(double R1, double R2, GLuint texture)
{
    this->R1 = R1;
    this->R2 = R2;
    this->texture = texture;
}

void Rings::DrawObject()
{
    glBindTexture(GL_TEXTURE_2D, texture); 
    glEnable(GL_TEXTURE_2D);
    int n = 360;

    glBegin(GL_QUADS);
    for (int i = 0; i < n; ++i)
    {
        double phi1 = 2*M_PI*(double)i/(double)n;
        double phi2 = 2*M_PI*(i+1)/n;

        glTexCoord2f(0.0f, 1.0f);
        glVertex3d(R1*cos(phi1), R1*sin(phi1), 0);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3d(R2*cos(phi1), R2*sin(phi1), 0);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3d(R2*cos(phi2), R2*sin(phi2), 0);
        glTexCoord2f(0.0f, 0.0f); 
        glVertex3d(R1*cos(phi2), R1*sin(phi2), 0);
    }
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void Drawable::setPos(Vector pos)
{
    position = pos;
};

void Drawable::setScale(double scale)
{
    this->scale = scale;
}

Text::Text(GLuint texture)
{
    this->texture = texture;

    //NegeGL
    float cx;   
    float cy;   

    list  = glGenLists( 256 );
    glBindTexture( GL_TEXTURE_2D, texture);

    for (GLuint i = 0; i < 256; i++)
    {
        cx = 1 - ( float )( i % 16 ) / 16.0f;
        cy = 1 - ( float )( i / 16 ) / 16.0f;

        glNewList( list + ( 255 - i ), GL_COMPILE );
        glBegin( GL_QUADS );
            glTexCoord2f( cx - 0.0625, cy );
            glVertex2i( 0, 0 );

            glTexCoord2f( cx, cy );
            glVertex2i( 16, 0 );

            glTexCoord2f( cx, cy - 0.0625f );
            glVertex2i( 16, 16 );

            glTexCoord2f( cx - 0.0625f, cy - 0.0625f);
            glVertex2i( 0, 16 );
        glEnd();

        glTranslated( 10, 0, 0 );
        glEndList();
    }
}

void Text::setText(std::string new_text)
{
    text = new_text;
}

Text::~Text()
{
    glDeleteLists(list, 256);
}

void Text::DrawObject()
{
    glDisable( GL_DEPTH_TEST );
    glEnable(GL_BLEND);

    glBindTexture( GL_TEXTURE_2D, texture);
    glEnable(GL_TEXTURE_2D);

    glBlendFunc( GL_SRC_ALPHA, GL_ONE );
    glListBase(list - 32 + ( 128 * 0 ));

    glCallLists(text.length(), GL_BYTE, text.c_str());

    glEnable( GL_DEPTH_TEST );
    glDisable( GL_BLEND );
}
