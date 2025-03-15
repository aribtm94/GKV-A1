#include <GL/glut.h>

// Sudut untuk setiap sendi
static int shoulder = 0, elbow = 0, geser = 0, hand = 0;
static int finger1 = 20, finger2 = 15, finger3 = 10, finger4 = 15, finger5 = 20;

// Fungsi inisialisasi
void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0); // Mengatur warna latar belakang menjadi hitam
    glShadeModel(GL_FLAT);
}

// Fungsi untuk menggambar jari
void drawFinger(float xOffset, float zOffset, int angle) {
    glPushMatrix();
    glTranslatef(xOffset, 0.25, zOffset);
    glRotatef((GLfloat)angle, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 0.15, 0.0);
    glPushMatrix();
    glScalef(0.15, 0.6, 0.1);
    glutWireCube(1.0);
    glPopMatrix();
    glPopMatrix();
}

// Fungsi untuk menggambar tampilan
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    
    // Transformasi bahu
    glTranslatef(-1.0 , 0.0, 0.0);
    glRotatef((GLfloat)shoulder, 0.0 + GLfloat(geser), 0.0, 1.0);
    glTranslatef(1.0 , 0.0, 0.0);
    
    // Menggambar lengan atas
    glPushMatrix();
    glScalef(2.0, 0.4, 1.0);
    glutWireCube(1.0);
    glPopMatrix();
    
    // Transformasi siku
    glTranslatef(1.0 , 0.0, 0.0);
    glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    
    // Menggambar lengan bawah
    glPushMatrix();
    glScalef(2.0, 0.4, 1.0);
    glutWireCube(1.0);
    glPopMatrix();

    // Transformasi tangan
    glTranslatef(1.0 , 0.0, 0.0);
    glRotatef((GLfloat)hand, 0.0, 0.0, 1.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glTranslatef(0.0, 0.0, 0.0);
    
    // Menggambar bagian tangan yang lebih besar
    glPushMatrix();
    glScalef(1.2, 0.5, 0.8);
    glutWireCube(1.0);
    glPopMatrix();

    // Menggambar jari-jari di depan tangan
    drawFinger(-0.3, 0.2, finger1);
    drawFinger(-0.15, 0.25, finger2);
    drawFinger(0.0, 0.3, finger3);
    drawFinger(0.15, 0.25, finger4);
    drawFinger(0.3, 0.2, finger5);
    
    glPopMatrix();
    glutSwapBuffers();
}

// Fungsi untuk menangani perubahan ukuran jendela
void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
}

// Fungsi untuk menangani input keyboard
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 's': shoulder = (shoulder + 5) % 360; break;
        case 'S': shoulder = (shoulder - 5) % 360; break;
        case 'e': elbow = (elbow + 5) % 360; break;
        case 'E': elbow = (elbow - 5) % 360; break;
        case 'a': geser = (geser + 5) % 360; break;
        case 'A': geser = (geser - 5) % 360; break;
        case 'd': hand = (hand + 5) % 100; break;
        case 'D': hand = (hand - 5) % 100; break;
        case '1': finger1 = (finger1 + 5) % 90; break;
        case '!': finger1 = (finger1 - 5) % 90; break;
        case '2': finger2 = (finger2 + 5) % 90; break;
        case '@': finger2 = (finger2 - 5) % 90; break;
        case '3': finger3 = (finger3 + 5) % 90; break;
        case '#': finger3 = (finger3 - 5) % 90; break;
        case '4': finger4 = (finger4 + 5) % 90; break;
        case '$': finger4 = (finger4 - 5) % 90; break;
        case '5': finger5 = (finger5 + 5) % 90; break;
        case '%': finger5 = (finger5 - 5) % 90; break;
        case 27: exit(0); break; // Keluar saat tombol ESC ditekan
        default: return;
    }
    glutPostRedisplay();
}

// Fungsi utama
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Lengan Robot dengan Jari");
    
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    
    return 0;
}

