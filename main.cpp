#include "CelestialBody.h"
#include "TextureManager.h"
#include "main.h"

GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[] = { 0.0f, 0.0f, 2.0f, 1.0f };

GLUquadricObj *quadratic;	
TextureManager tm = TextureManager();
CelestialBody sun(0, 0.055723, 320.3477, 1213.8664, 113.6427, 2.4852, 89.6567);
CelestialBody saturn( 9.582018, 0.055723, 320.3477, 1213.8664, 113.6427, 2.4852, 89.6567);
CelestialBody uranus(19.229412, 0.044406, 142.9559, 426.9282, 73.9893, 0.7726, 170.5310);
Body body;
Rings rings;
Body body2;
Rings rings2;
Body body3;
double T = 0;

void init(int width, int height)
{
	glEnable(GL_TEXTURE_2D);		

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  	glClearDepth(1.0);			
  	glDepthFunc(GL_LESS);	
  	glEnable(GL_DEPTH_TEST);
  	glShadeModel(GL_SMOOTH);

  	glMatrixMode(GL_PROJECTION);
  	glLoadIdentity();	

  	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

  	glMatrixMode(GL_MODELVIEW);
  
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);  	// add lighting. (ambient)
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);  	// add lighting. (diffuse).
    glLightfv(GL_LIGHT1, GL_POSITION,LightPosition); 	// set light position.
    glEnable(GL_LIGHT1);                             	// turn light 1 on.

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    body.init(1.2f, tm.getTexture("Textures/Planets/saturn.bmp"));
    rings.init(1.4f, 2.8f, tm.getTexture("Textures/Planets/saturn-rings.bmp"));
    saturn.add(&body);
    saturn.add(&rings);
    body2.init(1.0f, tm.getTexture("Textures/Planets/uranus.bmp"));
    rings2.init(1.2f, 4.0f, tm.getTexture("Textures/Planets/uranus-rings.bmp"));
    uranus.add(&body2);
    uranus.add(&rings2);
    body3.init(3.0f, tm.getTexture("Textures/Planets/sun.bmp"));
    sun.add(&body3);
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
    glLoadIdentity();		

    glTranslatef(0.0f,0.0f,-50.0f); 
    
    //glRotatef(xrot,1.0f,0.0f,0.0f);
    //glRotatef(yrot,0.0f,1.0f,0.0f);

    T+=1.0f/600.0f;
    saturn.nextFrame(T);
    saturn.Draw();
    uranus.nextFrame(T);
    uranus.Draw();
    sun.Draw();
	glFlush();
    glutSwapBuffers();
}
void idle()
{
    display();
}
void reshape(int width, int height)
{
    if (height == 0)	
        height=1;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}
void keyPressed(unsigned char key, int x, int y) 
{
}
void specialKeyPressed(int key, int x, int y) 
{
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA);  
    glutInitWindowSize(640, 480);  
    glutInitWindowPosition(0, 0);  
    glutCreateWindow("SolarSystem");  
    glutDisplayFunc(display);  
    glutFullScreen();
    glutIdleFunc(&idle); 
    glutReshapeFunc(&reshape);
    glutKeyboardFunc(&keyPressed);
    glutSpecialFunc(&specialKeyPressed);
    init(640, 480);
    std::cout << "Йоба!" << std::endl;

    glutMainLoop();  

    return 0;
}
