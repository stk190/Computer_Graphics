#include <GLUT/glut.h>
#include <cmath>

void display() {
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(0,700,0,700);

    // Red
glColor3f(1.0f, 0.0f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(0, 600);
glVertex2f(0, 700);
glVertex2f(700, 700);
glVertex2f(700, 600);
glEnd();

// Orange
glColor3f(1.0f, 0.5f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(0, 500);
glVertex2f(0, 600);
glVertex2f(700, 600);
glVertex2f(700, 500);
glEnd();

// Yellow
glColor3f(1.0f, 1.0f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(0, 400);
glVertex2f(0, 500);
glVertex2f(700, 500);
glVertex2f(700, 400);
glEnd();

// Green
glColor3f(0.0f, 1.0f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(0, 300);
glVertex2f(0, 400);
glVertex2f(700, 400);
glVertex2f(700, 300);
glEnd();

// Blue
glColor3f(0.0f, 0.0f, 1.0f);
glBegin(GL_QUADS);
glVertex2f(0, 200);
glVertex2f(0, 300);
glVertex2f(700, 300);
glVertex2f(700, 200);
glEnd();

// Indigo
glColor3f(0.29f, 0.0f, 0.51f);
glBegin(GL_QUADS);
glVertex2f(0, 100);
glVertex2f(0, 200);
glVertex2f(700, 200);
glVertex2f(700, 100);
glEnd();

// Violet
glColor3f(0.56f, 0.0f, 1.0f);
glBegin(GL_QUADS);
glVertex2f(0, 0);
glVertex2f(0, 100);
glVertex2f(700, 100);
glVertex2f(700, 0);
glEnd();

glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Lab 2");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
