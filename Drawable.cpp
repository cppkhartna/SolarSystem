#include "Drawable.h"

static GLfloat colors[12][3] =
{
    {1.0f,0.5f,0.5f},{1.0f,0.75f,0.5f},{1.0f,1.0f,0.5f},{0.75f,1.0f,0.5f},
    {0.5f,1.0f,0.5f},{0.5f,1.0f,0.75f},{0.5f,1.0f,1.0f},{0.5f,0.75f,1.0f},
    {0.5f,0.5f,1.0f},{0.75f,0.5f,1.0f},{1.0f,0.5f,1.0f},{1.0f,0.5f,0.75f}
};

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

    gluSphere(sphere,R,36,36);                // Draw A Sphere

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
    list  = glGenLists( 1 );
    glBindTexture( GL_TEXTURE_2D, texture);

    glNewList( list, GL_COMPILE );
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

    glEndList();
}

void Rings::DrawObject()
{
    glBindTexture(GL_TEXTURE_2D, texture); 
    glEnable(GL_TEXTURE_2D);

    glCallList(list);

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
    glEnable(GL_TEXTURE_2D);

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
    glDisable(GL_TEXTURE_2D);
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

    glDisable(GL_TEXTURE_2D);
    glEnable( GL_DEPTH_TEST );
    glDisable( GL_BLEND );
}

void Text::print(int x, int y, std::string _text, int W, int H)
{
    glMatrixMode( GL_PROJECTION );
    glPushMatrix( );
    glLoadIdentity( );
    glOrtho(0,W,0,H,-1,1);         
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix( );
    glLoadIdentity( );
    glTranslatef(x, y, 0);

    setText(_text);
    Draw();

    glMatrixMode( GL_PROJECTION );
    glPopMatrix();

    glMatrixMode( GL_MODELVIEW );
    glPopMatrix( );
}

Tail::Tail(GLuint texture)
{
    this->texture = texture;

    for (int i=0; i < MAX_PARTICLES; i++)
    {
        particles[i].active=true;
        particles[i].life=0.0f;
        particles[i].fade=float(rand()%100)/1000.0f+0.003f;
        particles[i].color=Vector(colors[(i+1)/(MAX_PARTICLES/12)][0], colors[(i+1)/(MAX_PARTICLES/12)][1], colors[(i+1)/(MAX_PARTICLES/12)][2]);
        particles[i].position = Vector();
        particles[i].direction=Vector(float((rand()%50)-26.0f)*10.0f, float((rand()%50)-25.0f)*10.0f, float((rand()%50)-25.0f)*10.0f);
        particles[i].gravity = Vector(0.0f, -0.8f, 0.0f);
    }

    list  = glGenLists( 1 );
    glBindTexture( GL_TEXTURE_2D, texture);
    glEnable(GL_TEXTURE_2D);

    glNewList( list, GL_COMPILE );

    glBegin(GL_QUADS);
        glTexCoord2d(1,1); glVertex2f(+0.5f,+0.5f);
        glTexCoord2d(0,1); glVertex2f(-0.5f,+0.5f);
        glTexCoord2d(0,0); glVertex2f(-0.5f,-0.5f);
        glTexCoord2d(1,0); glVertex2f(+0.5f,-0.5f);
    glEnd();

    glEndList();

    glDisable(GL_TEXTURE_2D);
}

void Tail::DrawObject()
{
    static int elapsed = 0;
    int Time=glutGet(GLUT_ELAPSED_TIME);

    std::cout << Time - elapsed << std::endl;
    if (Time - elapsed > 6)
       elapsed = Time;
    else
       return;

    static int col = 0;
    col++;
    col = col % 11;
    float slowdown=2.0f;
    velocity = Vector();

    glDisable( GL_DEPTH_TEST );
    glEnable(GL_BLEND);

    glBindTexture( GL_TEXTURE_2D, texture);
    glEnable(GL_TEXTURE_2D);

    glBlendFunc( GL_SRC_ALPHA, GL_ONE );

    for (int i=0; i < MAX_PARTICLES; i++)
    {
        if (particles[i].active)
        {
            float x=particles[i].position.X();
            float y=particles[i].position.Y();
            float z=particles[i].position.Z();

            glColor4f(particles[i].color.X(),particles[i].color.Y(),particles[i].color.Z(),particles[i].life);

            glTranslatef(x, y, z);
                glCallList(list);
            glTranslatef(-x, -y, -z);

            particles[i].position += particles[i].direction * (1/(slowdown*1000));
            particles[i].direction += particles[i].gravity;
            //particles[i].gravity = velocity;

            particles[i].life-=particles[i].fade;

            if (particles[i].life < 0.0f)
            {
                particles[i].life=1.0f;
                particles[i].fade=float(rand()%100)/1000.0f+0.003f;

                particles[i].position = Vector();
                particles[i].direction = Vector(float((rand()%60)-32.0f), float((rand()%60)-30.0f), float((rand()%60)-30.0f));
                //particles[i].gravity = velocity;

                particles[i].color = Vector(colors[col][0], colors[col][1], colors[col][2]);
            }
        }
    }
    glColor4f(1, 1, 1, 1);

    glEnable( GL_DEPTH_TEST );
    glDisable( GL_BLEND );
    glDisable(GL_TEXTURE_2D);

}
