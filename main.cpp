#include "SolarSystem.h"
#include "main.h"

GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[] = { 0.0f, 0.0f, 0.0f, 1.0f };

SolarSystem ss;

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

    ss.readXML("SolarSystem.xml");

}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
    glLoadIdentity();		

    glTranslatef(0.0f,0.0f,-100.0f); 
    
    //glRotatef(xrot,1.0f,0.0f,0.0f);
    //glRotatef(yrot,0.0f,1.0f,0.0f);

    ss.nextFrame();
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
    //std::cout << "Йоба" << std::endl;

    glutMainLoop();  

    return 0;
}
