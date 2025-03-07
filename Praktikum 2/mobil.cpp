
#include <GL/glut.h>
#include <math.h>
#define PI 3.1415926535898

void lingkaran(GLfloat x, GLfloat y, GLfloat radius, int circle_points) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= circle_points; i++) {
        float angle = 2.0f * PI * i / circle_points;
        glVertex2f(x + radius * cos(angle), y + radius * sin(angle));
    }
    glEnd();
}

void mobil(float x, float y, float r, float g, float b, float pr, float pg, float pb) {
    glPushMatrix();
    glTranslatef(x, y, 0);

    // Badan mobil
    glBegin(GL_POLYGON);
    glColor3f(r * 1.1, g * 1.1, b * 1.1);
    glVertex2f(-0.40, -0.10);
    glColor3f(r, g, b);
    glVertex2f(0.40, -0.10);
    glVertex2f(0.45, 0.05);
    glVertex2f(0.30, 0.20);
    glVertex2f(-0.30, 0.20);
    glVertex2f(-0.45, 0.05);
    glEnd();

    // Atap mobil
    glColor3f(r * 0.7, g * 0.7, b * 0.7);
    glBegin(GL_POLYGON);
    glVertex2f(-0.22, 0.20);
    glVertex2f(0.22, 0.20);
    glVertex2f(0.18, 0.30);
    glVertex2f(-0.18, 0.30);
    glEnd();

    // Pintu kiri
    glColor3f(pr, pg, pb);
    glBegin(GL_POLYGON);
    glVertex2f(-0.22, -0.10);
    glVertex2f(-0.05, -0.10);
    glVertex2f(-0.05, 0.18);
    glVertex2f(-0.22, 0.18);
    glEnd();
    
    // Pintu kanan
    glBegin(GL_POLYGON);
    glVertex2f(0.05, -0.10);
    glVertex2f(0.22, -0.10);
    glVertex2f(0.22, 0.18);
    glVertex2f(0.05, 0.18);
    glEnd();

    // Jendela kiri
    glColor3f(0.52f, 0.80f, 0.92f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.20, 0.05);
    glVertex2f(-0.07, 0.05);
    glVertex2f(-0.07, 0.16);
    glVertex2f(-0.20, 0.16);
    glEnd();
    
    // Jendela kanan
    glBegin(GL_POLYGON);
    glVertex2f(0.07, 0.05);
    glVertex2f(0.20, 0.05);
    glVertex2f(0.20, 0.16);
    glVertex2f(0.07, 0.16);
    glEnd();

    // Gagang pintu kiri
    glColor3f(0.8f, 0.8f, 0.8f);
    glRectf(-0.15, 0.02, -0.13, 0.04);
    
    // Gagang pintu kanan
    glRectf(0.13, 0.02, 0.15, 0.04);

    // Roda kiri
    glColor3f(0.0f, 0.0f, 0.0f);
    lingkaran(-0.28, -0.10, 0.09, 50);
    glColor3f(1.0f, 1.0f, 1.0f);
    lingkaran(-0.28, -0.10, 0.04, 10);

    // Roda kanan
    glColor3f(0.0f, 0.0f, 0.0f);
    lingkaran(0.28, -0.10, 0.09, 50);
    glColor3f(1.0f, 1.0f, 1.0f);
    lingkaran(0.28, -0.10, 0.04, 10);

    glPopMatrix();
}

void fullobjek(void) {
    glClearColor(0.05f, 0.05f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Bulan
    glPushMatrix();
    glColor3f(0.8f, 0.8f, 0.8f);
    lingkaran(0.7, 0.7, 0.1, 100);
    glColor3f(0.6f, 0.6f, 0.6f);
    lingkaran(0.73, 0.73, 0.03, 20);
    lingkaran(0.68, 0.66, 0.02, 15);
    lingkaran(0.72, 0.68, 0.01, 10);
    glPopMatrix();

    // Jalan
    glPushMatrix();
    glColor3f(0.1f, 0.1f, 0.1f);
    glRectf(-1.0, -1.0, 1.0, 0.0);
    glPopMatrix();

    // Gunung kiri
    glPushMatrix();
    glColor3f(0.1f, 0.3f, 0.1f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-1.0f, 0.0f);
    glVertex2f(-0.4f, 0.5f);
    glVertex2f(0.2f, 0.0f);
    glEnd();
    glPopMatrix();

    // Gunung kanan
    glPushMatrix();
    glColor3f(0.1f, 0.3f, 0.1f);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.6f, 0.5f);
    glVertex2f(1.0f, 0.0f);
    glEnd();
    glPopMatrix();

    // Mobil
    mobil(-0.5f, -0.6f, 0.7f, 0.0f, 0.0f, 1.0f, 0.5f, 0.5f);
    mobil(0.5f, -0.6f, 0.0f, 0.0f, 0.7f, 0.5f, 0.5f, 1.0f);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1600, 900);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Tugas Praktikum Pertemuan 2");
    glutDisplayFunc(fullobjek);
    glutMainLoop();
    return 0;
}
