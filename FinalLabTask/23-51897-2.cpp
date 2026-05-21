#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#endif

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>
using namespace std;

const int WIN_W = 800;
const int WIN_H = 500;
const float PI = 3.1415926f;

enum Weather { CLEAR = 0, RAIN = 1, SNOW = 2 };

int scene       = 1;
int weatherMode = CLEAR;
bool isDay      = true;
bool isPaused = false;
float lightFactor = 1.0f;

//animation variables
float cloudX1 = 0.0f, cloudX2 = 300.0f;
float scene2CloudX1 = -280.0f, scene2CloudX2 = -340.0f;
float carX    = -120.0f;
float carX2 = 900.0f;
float scene2CarX = -120.0f;
float carAngle = 0.0f;
float boatX   = -160.0f;
float birdOffset = 0.0f;
float waterAnim  = 0.0f;
float rainOffset = 0.0f;
float starPulseAngle = 0.0f;
float starScale = 1.0f + 0.2f * sin(starPulseAngle);
float bladeAngle = 0.0f;
float loomingCloudScale = 0.85f;
float carSpeed = 1.5f;
float blueCarSpeed = 1.2f;
float planeScale = 0.3f;
float radarAngle = 0.0f;
float scene2ShipSpeed = 1.6f;
int radarStopTimer = 0;
bool radarStopActive = false;
float fogAlpha   = 0.0f;
float planeX = -180.0f;
float trainX = WIN_W + 220.0f;
float coastalTrainX = -520.0f;
float busX   = -160.0f;
float shipX  = -180.0f;
bool signalGreen = true;
int  signalTimer = 0;

struct SnowParticle {
    float x, y;
    float speed;
    float drift;
    float size;
};
vector<SnowParticle> snowParticles;



void setColor(float r, float g, float b, bool lit = true) {
    float f = lit ? lightFactor : 1.0f;
    glColor3f(r * f, g * f, b * f);
}
float degToRad(float d) { return d * PI / 180.0f; }
//shapes
void drawGradientRect(float x1, float y1, float x2, float y2,float r1, float g1, float b1,float r2, float g2, float b2) {
    glBegin(GL_QUADS);
        glColor3f(r1, g1, b1); glVertex2f(x1, y1);
        glColor3f(r1, g1, b1); glVertex2f(x2, y1);
        glColor3f(r2, g2, b2); glVertex2f(x2, y2);
        glColor3f(r2, g2, b2); glVertex2f(x1, y2);
    glEnd();
}
void drawCircle(float cx, float cy, float r, int segs = 64) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= segs; i++) {
        float a = 2.0f * PI * i / segs;
        glVertex2f(cx + r * cos(a), cy + r * sin(a));
    }
    glEnd();
}
void drawCircleOutline(float cx, float cy, float r, int segs = 64) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segs; i++) {
        float a = 2.0f * PI * i / segs;
        glVertex2f(cx + r * cos(a), cy + r * sin(a));
    }
    glEnd();
}
void drawQuads(float x1, float y1, float x2, float y2,float x3, float y3, float x4, float y4) {
    glBegin(GL_QUADS);
        glVertex2f(x1, y1); glVertex2f(x2, y2);
        glVertex2f(x3, y3); glVertex2f(x4, y4);
    glEnd();
}
void drawRect(float x, float y, float w, float h) {
    drawQuads(x, y, x+w, y, x+w, y+h, x, y+h);
}
void drawLine(float x1, float y1, float x2, float y2) {
    glBegin(GL_LINES);
        glVertex2f(x1, y1); glVertex2f(x2, y2);
    glEnd();
}
void drawTriangle(float x1, float y1, float x2, float y2,float x3, float y3) {
    glBegin(GL_TRIANGLES);
        glVertex2f(x1, y1); glVertex2f(x2, y2); glVertex2f(x3, y3);
    glEnd();
}
void drawRoundRect(float x, float y, float w, float h, float r) {
    drawRect(x + r, y, w - 2*r, h);
    drawRect(x, y + r, w, h - 2*r);
    drawCircle(x + r,     y + r,     r);
    drawCircle(x + w - r, y + r,     r);
    drawCircle(x + r,     y + h - r, r);
    drawCircle(x + w - r, y + h - r, r);
}

//sky,sun, moon,clouds,stars,birds,water, tree
void drawSky() {
    if (isDay) {
        lightFactor = 1.0f;
        // Horizon gradient
        drawGradientRect(0, 250, WIN_W, WIN_H,
                         0.55f, 0.75f, 0.97f,
                         0.25f, 0.55f, 0.90f);
        drawGradientRect(0, 0, WIN_W, 250,
                         0.72f, 0.88f, 1.0f,
                         0.55f, 0.75f, 0.97f);
    } else {
        lightFactor = 0.42f;
        drawGradientRect(0, 0, WIN_W, WIN_H,
                         0.02f, 0.03f, 0.10f,
                         0.06f, 0.08f, 0.22f);
    }
}
void drawStars() {
    if (isDay) return;

    glColor3f(1.0f, 1.0f, 0.9f);

    auto starScale = [&](float phase) {
        return 0.8f + 0.5f * sin(degToRad(starPulseAngle + phase));
    };

    float scale;

    glPushMatrix();
    glTranslatef(40, 460, 0);
    scale = starScale(0.0f);
    glScalef(scale, scale, 1.0f);
    drawCircle(0, 0, 1.5f, 8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(90, 430, 0);
    scale = starScale(18.0f);
    glScalef(scale, scale, 1.0f);
    drawCircle(0, 0, 1.2f, 8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(130, 470, 0);
    scale = starScale(36.0f);
    glScalef(scale, scale, 1.0f);
    drawCircle(0, 0, 1.4f, 8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(180, 420, 0);
    scale = starScale(54.0f);
    glScalef(scale, scale, 1.0f);
    drawCircle(0, 0, 1.3f, 8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(250, 480, 0);
    scale = starScale(72.0f);
    glScalef(scale, scale, 1.0f);
    drawCircle(0, 0, 1.5f, 8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(320, 450, 0);
    scale = starScale(90.0f);
    glScalef(scale, scale, 1.0f);
    drawCircle(0, 0, 1.2f, 8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(380, 470, 0);
    scale = starScale(108.0f);
    glScalef(scale, scale, 1.0f);
    drawCircle(0, 0, 1.4f, 8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(430, 430, 0);
    scale = starScale(126.0f);
    glScalef(scale, scale, 1.0f);
    drawCircle(0, 0, 1.3f, 8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(500, 460, 0);
    scale = starScale(144.0f);
    glScalef(scale, scale, 1.0f);
    drawCircle(0, 0, 1.5f, 8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(560, 420, 0);
    scale = starScale(162.0f);
    glScalef(scale, scale, 1.0f);
    drawCircle(0, 0, 1.2f, 8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(620, 480, 0);
    scale = starScale(180.0f);
    glScalef(scale, scale, 1.0f);
    drawCircle(0, 0, 1.4f, 8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(690, 440, 0);
    scale = starScale(198.0f);
    glScalef(scale, scale, 1.0f);
    drawCircle(0, 0, 1.3f, 8);
    glPopMatrix();
}
void drawSun() {
   
    glColor4f(1.0f, 0.92f, 0.4f, 0.08f);
    drawCircle(400, 435, 55);
    glColor4f(1.0f, 0.88f, 0.3f, 0.15f);
    drawCircle(400, 435, 42);
    glColor3f(1.0f, 0.92f, 0.2f);
    drawCircle(400, 435, 28);
    glColor3f(1.0f, 0.98f, 0.7f);
    drawCircle(400, 435, 16);
}
void drawMoon() {
    glColor3f(0.6f, 0.6f, 0.75f);
    drawCircle(400, 435, 32);
    glColor3f(0.88f, 0.88f, 0.98f);
    drawCircle(400, 435, 24);
    glColor3f(0.70f, 0.70f, 0.82f);
    drawCircle(392, 440, 4);
    drawCircle(405, 426, 3);
    drawCircle(385, 428, 2.5f);
}
void drawSunMoon() {
    if (isDay) drawSun();
    else drawMoon();
}
void drawCloud(float x, float y, float size) {
    float f = lightFactor;
    float r = isDay ? 1.0f*f : 0.55f*f;
    float g = isDay ? 1.0f*f : 0.58f*f;
    float b = isDay ? 1.0f*f : 0.68f*f;

    glColor3f(r, g, b);
    drawCircle(x,            y,            size);
    drawCircle(x + size,     y + size*0.5f, size*1.25f);
    drawCircle(x + size*2.1f, y,            size);
    drawCircle(x + size*0.7f, y - size*0.2f, size*0.85f);
    drawCircle(x + size*1.5f, y - size*0.1f, size*0.9f);
    glColor3f(min(r+0.08f,1.0f), min(g+0.08f,1.0f), min(b+0.08f,1.0f));
    drawCircle(x + size,     y + size*0.65f, size*0.7f);
}
void drawScaledCloud(float x, float y, float size, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(scale, scale, 1.0f);
    drawCloud(0, 0, size);
    glPopMatrix();
}
void drawWindmill(float x, float y) {
    // Base (tower)
    setColor(0.45f, 0.35f, 0.25f);
    drawRect(x - 8, y, 16, 80);
    
    // Hub (center of blades)
    setColor(0.30f, 0.30f, 0.30f);
    drawCircle(x, y + 80, 6);
    
    // Draw rotating blades
    glPushMatrix();
    glTranslatef(x, y + 80, 0);
    glRotatef(bladeAngle, 0, 0, 1);
    
    setColor(0.85f, 0.82f, 0.75f);
    // Blade 1
    drawRect(-4, 0, 8, 35);
    // Blade 2 (90 degrees)
    glPushMatrix();
    glRotatef(90, 0, 0, 1);
    drawRect(-4, 0, 8, 35);
    glPopMatrix();
    // Blade 3 (180 degrees)
    glPushMatrix();
    glRotatef(180, 0, 0, 1);
    drawRect(-4, 0, 8, 35);
    glPopMatrix();
    // Blade 4 (270 degrees)
    glPushMatrix();
    glRotatef(270, 0, 0, 1);
    drawRect(-4, 0, 8, 35);
    glPopMatrix();
    
    glPopMatrix();
}
void drawRadar(float x, float y) {
    // Radar tower base
    setColor(0.28f, 0.30f, 0.34f);
    drawRect(x - 4, y - 8, 8, 16);
    drawRect(x - 10, y + 8, 20, 6);

    // Radar dish and rotating beam
    glPushMatrix();
    glTranslatef(x, y + 12, 0);
    glRotatef(radarAngle, 0, 0, 1);

    setColor(0.78f, 0.82f, 0.88f);
    drawRect(-2, 0, 4, 18);
    drawCircle(0, 18, 6);
    drawCircleOutline(0, 18, 8);

    glColor4f(0.16f, 0.95f, 0.24f, 0.18f);
    glBegin(GL_TRIANGLES);
        glVertex2f(0, 18);
        glVertex2f(-42, 80);
        glVertex2f(42, 80);
    glEnd();
    glPopMatrix();
}
void drawBird(float x, float y, float scale = 1.0f) {
    float d = isDay ? 0.05f : 0.4f;
    glColor3f(d, d, d);
    glLineWidth(1.5f);
    glBegin(GL_LINE_STRIP);
        glVertex2f(x,               y);
        glVertex2f(x + 8*scale,     y + 5*scale);
        glVertex2f(x + 16*scale,    y);
    glEnd();
    glBegin(GL_LINE_STRIP);
        glVertex2f(x + 16*scale,    y);
        glVertex2f(x + 24*scale,    y + 5*scale);
        glVertex2f(x + 32*scale,    y);
    glEnd();
    glLineWidth(1.0f);
}
void drawWater(float y1, float y2) {
    // Base water gradient
    float wr = 0.12f, wg = 0.38f, wb = 0.72f;
    drawGradientRect(0, y1, WIN_W, y2,
                     wr*lightFactor,  wg*lightFactor,  wb*lightFactor,
                     (wr+0.08f)*lightFactor, (wg+0.18f)*lightFactor,
                     (wb+0.12f)*lightFactor);

    // Animated ripples
    setColor(0.55f, 0.75f, 0.95f);
    glLineWidth(1.5f);
    for (int wx = 0; wx < WIN_W; wx += 60) {
        float off = fmod(waterAnim + wx * 0.3f, 60.0f);
        drawLine(wx - off, y2 - 20, wx - off + 30, y2 - 18);
        drawLine(wx - off + 10, y2 - 45, wx - off + 40, y2 - 43);
        drawLine(wx - off + 5,  y2 - 70, wx - off + 25, y2 - 68);
    }
    glLineWidth(1.0f);

    // Reflection shimmer (sun/moon)
    if (isDay) {
        glColor3f(1.0f * lightFactor, 0.95f * lightFactor, 0.6f * lightFactor);
    } else {
        glColor3f(0.6f * lightFactor, 0.6f * lightFactor, 0.7f * lightFactor);
    }
    float shimX = 400 + 30 * sin(degToRad(waterAnim * 3.0f));
    for (int si = 0; si < 5; si++) {
        float sw = 4.0f - si;
        drawLine(shimX - 10 + si*6, y2 - 10 - si*8,
                 shimX - 10 + si*6 + sw, y2 - 10 - si*8);
    }
}
void drawTree(float x, float y, float scale = 1.0f) {

    setColor(0.32f, 0.20f, 0.10f);
    drawRect(x - 6*scale, y, 12*scale, 52*scale);
    setColor(0.22f, 0.14f, 0.07f);
    drawRect(x - 2*scale, y, 4*scale, 52*scale);
    setColor(0.01f, 0.28f, 0.04f);
    drawCircle(x + 2*scale, y + 58*scale, 24*scale);
    setColor(0.04f, 0.45f, 0.07f);
    drawCircle(x - 12*scale, y + 52*scale, 20*scale);
    drawCircle(x + 14*scale, y + 50*scale, 20*scale);
    drawCircle(x,            y + 70*scale, 22*scale);
    setColor(0.15f, 0.68f, 0.12f);
    drawCircle(x - 8*scale, y + 60*scale, 14*scale);
    drawCircle(x + 8*scale, y + 68*scale, 15*scale);
    setColor(0.25f, 0.80f, 0.18f);
    drawCircle(x,   y + 76*scale, 12*scale);
}

//street fence, streetlight, signal, walkway
void drawFence(float startX, float endX, float y) {
    if (scene == 2 && y < 50) return;
    // Horizontal bars
    glColor3f(0.75f, 0.75f, 0.75f);
    drawRect(startX, y, endX - startX, 5);
    drawRect(startX, y + 20, endX - startX, 5);

    // Vertical supports
    for (float x = startX; x <= endX; x += 25) {
        drawRect(x, y - 5, 4, 30);
    }
}
void drawStreetLight(float x, float y, bool facingRight = true) {
    // Base
    setColor(0.35f, 0.35f, 0.38f);
    drawRect(x, y, 6, 70);
    drawRect(x - 8, y, 22, 7);  // Foot plate

    // Arm
    float armDir = facingRight ? 1.0f : -1.0f;
    setColor(0.30f, 0.30f, 0.32f);
    drawRect(x + 3, y + 65, armDir * 28, 4);

    // Lamp housing
    float lx = facingRight ? x + 28 : x - 22;
    setColor(0.25f, 0.25f, 0.28f);
    drawRect(lx, y + 60, 16, 10);

    if (!isDay) {
        // Warm glow
        glColor3f(1.0f, 0.85f, 0.40f);
        drawCircle(lx + 8, y + 72, 9);

        // Light cone (soft)
        glColor3f(1.0f * 0.08f, 0.9f * 0.08f, 0.5f * 0.08f);
        drawTriangle(lx, y + 63, lx + 16, y + 63,
                     lx + 8, y - 20);
    }
}
void drawSignal(float x, float y, bool green = true) {
    // Pole
    setColor(0.22f, 0.22f, 0.24f);
    drawRect(x, y, 7, 60);

    // Box
    setColor(0.12f, 0.12f, 0.14f);
    drawRoundRect(x - 8, y + 60, 23, 55, 4);

    // Red light
    glColor3f(green ? 0.30f : 1.0f,
              0.05f,
              0.05f);
    drawCircle(x + 3.5f, y + 100, 7);

    // Glow ring for active red
    if (!green) {
        glColor3f(0.8f, 0.1f, 0.1f);
        drawCircleOutline(x + 3.5f, y + 100, 9);
    }

    // Green light
    glColor3f(0.05f,
              green ? 1.0f : 0.20f,
              0.05f);
    drawCircle(x + 3.5f, y + 80, 7);

    // Glow ring for active green
    if (green) {
        glColor3f(0.1f, 0.8f, 0.1f);
        drawCircleOutline(x + 3.5f, y + 80, 9);
    }
}
void drawWalkway(float x, float y, float w, float h) {
    // Main walkway base
    setColor(0.55f, 0.55f, 0.58f);
    drawRect(x, y, w, h);

    // Edge borders (slightly darker strips)
    setColor(0.45f, 0.45f, 0.48f);
    drawRect(x, y, w, 6);         // bottom border
    drawRect(x, y + h - 6, w, 6); // top border

    // Tile grid (horizontal lines)
    glColor3f(0.40f, 0.40f, 0.43f);
    for (float yy = y; yy < y + h; yy += 25) {
        drawLine(x, yy, x + w, yy);
    }

    // Tile grid (vertical lines)
    for (float xx = x; xx < x + w; xx += 40) {
        drawLine(xx, y, xx, y + h);
    }
    // Slight highlight strip (light reflection)
    setColor(0.62f, 0.62f, 0.65f);
    drawRect(x, y + h * 0.65f, w, 2);
}

bool windowOn(int bx, int wx, int wy) {
    int h = (bx * 31 + wx * 17 + wy * 7) % 5;
    return h != 0;
}
//building
void drawBuilding(float x, float y, float w, float h,float rBase, float gBase, float bBase) {
    
    drawGradientRect(x, y, x + w, y + h,
                     rBase * lightFactor,
                     gBase * lightFactor,
                     bBase * lightFactor,
                     (rBase - 0.05f) * lightFactor,
                     (gBase - 0.05f) * lightFactor,
                     (bBase + 0.02f) * lightFactor);


    setColor(rBase - 0.08f, gBase - 0.08f, bBase);
    drawRect(x, y, 6, h);
    setColor(rBase + 0.08f, gBase + 0.08f, bBase + 0.06f);
    drawRect(x - 4, y + h, w + 8, 8);
    float wSize = 12, gap = 22;
    for (float wy = y + 18; wy < y + h - 15; wy += gap) {
        for (float wx = x + 14; wx < x + w - 14; wx += gap) {

            if (isDay) {
                
                setColor(0.62f, 0.82f, 0.98f, false);
                drawRect(wx, wy, wSize, wSize);
                setColor(0.85f, 0.95f, 1.0f, false);
                drawRect(wx, wy + wSize - 4, wSize, 4);
            } else {
                if (windowOn((int)x, (int)wx, (int)wy)) {
                    glColor3f(1.0f, 0.88f, 0.40f);
                    drawRect(wx, wy, wSize, wSize);
                    // Window glow
                    glColor3f(0.5f, 0.44f, 0.10f);
                    drawRect(wx - 2, wy - 2, wSize + 4, wSize + 4);
                    glColor3f(1.0f, 0.88f, 0.40f);
                    drawRect(wx, wy, wSize, wSize);
                } else {
                    glColor3f(0.06f, 0.06f, 0.10f);
                    drawRect(wx, wy, wSize, wSize);
                }
            }
        }
    }
}
void drawBuilding2(float x, float y, float w, float h,float rBase, float gBase, float bBase) {
    drawBuilding(x, y, w, h, rBase, gBase, bBase);

    setColor(0.30f, 0.30f, 0.32f);
    drawRect(x + w/2 - 2, y + h, 4, 30);
    drawRect(x + w/2 - 6, y + h + 24, 12, 4);

    if (!isDay) {
        glColor3f(1.0f, 0.2f, 0.2f);
        drawCircle(x + w/2, y + h + 32, 4);
    }
}

//car,boat,airplane
void drawCar(float x, float y, float r, float g, float b) {
   
    setColor(0.05f, 0.05f, 0.05f);
    glBegin(GL_QUADS);
        glVertex2f(x + 5,  y - 7);
        glVertex2f(x + 63, y - 7);
        glVertex2f(x + 60, y - 2);
        glVertex2f(x + 8,  y - 2);
    glEnd();

    setColor(r, g, b);
    drawRect(x, y, 68, 22);
    setColor(r * 0.88f, g * 0.88f, b * 0.88f);
    glBegin(GL_QUADS);
        glVertex2f(x + 14, y + 22);
        glVertex2f(x + 54, y + 22);
        glVertex2f(x + 46, y + 40);
        glVertex2f(x + 22, y + 40);
    glEnd();

    setColor(0.55f, 0.82f, 1.0f);
    drawTriangle(x + 16, y + 22, x + 33, y + 22, x + 25, y + 38);
    drawTriangle(x + 35, y + 22, x + 52, y + 22, x + 44, y + 38);

    if (!isDay) {
        glColor3f(1.0f, 1.0f, 0.7f);
    } else {
        setColor(0.9f, 0.9f, 0.7f);
    }
    drawRect(x + 60, y + 6, 6, 8);
    drawRect(x + 2,  y + 6, 6, 8);


    glColor3f(0.9f * lightFactor, 0.1f, 0.1f);
    drawRect(x + 2, y + 8, 5, 6);

    glColor3f(0.08f, 0.08f, 0.08f);
    drawCircle(x + 16, y - 3, 9);
    drawCircle(x + 52, y - 3, 9);
    setColor(0.65f, 0.65f, 0.68f);
    drawCircle(x + 16, y - 3, 5);
    drawCircle(x + 52, y - 3, 5);
    setColor(0.80f, 0.80f, 0.82f);
    drawCircle(x + 16, y - 3, 2.5f);
    drawCircle(x + 52, y - 3, 2.5f);

    setColor(r * 0.7f, g * 0.7f, b * 0.7f);
    drawRect(x - 4, y + 3, 6, 14);
    drawRect(x + 66, y + 3, 6, 14);
}
void drawRotatedCar(float x, float y, float angleDeg,float r, float g, float b) {
    glPushMatrix();
        glTranslatef(x, y, 0);
        glRotatef(angleDeg, 0, 0, 1);
        drawCar(-34, -12, r, g, b);
    glPopMatrix();
}
void drawBoat(float x, float y) {
    // Hull shadow
    setColor(0.18f, 0.08f, 0.04f);
    drawTriangle(x + 5, y - 5, x + 108, y - 5, x + 85, y - 32);

    // Hull
    setColor(0.52f, 0.24f, 0.10f);
    drawTriangle(x,     y, x + 105, y, x + 82, y - 30);
    drawTriangle(x,     y, x + 82,  y - 30, x + 20, y - 30);

    // Hull edge highlight
    setColor(0.72f, 0.42f, 0.20f);
    drawLine(x, y, x + 105, y);

    // Mast
    setColor(0.28f, 0.15f, 0.06f);
    drawRect(x + 46, y, 4, 70);

    // Sail
    setColor(0.95f, 0.92f, 0.82f);
    drawTriangle(x + 50, y + 5, x + 50, y + 68, x + 90, y + 15);

    
}
void drawAirplane(float x, float y) {

    setColor(0.86f, 0.88f, 0.90f);
    glBegin(GL_POLYGON);
        glVertex2f(x,      y + 8);
        glVertex2f(x + 12, y + 16);
        glVertex2f(x + 76, y + 16);
        glVertex2f(x + 96, y + 10);
        glVertex2f(x + 76, y + 4);
        glVertex2f(x + 12, y + 4);
    glEnd();


    setColor(0.66f, 0.70f, 0.78f);
    glBegin(GL_QUADS);
        glVertex2f(x + 38, y + 11);
        glVertex2f(x + 68, y + 11);
        glVertex2f(x + 92, y - 14);
        glVertex2f(x + 58, y - 10);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(x + 35, y + 13);
        glVertex2f(x + 58, y + 14);
        glVertex2f(x + 43, y + 34);
        glVertex2f(x + 24, y + 30);
    glEnd();

    setColor(0.58f, 0.62f, 0.70f);
    drawTriangle(x + 10, y + 15, x + 26, y + 15, x + 12, y + 38);
    drawTriangle(x + 12, y + 7, x + 30, y + 7, x + 4, y - 6);

    setColor(0.30f, 0.62f, 0.88f);
    drawTriangle(x + 78, y + 13, x + 92, y + 10, x + 78, y + 8);
    for (int i = 0; i < 5; i++) {
        drawRect(x + 25 + i * 9, y + 10, 4, 4);
    }
}


void initSnow() {

    snowParticles.clear();

    for (int i = 0; i < 100; i++) {

        SnowParticle p;

       
        p.x = (i * 37) % WIN_W;

       
        p.y = (i * 53) % WIN_H;

      
        p.speed = 0.2f + (i % 5) * 0.08f;

   
        if (i % 2 == 0)
            p.drift = 0.05f;
        else
            p.drift = -0.05f;

    
        p.size = 1.5f + (i % 3);

        snowParticles.push_back(p);
    }
}
void drawSnow() {

    for (auto &p : snowParticles) {
        glColor3f(0.90f, 0.90f, 1.0f);
        drawCircle(p.x, p.y, p.size);
        glColor3f(1.0f, 1.0f, 1.0f);
        drawCircle(p.x, p.y, p.size * 0.45f);
    }
}
void drawRain() {
    glLineWidth(1.2f);

    for (int x = -10; x < WIN_W + 10; x += 22) {
        for (int y = 0; y < WIN_H + 60; y += 36) {
            float yy = fmod(y - rainOffset * 0.35f, WIN_H + 60.0f);
            glColor3f(0.55f, 0.68f, 0.95f);
            drawLine(x, yy, x + 4, yy - 14);
        }
    }
    glLineWidth(1.0f);
    glColor3f(0.50f, 0.65f, 0.95f);
    for (int x = 30; x < WIN_W; x += 80) {
        drawCircleOutline(x, 8, 4);
        drawCircleOutline(x + 35, 5, 3);
    }
}
void drawWeather() {
    if (weatherMode == RAIN)  drawRain();
    else if (weatherMode == SNOW) drawSnow();
}

//scene
void drawScene1() {
   
    drawSky();
    drawStars();
    drawSunMoon();
    drawStars();
    drawScaledCloud(cloudX1 + 40,  435, 20, loomingCloudScale);
    drawCloud(cloudX2 + 320, 455, 16);
    drawScaledCloud(cloudX1,  435, 20, loomingCloudScale);
    drawCloud(cloudX2, 455, 16);
    drawCloud(cloudX1 + 550, 420, 22);
    
    drawScaledCloud(cloudX1 + 80, 430, 22, loomingCloudScale);
    drawCloud(cloudX2 + 350, 450, 18);
    drawScaledCloud(cloudX1, 430, 22, loomingCloudScale);
    drawCloud(cloudX2, 450, 18);
    drawCloud(cloudX1 + 600, 420, 20);

    drawWater(0, 170);

    setColor(0.76f, 0.70f, 0.50f);
    drawRect(0, 170, 800, 30);

    //road
    setColor(0.20f, 0.20f, 0.22f);
    drawRect(0, 200, 800, 100);

    //divider
    glColor3f(1.0f, 1.0f, 0.6f);
    for (int x = 0; x < WIN_W; x += 80) {
        drawRect(x, 248, 35, 4);
    }

    //zebra
    setColor(0.20f, 0.20f, 0.22f);
    drawRect(320, 200, 60, 100);
    glColor3f(1, 1, 1);
    drawLine(320, 200, 320, 300);
    drawLine(380, 200, 380, 300);
    for (int y = 200; y < 300; y += 14) {
        drawRect(320, y, 60, 6);
    }

    //walkway
    drawWalkway(0, 300, 800, 30);

    //tree
    drawTree(450, 310, 1.2f);
    drawTree(550, 310, 1.2f);

    //fence
    drawFence(0, 320, 200);
    drawFence(380, 800, 200);
     

    

    //buildings
    drawBuilding(  0, 330,  80, 140, 0.28f, 0.28f, 0.35f);
    drawBuilding( 90, 330,  90, 160, 0.24f, 0.24f, 0.32f);
    //drawBuilding(630, 330,  90, 155, 0.24f, 0.24f, 0.32f);
    drawBuilding(730, 330,  70, 130, 0.28f, 0.28f, 0.35f);
    //windmill
    drawWindmill(700, 310);
    drawWindmill(250, 310);
    drawFence(0, 320, 300);
    drawFence(380, 800, 300);
    drawStreetLight(250, 300, true);
    drawStreetLight(650, 300, false);

    //cars
    drawSignal(400, 300, signalGreen);
    drawCar(carX, 242, 0.85f, 0.08f, 0.06f);
    glPushMatrix();
    glTranslatef(carX2 + 34, 275 + 20, 0);
    glScalef(-1, 1, 1);
    drawCar(-34, -20, 0.10f, 0.40f, 0.90f);
    glPopMatrix();

    // Trees
    drawTree(110, 192, 1.2f);
    drawTree(680, 192, 1.2f);

    //signals
    drawSignal(300, 200, signalGreen);

    drawStreetLight(150, 200, true);
    drawStreetLight(550, 200, false);

    //birds
    if (weatherMode == CLEAR && isDay) {
        float bo = birdOffset;
        drawBird(180 + bo, 440, 1.0f);
        drawBird(340 + bo, 418, 0.9f);
        drawBird(500 + bo * 0.7f, 432, 1.0f);
    }
}
void drawScene2Bus(float x) {
    setColor(0.95f, 0.18f, 0.12f);
    drawRect(x, 165, 120, 38);
    setColor(0.72f, 0.08f, 0.05f);
    drawRect(x + 15, 190, 70, 18);
    glColor3f(0.72f, 0.88f, 1.0f);
    for (int i = 0; i < 5; i++) drawRect(x + 12 + i * 18, 175, 12, 10);
    glColor3f(0.1f, 0.1f, 0.1f);
    drawCircle(x + 25, 160, 10);
    drawCircle(x + 95, 160, 10);
}

void drawScene2Car(float x) {
    setColor(0.1f, 0.45f, 0.9f);
    drawRect(x + 240, 125, 55, 20);
    setColor(0.08f, 0.28f, 0.6f);
    drawRect(x + 250, 142, 30, 12);
    setColor(0.55f, 0.82f, 1.0f);
    drawRect(x + 253, 144, 9, 6);
    drawRect(x + 267, 144, 9, 6);
    glColor3f(0.1f, 0.1f, 0.1f);
    drawCircle(x + 252, 122, 6);
    drawCircle(x + 282, 122, 6);
}

void drawRadarBuilding(float x, float y) {
    // Small radar building on the right sea corner
    setColor(0.28f, 0.30f, 0.35f);
    drawRect(x, y, 42, 30);
    drawRect(x + 10, y + 30, 22, 20);
    setColor(0.22f, 0.24f, 0.28f);
    drawRect(x + 4, y + 5, 34, 8);
    drawRect(x + 8, y + 14, 28, 6);
    setColor(0.68f, 0.72f, 0.78f);
    drawRect(x + 12, y + 32, 8, 8);
    drawRect(x + 22, y + 32, 8, 8);
    drawRadar(x + 21, y + 52);
}

void drawScene2()
{
    drawSky();
    drawSunMoon();
    drawStars();
    drawCloud(scene2CloudX1 + 80, 430, 22);
    drawCloud(scene2CloudX2 + 350, 450, 18);
    drawCloud(scene2CloudX1 + 600, 420, 20);

    //airplane
    glPushMatrix();
    glTranslatef(planeX, 425, 0);
    glScalef(planeScale, planeScale, 1.0f);
    glColor4f(1.0f, 1.0f, 1.0f, 0.22f);
    drawLine(-60, 13, 20, 13);
    drawLine(-40, 19, 20, 19);
    drawAirplane(0, 0);
    glPopMatrix();

   
    //buildings
    drawBuilding2(10, 240, 70, 170, 0.14f, 0.18f, 0.26f);
    drawBuilding2(90, 250, 60, 160, 0.16f, 0.18f, 0.24f);
    drawBuilding2(170, 230, 55, 180, 0.18f, 0.20f, 0.28f);
    drawBuilding2(250, 245, 50, 145, 0.15f, 0.17f, 0.22f);
    drawBuilding2(320, 235, 80, 175, 0.13f, 0.15f, 0.21f);
    drawBuilding2(420, 245, 65, 155, 0.17f, 0.18f, 0.26f);
    drawBuilding2(500, 240, 90, 170, 0.16f, 0.19f, 0.27f);
    drawBuilding2(610, 250, 55, 145, 0.14f, 0.16f, 0.22f);
    drawBuilding2(690, 230, 75, 180, 0.18f, 0.20f, 0.28f);

   
    //road
    setColor(0.40f, 0.40f, 0.45f);
    drawRect(0, 255, WIN_W, 12);
    drawRect(0, 240, WIN_W, 8);
    for (int x = 0; x <= WIN_W; x += 100) {
        drawRect(x + 8, 210, 12, 48);
    }
    setColor(0.48f, 0.48f, 0.52f);
    drawRect(0, 265, WIN_W, 4);
    glColor3f(1.0f, 0.95f, 0.6f);
    for (int x = 20; x < WIN_W; x += 70) drawRect(x, 264, 24, 3);

    //railway

    glColor3f(0.55f, 0.35f, 0.15f);
    for (int x = 0; x < WIN_W; x += 28) drawRect(x, 228, 14, 30);
    setColor(0.35f, 0.35f, 0.35f);
    drawRect(0, 232, WIN_W, 8);
    drawRect(0, 246, WIN_W, 8);
    //train
    setColor(0.75f, 0.08f, 0.08f);
    drawRect(trainX, 250, 90, 42);
    setColor(0.55f, 0.05f, 0.05f);
    drawRect(trainX + 42, 292, 38, 20);
    setColor(0.90f, 0.12f, 0.08f);
    drawRect(trainX + 8, 264, 22, 18);
    setColor(0.12f, 0.12f, 0.12f);
    drawRect(trainX + 22, 292, 12, 28);
    drawRect(trainX + 36, 300, 8, 16);
    setColor(0.95f, 0.88f, 0.45f);
    drawCircle(trainX + 5, 272, 5);
    setColor(0.25f, 0.25f, 0.28f);
    drawTriangle(trainX, 250, trainX - 18, 240, trainX + 18, 250);
    setColor(0.85f, 0.92f, 1.0f);
    drawRect(trainX + 52, 299, 18, 9);
    setColor(0.95f, 0.72f, 0.12f);
    drawRect(trainX + 8, 257, 72, 4);
    for (int i = 1; i <= 3; i++) {
        setColor(0.15f, 0.35f, 0.85f);
        drawRect(trainX + i * 95, 250, 85, 42);
        glColor3f(0.85f, 0.92f, 1.0f);
        for (int w = 0; w < 5; w++) drawRect(trainX + i * 95 + 10 + w * 14, 265, 8, 10);
    }
    glColor3f(0.08f, 0.08f, 0.08f);
    drawCircle(trainX + 22, 245, 7);
    drawCircle(trainX + 62, 245, 7);
    for (int i = 1; i <= 3; i++) {
        float carBase = trainX + i * 95;
        drawCircle(carBase + 20, 245, 6);
        drawCircle(carBase + 65, 245, 6);
    }
    setColor(0.70f, 0.70f, 0.72f);
    glLineWidth(2);
    drawLine(trainX + 22, 245, trainX + 62, 245);
    for (int i = 1; i <= 3; i++) {
        float carBase = trainX + i * 95;
        drawLine(carBase + 20, 245, carBase + 65, 245);
    }
    glLineWidth(1);
    for (int i = 0; i < 6; i++) {
        float puff = (float)i;
        glColor4f(0.72f, 0.72f, 0.72f, 0.48f - puff * 0.05f);
        drawCircle(trainX + 30 + puff * 22 + sin(degToRad(waterAnim * 8 + puff * 25)) * 4,
                   328 + puff * 8,
                   9 + puff * 2.5f);
    }

    setColor(0.18f, 0.18f, 0.18f);
    drawRect(0, 115, WIN_W, 105);

    glColor3f(1.0f, 0.9f, 0.1f);
    drawRect(0, 166, WIN_W, 3);
    drawRect(0, 172, WIN_W, 3);
    glColor3f(0.92f, 0.92f, 0.92f);
    for (int x = 0; x < WIN_W; x += 55) {
        drawRect(x, 140, 30, 3);
        drawRect(x, 195, 30, 3);
    }
    setColor(0.20f, 0.20f, 0.22f);
    drawRect(0, 115, WIN_W, 8);
    drawRect(0, 212, WIN_W, 8);

    // sidewalks
    setColor(0.45f, 0.45f, 0.47f);
    drawRect(0, 107, WIN_W, 8);
    drawRect(0, 220, WIN_W, 8);

    //fence
    
    drawFence(0, WIN_W, 220);

    //bus,car
    drawScene2Car(scene2CarX);
    drawScene2Bus(busX);
    drawFence(0, WIN_W, 105);

    

    
    //water

    drawWater(0, 100);

    drawRadarBuilding(720, 80);

    glColor4f(0.0f, 0.0f, 0.1f, 0.2f);
    drawRect(0, 0, WIN_W, 60);

   
    glPopMatrix();

    
    for (int i = 0; i < 20; i++) {
        glColor4f(1, 1, 1, 0.12f);
        drawLine(i * 45, 50 + sin((waterAnim + i) * 0.3f) * 2,
                 i * 45 + 20, 52 + sin((waterAnim + i) * 0.3f) * 2);
    }

    //boat
    glPushMatrix();
        glTranslatef(boatX, 82, 0);
        glScalef(0.72f, 0.72f, 1.0f);
        drawBoat(0, 0);
    glPopMatrix();

    //ship
    glColor4f(0.02f, 0.05f, 0.08f, 0.22f);
    drawRect(shipX + 18, 35, 105, 6);
    setColor(0.2f, 0.2f, 0.25f);
    glBegin(GL_POLYGON);
        glVertex2f(shipX, 70);
        glVertex2f(shipX + 140, 70);
        glVertex2f(shipX + 115, 45);
        glVertex2f(shipX + 20, 45);
    glEnd();
    setColor(0.12f, 0.12f, 0.16f);
    drawRect(shipX + 18, 45, 98, 7);
    setColor(0.75f, 0.10f, 0.08f);
    drawRect(shipX + 25, 42, 86, 5);
    setColor(0.08f, 0.08f, 0.11f);
    drawRect(shipX + 31, 38, 74, 5);
    setColor(0.85f, 0.85f, 0.9f);
    drawRect(shipX + 35, 70, 60, 35);
    setColor(0.70f, 0.72f, 0.78f);
    drawRect(shipX + 42, 101, 45, 8);
    setColor(0.12f, 0.32f, 0.55f);
    for (int w = 0; w < 4; w++) {
        drawRect(shipX + 42 + w * 12, 82, 7, 8);
    }
    setColor(0.95f, 0.95f, 0.92f);
    drawLine(shipX + 15, 74, shipX + 128, 74);
    for (int r = 0; r < 8; r++) {
        drawLine(shipX + 22 + r * 13, 70, shipX + 22 + r * 13, 78);
    }
    setColor(0.8f, 0.15f, 0.1f);
    drawRect(shipX + 85, 90, 15, 25);
    setColor(0.18f, 0.18f, 0.20f);
    drawRect(shipX + 82, 115, 21, 5);
    setColor(0.95f, 0.95f, 0.95f);
    drawRect(shipX + 68, 105, 3, 35);
    setColor(0.95f, 0.12f, 0.12f);
    drawTriangle(shipX + 71, 135, shipX + 96, 130, shipX + 71, 124);
    setColor(0.95f, 0.18f, 0.12f);
    drawCircleOutline(shipX + 24, 60, 6);
    drawCircleOutline(shipX + 125, 61, 6);

    //streetlight
    for (int x = 60; x < 800; x += 120) {
        setColor(0.25f, 0.25f, 0.25f);
        drawRect(x, 210, 6, 55);
        glColor3f(1.0f, 0.95f, 0.6f);
        drawCircle(x + 3, 268, 6);
    }
    //trees
    drawTree(40, 210, 0.8f);
    drawTree(620, 210, 0.8f);
}


// Animation

void update(int value) {
    if (isPaused) {
        glutPostRedisplay();
        glutTimerFunc(16, update, 0);
        return;
    }
    //clouds
    if (scene == 1) {
        cloudX1 += 0.55f;
        cloudX2 += 0.30f;
        if (cloudX1 > WIN_W + 200) cloudX1 = -250;
        if (cloudX2 > WIN_W + 200) cloudX2 = -300;
    } 
    else if (scene == 2) {
        scene2CloudX1 += 0.55f;
        scene2CloudX2 += 0.30f;
        if (scene2CloudX1 > WIN_W + 200) scene2CloudX1 = -250;
        if (scene2CloudX2 > WIN_W + 200) scene2CloudX2 = -300;
    }

    // Windmill blade rotation
    bladeAngle -= 2.0f;
    if (bladeAngle > 360.0f) bladeAngle = 0.0f;

    if (scene == 1) {
        //cloud scaling
        if (cloudX1 <= 250.0f) {
            loomingCloudScale += 0.001f; 
            if (loomingCloudScale > 2.0f) loomingCloudScale = 2.0f;
        } 
        else {
            loomingCloudScale -= 0.001f;
            if (loomingCloudScale < 0.7f) loomingCloudScale = 0.7f;
        }

        // Reset loop when the cloud goes entirely off the screen
        if (cloudX1 > WIN_W + 200) {
            cloudX1 = -250.0f;
            loomingCloudScale = 0.85f;
        }
        
        // Traffic signal
        signalTimer++;
        if (signalTimer > 133) { 
            signalGreen = !signalGreen; 
            signalTimer = 0; 
        }

        // Red car 
        float redStopLine = 392.0f;
        float redFront = carX + 68.0f;
        bool redCarApproachingSignal = redFront < redStopLine && redFront > redStopLine - 190.0f;

        if (!signalGreen && redCarApproachingSignal) {
            carSpeed -= 0.1f;
            if (carSpeed < 0.0f) carSpeed = 0.0f;
        } 
        else {
            carSpeed += 0.1f;
            if (carSpeed > 2.5f) carSpeed = 2.5f;
        }

        carX += carSpeed;
        if (!signalGreen && redCarApproachingSignal && redFront + carSpeed > redStopLine - 5.0f) {
            carX = redStopLine - 68.0f - 5.0f;
            carSpeed = 0.0f;
        }
        if (carX > WIN_W + 130) carX = -160;

        // Blue car 
        carX2 -= blueCarSpeed;
        float blueStopLine = 308.0f;
        float blueFront = carX2;
        bool blueCarApproachingSignal = blueFront > blueStopLine && blueFront < blueStopLine + 190.0f;

        if (!signalGreen && blueCarApproachingSignal) {
            blueCarSpeed -= 0.1f;
            if (blueCarSpeed < 0.0f) blueCarSpeed = 0.0f;
        } 
        else {
            blueCarSpeed += 0.1f;
            if (blueCarSpeed > 2.5f) blueCarSpeed = 2.5f;
        }

        if (!signalGreen && blueCarApproachingSignal && blueFront - blueCarSpeed < blueStopLine + 5.0f) {
            carX2 = blueStopLine + 5.0f;
            blueCarSpeed = 0.0f;
        }
        if (carX2 < -140) {
            float relativeReset = carX + 400.0f;
            carX2 = (relativeReset < WIN_W + 100.0f) ? relativeReset : WIN_W + 100.0f;
        }
    } 
    else if (scene == 2) {
        scene2CarX += 1.5f;
        if (scene2CarX > WIN_W + 130) scene2CarX = -160;
    }

    // Radar rotation
    radarAngle += 1.8f;
    if (radarAngle > 360.0f) radarAngle = 0.0f;

    // Airplane distance effect
    float planeProgress = (planeX + 220.0f) / (WIN_W + 320.0f);
    planeScale = 1.3f - planeProgress;
    if (planeScale < 0.3f) planeScale = 0.3f;
    if (planeScale > 1.3f) planeScale = 1.3f;
    planeX += 3.5f;
    if (planeX > WIN_W + 100) planeX = -220.0f;

    trainX -= 2.2f;
    if (trainX < -420.0f) trainX = WIN_W + 220.0f;

    coastalTrainX += 2.0f;
    if (coastalTrainX > WIN_W + 120.0f) coastalTrainX = -520.0f;

    busX += 1.8f;
    if (busX > WIN_W + 120) busX = -180.0f;

    if (scene == 2) {
        radarStopTimer++;
        if (!radarStopActive && radarStopTimer >= 233) {
            radarStopActive = true;
            radarStopTimer = 0;
        }
        if (radarStopActive && radarStopTimer >= 33) {
            radarStopActive = false;
            radarStopTimer = 0;
        }
        if (!radarStopActive) {
            shipX += scene2ShipSpeed;
        }
        if (shipX > WIN_W + 160) shipX = -220.0f;
    } 
    else {
        shipX += 1.6f;
        if (shipX > WIN_W + 160) shipX = -220.0f;
    }

    // Boat
    boatX += 0.5f;
    if (boatX > WIN_W + 150) boatX = -170;

    //water
    waterAnim += 0.4f;
    if (waterAnim > 60) waterAnim = 0;

    //birds
    birdOffset = 12.0f;
    
    //star
    starPulseAngle += 0.1f;

    //rain
    rainOffset += 9.0f;
    if (rainOffset > 36.0f) rainOffset = 0.0f;


    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

// Input

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case '1': scene = 1; break;
        case '2': scene = 2; break;
        /* scene 3 removed */
        case 'r': case 'R': weatherMode = RAIN;  break;
        case 'c': case 'C': weatherMode = CLEAR; break;
        case 'd': case 'D': isDay = true; break;
        case 'n': case 'N': isDay = false; break;
        case 27: exit(0);
    }
}

void mouse(int button, int state, int x, int y) {

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        isDay = !isDay;
    }   
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        isDay = !isDay;
    }
    
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        isPaused = !isPaused; 
    }
    
    
}

// Display

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    if      (scene == 1) drawScene1();
    else if (scene == 2) drawScene2();

    drawWeather();

    glutSwapBuffers();
}

void init() {
    system("echo HELLO FROM PROGRAM");
    cout << "OPENGL PROJECT CONTROLS:\n"<<flush;
    cout << "Keyboard Controls:\n";
    cout << "1  -> Scene 1\n";
    cout << "2  -> Scene 2\n";
    cout << "D  -> Day Mode\n";
    cout << "N  -> Night Mode\n";
    cout << "R  -> Rain Weather\n";
    
    cout << "C  -> Clear Weather\n";
    cout << "ESC -> Exit Program\n\n";

    cout << "Mouse Controls:\n";
    cout << "Left Click  -> Day/Night Mode\n";
    cout << "Right Click -> Stop Animation\n";

    glClearColor(0, 0, 0, 1);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIN_W, 0, WIN_H);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    srand((unsigned int)time(0));
    initSnow();

}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WIN_W, WIN_H);
    glutCreateWindow("Computer Graphics Project - 23-51897-2");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutTimerFunc(0, update, 0);




    glutMainLoop();
    return 0;
}
