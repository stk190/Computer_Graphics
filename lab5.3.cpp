#include <GLUT/glut.h>
#include <cmath>

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);   

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 900, 0, 600);  

    glMatrixMode(GL_MODELVIEW);
}

void display() {

//red
glColor3f(0.88f, 0.24f, 0.19f);
glBegin(GL_QUADS);
    glVertex2f(0, 300);
    glVertex2f(0, 600);     
    glVertex2f(900, 600);
    glVertex2f(900,300);    
glEnd();
//blue
glColor3f(0.0f, 0.08f, 0.54f);
glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(0, 300);     
    glVertex2f(900, 300);
    glVertex2f(900,0);
glEnd();

//white
glColor3f(1.0f, 1.0f, 1.0f);
glBegin(GL_QUADS);
    glVertex2f(0, 200);
    glVertex2f(0, 400);     
    glVertex2f(900, 400);
    glVertex2f(900,200);
glEnd();



//green(triangle)
glColor3f(0.0f, 0.48f, 0.30f);
glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(0, 600);     
    glVertex2f(150, 600);
    glVertex2f(150,0);
glEnd();
glBegin(GL_QUADS);
    glVertex2f(150, 0);
    glVertex2f(150, 600);     
    glVertex2f(450, 350);
    glVertex2f(450,250);
glEnd();
//white(triangle)
glColor3f(1.0f, 1.0f, 1.0f);
glBegin(GL_QUADS);
    glVertex2f(210, 0);
    glVertex2f(150, 0);     
    glVertex2f(450, 250);
    glVertex2f(450, 200);
glEnd();
glBegin(GL_QUADS);
    glVertex2f(150, 600);
    glVertex2f(210, 600);     
    glVertex2f(450, 400);
    glVertex2f(450, 350);
glEnd();
//green
glColor3f(0.0f, 0.48f, 0.30f);
glBegin(GL_QUADS);
    glVertex2f(0, 230);
    glVertex2f(0, 370);     
    glVertex2f(900, 370);
    glVertex2f(900,230);
glEnd();
//ylw
glColor3f(1.0f, 0.71f, 0.07f);
glBegin(GL_TRIANGLES);
    glVertex2f(0,40); 
    glVertex2f(0, 560);
    glVertex2f(300,300);
glEnd();

//black
glColor3f(0.0f, 0.0f, 0.0f);
glBegin(GL_TRIANGLES);
    glVertex2f(0,90); 
    glVertex2f(0, 510);
    glVertex2f(250,300);
    glEnd();
glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(900, 600);
    glutCreateWindow("Lab 5.1");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
