#include <GLUT/glut.h>
#include <cmath>

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);   

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1100, 0, 800);  

    glMatrixMode(GL_MODELVIEW);
}

void display() {


//red
glColor3f(0.73f, 0.05f, 0.18f);
glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(0, 800);     
    glVertex2f(1100, 800);
    glVertex2f(1100,0);
glEnd();
    //white
glColor3f(1.0f, 1.0f, 1.0f);
glBegin(GL_QUADS);
    glVertex2f(0, 300);
    glVertex2f(0, 500);     
    glVertex2f(1100, 500);
    glVertex2f(1100,300);
glEnd();
glBegin(GL_QUADS);
    glVertex2f(300, 0);
    glVertex2f(300, 800);     
    glVertex2f(500, 800);
    glVertex2f(500,0);
glEnd();
//blue
glColor3f(0.0f, 0.13f, 0.36f);
glBegin(GL_QUADS);
    glVertex2f(0, 350);
    glVertex2f(0, 450);     
    glVertex2f(1100, 450);
    glVertex2f(1100,350);
glEnd();
glBegin(GL_QUADS);
    glVertex2f(350, 0);
    glVertex2f(350, 800);     
    glVertex2f(450, 800);
    glVertex2f(450,0);
glEnd();

glFlush();

}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(1100, 800);
    glutCreateWindow("Lab 5.1");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
