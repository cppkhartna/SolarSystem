#include "SolarSystem.h"
#include "main.h"

GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[] = { 0.0f, 0.0f, 0.0f, 1.0f };

SolarSystem ss;

int mouse_x = 0, mouse_y = 0, mouse_button = -1, mouse_state = GLUT_UP;

double x_angle = 0; // Угол поворота объектов
double y_angle = 0;

double xpos = 100.0f, ypos, xrot, yrot, xspeed, yspeed;
double scale = 3.125f;
double zFar = 10000;
#define ENTER 13
#define ESCAPE 27
#define SPACEBAR 32
bool move = true;
bool step = true;

void init(int width, int height)
{
    glEnable(GL_TEXTURE_2D);		

    glClearColor(0.00f, 0.00f, 0.1f, 0.0f);
    glClearDepth(1.0);			
    glDepthFunc(GL_LESS);	
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();	

    gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f, zFar);
    glTranslatef(0.0f,0.0f, -zFar/2.0f); //center of our shiny little universe

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

    glMatrixMode(GL_MODELVIEW);

    glRotatef(360.0f-yrot, 0.0f, 1.0f, 0.0f);

    glRotated(x_angle,1,0,0);
    glRotated(y_angle,0,0,1);

    glTranslatef(0.0f,0.0f,-xpos);
    glScalef(scale, scale, scale);

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

    gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, zFar);
    glMatrixMode(GL_MODELVIEW);
}

void keyPressed(unsigned char key, int x, int y) 
{
    usleep(100);

    switch (key) 
    {    
        case ESCAPE: 
            glutDestroyWindow(glutGetWindow());
            exit(1);
            break;
        case SPACEBAR: 
            ss.step();
            break;
        case ENTER: 
            ss.move();
            break;
        case '-': 
            scale /= 2;
            std::cout << scale << std::endl;
            break;
        case '+': case '=': 
            scale *= 2;
            std::cout << scale << std::endl;
            break;
        case '(': 
            ss.slowDown();
            break;
        case ')': 
            ss.speedUp();
            break;
    }
}

void specialKeyPressed(int key, int x, int y) 
{
    usleep(100);

    switch (key) 
    {    
        case GLUT_KEY_UP: 
            xpos -= 0.5f;
            break;

        case GLUT_KEY_DOWN: 
            xpos += 0.5f;
            break;

        case GLUT_KEY_LEFT:
            yrot += 1.5f;
            break;

        case GLUT_KEY_RIGHT:
            yrot -= 1.5f;
            break;

        default:
            //printf ("Special key %d pressed. No action there yet.\n", key);
            break;
    }	
}

void mouseClick(int button,int state,int x,int y)
{
    mouse_button = button;
    mouse_state = state;
    mouse_x = x;
    mouse_y = y;
}

void mouseMotion(int x,int y)
{
    int dx = x - mouse_x;
    int dy = y - mouse_y;
    if(mouse_state == GLUT_DOWN)
    {
        if(mouse_button == GLUT_LEFT_BUTTON)
        {
            y_angle += dx/3;
            if(y_angle < 0)
                y_angle += 360;
            if(y_angle >= 360)
                y_angle -= 360;
            x_angle += dy/3;
            if(x_angle < 5)
                x_angle = 10;
            if(x_angle > 90)
                x_angle = 90;
            //display();
        }
    }
    mouse_x = x;
    mouse_y = y;
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA);  
    glutInitWindowSize(640, 480);  
    glutInitWindowPosition(0, 0);  
    glutCreateWindow("SolarSystem");  
    glutMouseFunc(mouseClick);
    glutMotionFunc(mouseMotion);
    glutDisplayFunc(display);  
    glutFullScreen();
    glutIdleFunc(&idle); 
    glutReshapeFunc(&reshape);
    glutKeyboardFunc(&keyPressed);
    glutSpecialFunc(&specialKeyPressed);
    init(640, 480);

    std::cout << "Йоба" << std::endl;

    glutMainLoop();  

    return 0;
}
