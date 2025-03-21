#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

float angle = 0.0, deltaAngle = 0.0, ratio;
float x = 0.0f, y = 1.75f, z = 15.0f; 
float lx = 0.0f, ly = 0.0f, lz = -1.0f;
int deltaMove = 0, deltaYMove = 0, h, w;

void Reshape(int w1, int h1) {
    if (h1 == 0) h1 = 1;
    w = w1;
    h = h1;
    ratio = 1.0f * w / h;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45, ratio, 0.1, 1000);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
}

void orientMe(float ang) {
    lx = sin(ang);
    lz = -cos(ang);
    glLoadIdentity();
    gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
}

void moveMeFlat(int i) {
    x = x + i * lx * 0.01;
    z = z + i * lz * 0.01;
    glLoadIdentity();
    gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
}

void moveMeVertical(int i) {
    y += i * 0.01;
    glLoadIdentity();
    gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
}

void Grid() {
    double i;
    const float Z_MIN = -50, Z_MAX = 50;
    const float X_MIN = -50, X_MAX = 50;
    const float gap = 1.5;
    
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_LINES);
    for (i = Z_MIN; i < Z_MAX; i += gap) {
        glVertex3f(i, 0, Z_MIN);
        glVertex3f(i, 0, Z_MAX);
    }
    for (i = X_MIN; i < X_MAX; i += gap) {
        glVertex3f(X_MIN, 0, i);
        glVertex3f(X_MAX, 0, i);
    }
    glEnd();
}

void KotakKayu() { 
    for (int i = 0; i < 6; i++) {
        glPushMatrix();
        switch (i) {
            case 0: glColor3f(0.0f, 1.0f, 1.0f); glTranslatef(0, 0, 3); break; // Front
            case 1: glColor3f(1.0f, 0.0f, 1.0f); glRotated(-90, 1, 0, 0); glTranslatef(0, 0, 3); break; // Top
            case 2: glColor3f(1.0f, 1.0f, 0.0f); glRotated(180, 1, 0, 0); glTranslatef(0, 0, 3); break; // Back
            case 3: glColor3f(1.0f, 0.0f, 0.0f); glRotated(90, 1, 0, 0); glTranslatef(0, 0, 3); break; // Bottom
            case 4: glColor3f(0.0f, 1.0f, 0.0f); glRotated(-90, 0, 1, 0); glTranslatef(0, 0, 3); break; // Left
            case 5: glColor3f(0.0f, 0.0f, 1.0f); glRotated(90, 0, 1, 0); glTranslatef(0, 0, 3); break; // Right
        }
        glBegin(GL_QUADS);
        glVertex3f(-3.0f, -3.0f, 0.0f);
        glVertex3f(3.0f, -3.0f, 0.0f);
        glVertex3f(3.0f, 3.0f, 0.0f);
        glVertex3f(-3.0f, 3.0f, 0.0f);
        glEnd();
        glPopMatrix();
    }
}

void display() {
    if (deltaMove) moveMeFlat(deltaMove);
    if(deltaYMove) moveMeVertical(deltaYMove);
    if (deltaAngle) {
        angle += deltaAngle;
        orientMe(angle);
    }
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    Grid();
    KotakKayu();
    
    glutSwapBuffers();
    glFlush();
}

void lighting() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    
    const GLfloat light_position[] = {0.0f, 20.0f, 10.0f, 1.0f};
    const GLfloat light_ambient[] = {0.5f, 0.5f, 0.5f, 1.0f};
    const GLfloat light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    const GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
}

void init(void) {
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void pressSpecialKey(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT: deltaAngle = -0.0005f; break;
        case GLUT_KEY_RIGHT: deltaAngle = 0.0005f; break;
        case GLUT_KEY_UP: deltaMove = 1; break;
        case GLUT_KEY_DOWN: deltaMove = -1; break;
    }
}

void releaseSpecialKey(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT: if (deltaAngle < 0.0f) deltaAngle = 0.0f; break;
        case GLUT_KEY_RIGHT: if (deltaAngle > 0.0f) deltaAngle = 0.0f; break;
        case GLUT_KEY_UP: if (deltaMove > 0) deltaMove = 0; break;
        case GLUT_KEY_DOWN: if (deltaMove < 0) deltaMove = 0; break;
    }
}

void pressKey(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': deltaYMove = 1; break;
        case 's': deltaYMove = -1; break;
    }
}

void releaseKey(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': if (deltaYMove > 0) deltaYMove = 0; break;
        case 's': if (deltaYMove < 0) deltaYMove = 0; break;
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Kubus 3D Lighting");

    glutIgnoreKeyRepeat(1);
    glutSpecialFunc(pressSpecialKey);
    glutSpecialUpFunc(releaseSpecialKey);
    glutKeyboardFunc(pressKey);        
    glutKeyboardUpFunc(releaseKey);   
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(Reshape);

    lighting();
    init();

    glutMainLoop();
    return 0;
}


