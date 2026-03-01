#include <GLUT/glut.h>
#include <cmath>

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,330,0,250);

    glMatrixMode(GL_MODELVIEW);
}

void display() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

//upper black
for (int i = 1; i < 8; i++) {
        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_QUADS);

        glVertex2f(10 + i * 10, 150);
        glVertex2f(10 + i * 10, 150 + i * 10);
        glVertex2f(320 - i * 10, 150 +i * 10);
        glVertex2f(320 - i * 10, 150);
    glEnd();
}

//upperylw
for (int i = 1; i < 7; i++) {
        glColor3f(1.0f, 1.0f, 0.0f);
        glBegin(GL_QUADS);

        glVertex2f(20 + i * 10, 150);
        glVertex2f(20 + i * 10, 150 + i * 10);
        glVertex2f(310 - i * 10, 150 +i * 10);
        glVertex2f(310 - i * 10, 150);
    glEnd();
}
//mid black
glColor3f(0.0f, 0.0f, 0.0f);
glBegin(GL_QUADS);

glVertex2f(10, 80);
glVertex2f(10, 150);
glVertex2f(320, 150);
glVertex2f(320, 80);
glEnd();

//mid ylw
glColor3f(1.0f, 1.0f, 0.0f);
glBegin(GL_QUADS);

glVertex2f(20, 80);
glVertex2f(20, 150);
glVertex2f(310, 150);
glVertex2f(310, 80);
glEnd();

//lower black
for (int i = 1; i < 8; i++) {
        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_QUADS);

        glVertex2f(10 + i * 10, 80);
        glVertex2f(10 + i * 10, 80 - i * 10);
        glVertex2f(320 - i * 10, 80 -i * 10);
        glVertex2f(320 - i * 10, 80);
    glEnd();
}

//lower yellow
for (int i = 1; i < 7; i++) {
        glColor3f(1.0f, 1.0f, 0.0f);
        glBegin(GL_QUADS);

        glVertex2f(20 + i * 10, 80);
        glVertex2f(20 + i * 10, 80 - i * 10);
        glVertex2f(310 - i * 10, 80 -i * 10);
        glVertex2f(310 - i * 10, 80);
    glEnd();
}

//mid logo black
glColor3f(0.0f, 0.0f, 0.0f);
glBegin(GL_QUADS);

glVertex2f(30, 90);
glVertex2f(30, 140);
glVertex2f(300, 140);
glVertex2f(300, 90);
glEnd();

//mid logo upper
for (int i = 1; i < 6; i++) {
        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_QUADS);

        glVertex2f(30 + i * 10, 140);
        glVertex2f(30 + i * 10, 140 +i * 10);
        glVertex2f(300 - i * 10, 140 +i * 10);
        glVertex2f(300 - i * 10, 140);
    glEnd();
}
//mid logo lower
for (int i = 1; i < 6; i++) {
        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_QUADS);

        glVertex2f(30 + i * 10, 90);
        glVertex2f(30 + i * 10, 90 - i * 10);
        glVertex2f(300 - i * 10, 90 -i * 10);
        glVertex2f(300 - i * 10, 90);
    glEnd();
}
//extra 1 ylw
glColor3f(1.0f, 1.0f, 0.0f);
glBegin(GL_QUADS);
    glVertex2f(110,140);
    glVertex2f(110,150);
    glVertex2f(130,150);
    glVertex2f(130,140);
    glEnd();
glBegin(GL_QUADS);
    glVertex2f(100,150);
    glVertex2f(100,180);
    glVertex2f(140,180);
    glVertex2f(140,150);
    glEnd();
glBegin(GL_QUADS);
    glVertex2f(110,180);
    glVertex2f(110,190);
    glVertex2f(140,190);
    glVertex2f(140,180);
    glEnd();
glBegin(GL_QUADS);
    glVertex2f(130,70);
    glVertex2f(130,80);
    glVertex2f(140,80);
    glVertex2f(140,70);
    glEnd();
glBegin(GL_QUADS);
    glVertex2f(120,60);
    glVertex2f(120,70);
    glVertex2f(150,70);
    glVertex2f(150,60);
    glEnd();
glBegin(GL_QUADS);
    glVertex2f(110,50);
    glVertex2f(110,60);
    glVertex2f(150,60);
    glVertex2f(150,50);
    glEnd();
glBegin(GL_QUADS);
    glVertex2f(110,40);
    glVertex2f(110,50);
    glVertex2f(160,50);
    glVertex2f(160,40);
    glEnd();


//extra 1 ylw mirror
glColor3f(1.0f, 1.0f, 0.0f);
glBegin(GL_QUADS);
    glVertex2f(200,140);
    glVertex2f(200,150);
    glVertex2f(220,150);
    glVertex2f(220,140);
    glEnd();
glBegin(GL_QUADS);
    glVertex2f(190,150);
    glVertex2f(190,180);
    glVertex2f(230,180);
    glVertex2f(230,150);
    glEnd();
glBegin(GL_QUADS);
    glVertex2f(190,180);
    glVertex2f(190,190);
    glVertex2f(220,190);
    glVertex2f(220,180);
    glEnd();
glBegin(GL_QUADS);
    glVertex2f(190,70);
    glVertex2f(190,80);
    glVertex2f(200,80);
    glVertex2f(200,70);
    glEnd();    
glBegin(GL_QUADS);
    glVertex2f(180,60);
    glVertex2f(180,70);
    glVertex2f(210,70);
    glVertex2f(210,60);
    glEnd();
glBegin(GL_QUADS);
    glVertex2f(180,50);
    glVertex2f(180,60);
    glVertex2f(220,60);
    glVertex2f(220,50);
    glEnd();
glBegin(GL_QUADS);
    glVertex2f(170,40);
    glVertex2f(170,50);
    glVertex2f(220,50);
    glVertex2f(220,40);
    glEnd();  
//black extra
glColor3f(0.0f, 0.0f, 0.0f);
glBegin(GL_QUADS);
    glVertex2f(220,30);
    glVertex2f(220,40);
    glVertex2f(230,40);
    glVertex2f(230,30);
    glEnd();  
glBegin(GL_QUADS);
    glVertex2f(140,190);
    glVertex2f(140,200);
    glVertex2f(150,200);
    glVertex2f(150,190);
    glEnd();  
//black extra mirror
glColor3f(0.0f, 0.0f, 0.0f);
glBegin(GL_QUADS);
    glVertex2f(100,30);
    glVertex2f(100,40); 
    glVertex2f(110,40);
    glVertex2f(110,30);
glEnd();
glBegin(GL_QUADS);
    glVertex2f(180,190);
    glVertex2f(180,200);
    glVertex2f(190,200);
    glVertex2f(190,190);
    glEnd();

 //line   
glBegin(GL_LINES);
glColor3f(0.0f, 1.0f, 0.0f);
    for (int i = 0; i <= 250; i += 10) {
    glVertex2f(0, i);
    glVertex2f(330, i);
}
for (int j = 0; j <= 330; j += 10) {
    glVertex2f(j, 0);
    glVertex2f(j, 250);
}
    glEnd();


glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(330, 250);
    glutCreateWindow("Lab 4");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
