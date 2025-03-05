#define GL_SILENCE_DEPRECATION
#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Variáveis globais para controle
float movimentoX = 0.0f;
bool direcaoX = true;
float movimentoY = 0.0f;
bool direcaoY = true;
float escala = 1.0f;
bool aumentando = true;

void myInit(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

void desenhaTriangulo() {
    glBegin(GL_TRIANGLES);
        glVertex2i(0, 50);
        glVertex2i(50, -50);
        glVertex2i(-50, -50);
    glEnd();
}

void desenhaLinhaEixos() {
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
        glVertex2i(-300, 0);
        glVertex2i(300, 0);
        glVertex2i(0, -300);
        glVertex2i(0, 300);
    glEnd();
}

void myDisplay(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-300, 300, -300, 300);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    desenhaLinhaEixos();
    
    // fixo
    glColor3f(1.0f, 0.0f, 1.0f);
    glPushMatrix();
    glTranslatef(-150, 150, 0);
    desenhaTriangulo();
    glPopMatrix();
    
    // movendo horizontalmente 
    glPushMatrix();
    glTranslatef(150 + movimentoX, 150, 0);
    desenhaTriangulo();
    glPopMatrix();
    
    // movendo verticalmente 
    glPushMatrix();
    glTranslatef(-150, -150 + movimentoY, 0);
    desenhaTriangulo();
    glPopMatrix();
    
    // aumentando e diminuindo 
    glPushMatrix();
    glTranslatef(150, -150, 0);
    glScalef(escala, escala, 1.0f);
    desenhaTriangulo();
    glPopMatrix();
    
    glutSwapBuffers();
}

void atualiza(int valor) {
    // Movimento horizontal
    if (direcaoX) {
        movimentoX += 5.0f;
        if (movimentoX > 50.0f) direcaoX = false;
    } else {
        movimentoX -= 5.0f;
        if (movimentoX < -50.0f) direcaoX = true;
    }
    
    // Movimento vertical
    if (direcaoY) {
        movimentoY += 5.0f;
        if (movimentoY > 50.0f) direcaoY = false;
    } else {
        movimentoY -= 5.0f;
        if (movimentoY < -50.0f) direcaoY = true;
    }
    
    // Zoom in/out
    if (aumentando) {
        escala += 0.05f;
        if (escala > 1.5f) aumentando = false;
    } else {
        escala -= 0.05f;
        if (escala < 0.5f) aumentando = true;
    }
    
    glutPostRedisplay();
    glutTimerFunc(50, atualiza, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(150, 150);
    glutCreateWindow("Transformacoes 2D");
    
    myInit();
    
    glutDisplayFunc(myDisplay);
    glutTimerFunc(50, atualiza, 0);
    
    glutMainLoop();
}
