#include <GLUT/glut.h>
#include <cmath>

void display() {
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(-250,250,-250,250);
    //quad
    glBegin(GL_LINES);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(-250,0);
    glVertex2f(250,0);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(0,-250);
    glVertex2f(0,250);
    glEnd();


    //traingle
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(-130,220);
        glVertex2f(-220,30);
        glVertex2f(-30,30);
    glEnd();

    //hex
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glColor3f(0.3f, 0.5f, 0.1f);
    glVertex2f(30, 130);
    glVertex2f(90,220);
    glVertex2f(170, 220);
    glVertex2f(220, 130);
    glVertex2f(170, 30);
    glVertex2f(90,30);
    glEnd();

    //square

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_QUADS);
        glVertex2f(-30, -30);
        glVertex2f(-220, -30);
        glVertex2f(-220, -220);
        glVertex2f(-30, -220);
    glEnd();

    // triangle 2
    glColor3f(1.0, 0.5, 0.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(130,-30);
        glVertex2f(90,-220);
        glVertex2f(170,-220);
    glEnd();
    

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Lab 1");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
