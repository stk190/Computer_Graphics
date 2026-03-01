#include <GLUT/glut.h>
#include <cmath>

void display() {
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(0,400,0,400);

for (int i = 0; i < 8; i++) {    
    for (int j = 0; j < 8; j++) {
    if ((i+j)%2==0){
            glColor3f(1.0f, 1.0f, 1.0f);
            glBegin(GL_QUADS);
            glVertex2f(i*50, j*50);
            glVertex2f(i*50, j*50+50);
            glVertex2f(i*50+50, j*50+50);
            glVertex2f(i*50+50, j*50);
            glEnd();
    }
    else{
            glColor3f(0.0f, 0.0f, 0.0f);
            glBegin(GL_QUADS);
            glVertex2f(i*50, j*50);
            glVertex2f(i*50, j*50+50);
            glVertex2f(i*50+50, j*50+50);
            glVertex2f(i*50+50, j*50);
            glEnd();
    }
    }
    
    
}
glFlush();

}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Lab 3");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
