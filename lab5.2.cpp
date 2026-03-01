#include <GLUT/glut.h>
#include <cmath>

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);   

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 600, 0, 300);  

    glMatrixMode(GL_MODELVIEW);
}

void display() {



//black
glColor3f(0.0f, 0.0f, 0.0f);
glBegin(GL_QUADS);
    glVertex2f(0, 200);
    glVertex2f(0, 300);     
    glVertex2f(600, 300);
    glVertex2f(600,200);
glEnd();
//white
glColor3f(1.0f, 1.0f, 1.0f);
glBegin(GL_QUADS);
    glVertex2f(0, 100);
    glVertex2f(0, 200);     
    glVertex2f(600, 200);
    glVertex2f(600,100);
glEnd();
//green
glColor3f(0.0f, 0.48f, 0.24f);
glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(0, 100);     
    glVertex2f(600, 100);
    glVertex2f(600,0);
glEnd();

//red
glColor3f(0.81f, 0.07f, 0.15f);
glBegin(GL_TRIANGLES);
    glVertex2f(0, 0);
    glVertex2f(0, 300);
    glVertex2f(200, 150);     
glEnd();
glFlush();

}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 300);
    glutCreateWindow("Lab 5.1");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
