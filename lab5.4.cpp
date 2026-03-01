#include <GLUT/glut.h>
#include <cmath>

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);   

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 809, 0, 500);  

    glMatrixMode(GL_MODELVIEW);
}

void display() {

    glClear(GL_COLOR_BUFFER_BIT);

  
    glColor3f(0.0f, 0.42f, 0.31f);

    // Bottom green
    glBegin(GL_QUADS);
        glVertex2f(0,0);
        glVertex2f(809,0);
        glVertex2f(809,100);
        glVertex2f(0,100);
    glEnd();

    //green
    glBegin(GL_QUADS);
        glVertex2f(0,200);
        glVertex2f(809,200);
        glVertex2f(809,300);
        glVertex2f(0,300);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(0,400);
        glVertex2f(809,400);
        glVertex2f(809,500);
        glVertex2f(0,500);
    glEnd();


  
    glColor3f(1.0f, 0.81f, 0.0f);

    glBegin(GL_QUADS);
        glVertex2f(0,100);
        glVertex2f(809,100);
        glVertex2f(809,200);
        glVertex2f(0,200);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0,300);
        glVertex2f(809,300);
        glVertex2f(809,400);
        glVertex2f(0,400);
    glEnd();


    glColor3f(0.82f, 0.06f, 0.20f);

    glBegin(GL_QUADS);
        glVertex2f(0,200);
        glVertex2f(300,200);
        glVertex2f(300,500);
        glVertex2f(0,500);
    glEnd();


  /*/  //white star
    glColor3f(1.0f,1.0f,1.0f);

glBegin(GL_QUADS);
    glVertex2f(150,350);
    glVertex2f(110,275);
    glVertex2f(150,435);
    glVertex2f(190,275);
glEnd();

glBegin(GL_QUADS);
    glVertex2f(150,350);
    glVertex2f(75,385);
    glVertex2f(225,385);
    glVertex2f(110,275);
glEnd();

glBegin(GL_QUADS);
    glVertex2f(150,350);
    glVertex2f(150,435);
    glVertex2f(190,275);
    glVertex2f(75,385);
glEnd();

glBegin(GL_QUADS);
    glVertex2f(150,350);
    glVertex2f(225,385);
    glVertex2f(110,275);
    glVertex2f(150,435);
glEnd();

glBegin(GL_QUADS);
    glVertex2f(150,350);
    glVertex2f(190,275);
    glVertex2f(75,385);
    glVertex2f(225,385);
glEnd();
*/
/*//white star polygone
    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_POLYGON);
        
        glVertex2f(110,275);
        glVertex2f(150,425);
        glVertex2f(190,275);
        glVertex2f(75,385);
        glVertex2f(225,385);
    glEnd();
*/

//white star line
    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_LINES);
        glVertex2f(110,275);
        glVertex2f(150,450);
        glVertex2f(150,450);
        glVertex2f(190,275);
        glVertex2f(190,275);
        glVertex2f(75,385);
        glVertex2f(75,385);
        glVertex2f(225,385);
        glVertex2f(225,385);
        glVertex2f(110,275);
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(809, 500);
    glutCreateWindow("lab 5.4");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}