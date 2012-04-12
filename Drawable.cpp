#include "Drawable.h"

void Drawable::Draw()
{
	glPushMatrix();
	//glLoadIdentity();

    glTranslated(position.X(), position.Y(), position.Z());	

    angle += w;

	glRotated(angle.X(), axis.X(), 0, 0);
	glRotated(angle.Y(), 0, axis.Y(), 0);
	glRotated(angle.Z(), 0, 0, axis.Z());

	glScaled(scale.X(), scale.Y(), scale.Z());

    DrawObject();

	glPopMatrix();
}

void Body::DrawObject()
{
    glBindTexture(GL_TEXTURE_2D, texture); 
    glEnable(GL_TEXTURE_2D);

    gluSphere(sphere,R,32,32);                // Draw A Sphere

    glDisable(GL_TEXTURE_2D);
}

void Body::init(double R, GLuint texture)
{
    this->R = R;
    this->texture = texture;

    sphere=gluNewQuadric();   
    gluQuadricNormals(sphere, GLU_SMOOTH); 
    gluQuadricTexture(sphere, GL_TRUE);
}

