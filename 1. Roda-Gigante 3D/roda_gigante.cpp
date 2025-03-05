#define GL_SILENCE_DEPRECATION
#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Variáveis globais para controle da câmera e animação
GLfloat cameraAngleX = 0.0f;
GLfloat cameraAngleY = 0.0f;
GLfloat cameraDistance = 10.0f;
GLfloat wheelRotation = 0.0f;
GLfloat rotationSpeed = 1.0f;  // Velocidade de rotação
bool isRotating = true;

// Parâmetros de iluminação
GLfloat light0_pos[] = {5.0f, 5.0f, 5.0f, 1.0f};
GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat red[] = {1.0f, 0.0f, 0.0f, 1.0f};

// Função para configurar a iluminação
void setupLighting() {
    glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, white);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}

// Função para desenhar uma esfera
void drawSphere(GLfloat radius, GLint slices, GLint stacks) {
    glutSolidSphere(radius, slices, stacks);
}

// Função para desenhar um cubo (cadeirinha) com cor personalizada
void drawSeat(float r, float g, float b) {
    glDisable(GL_LIGHTING);
    glPushMatrix();
    glScalef(0.2f, 0.1f, 0.1f);
    glColor3f(r, g, b);  // Usando os valores passados para cor
    glutSolidCube(1.0f);
    glPopMatrix();
    glEnable(GL_LIGHTING); 
}


void drawFerrisWheel() {
    glDisable(GL_LIGHTING);
    glColor3f(0.3f, 0.3f, 0.3f); // Cinza escuro para a estrutura
    glPushMatrix();

    // Desenha as linhas fixas do centro da roda até a base
    glPushMatrix();
    glLineWidth(3.0f); // Define a espessura da linha
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);  // Cor da linha
    glVertex3f(0.0f, 0.0f, 0.0f);  // Centro da roda
    glVertex3f(1.25f, -2.0f, 0.0f); // Ponto à direita (no chão)
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glLineWidth(3.0f); // Define a espessura da linha
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);  // Cor da linha
    glVertex3f(0.0f, 0.0f, 0.0f);  // Centro da roda
    glVertex3f(-1.25f, -2.0f, 0.0f); // Ponto à esquerda (no chão)
    glEnd();
    glPopMatrix();

    glRotatef(90, 1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, 0.0f);  // Ajustando a posição da esfera
    drawSphere(0.1, 20, 20);  // Desenhando uma esfera pequena
    glPopMatrix();

    glPushMatrix();
    glRotatef(wheelRotation, 0.0f, 0.0f, 1.0f);
    glColor3f(0.2f, 0.2f, 0.2f); // Cinza escuro para a roda
    glutSolidTorus(0.05, 1.5, 20, 20);

    // Lista de cores para as cadeirinhas
    float colors[8][3] = {
        {1.0f, 0.0f, 0.0f}, // Vermelho
        {0.0f, 1.0f, 0.0f}, // Verde
        {0.0f, 0.0f, 1.0f}, // Azul
        {1.0f, 1.0f, 0.0f}, // Amarelo
        {1.0f, 0.5f, 0.0f}, // Laranja
        {0.5f, 0.0f, 0.5f}, // Roxo
        {0.0f, 1.0f, 1.0f}, // Ciano
        {1.0f, 0.0f, 1.0f}  // Magenta
    };

    for (int i = 0; i < 8; i++) {
        glPushMatrix();
        glRotatef(45 * i, 0.0f, 0.0f, 1.0f);
        glTranslatef(1.5f, 0.0f, 0.0f);
        
        // Desenhando a linha do centro até a cadeirinha
        glBegin(GL_LINES);
        glColor3f(0.0f, 0.0f, 0.0f);  // Cor da linha
        glVertex3f(-2.0f, 0.0f, 0.0f);  // Centro da roda
        glVertex3f(0.0f, 0.0f, 0.0f);  // Posição da cadeirinha
        glEnd();

        // Passa a cor para a função drawSeat
        drawSeat(colors[i][0], colors[i][1], colors[i][2]);

        glPopMatrix();
    }

    glPopMatrix();
    glEnable(GL_LIGHTING); 
}


// Função para desenhar o chão
void drawGround() {
    glDisable(GL_LIGHTING);  // Desativa iluminação para o chão
    glColor3f(0.0f, 1.0f, 0.0f);

    glPushMatrix();
    glTranslatef(0.0f, -2.0f, 0.0f);
    glScalef(5.0f, 0.1f, 5.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glEnable(GL_LIGHTING);  // Reativa iluminação para o restante da cena
}


// Função de renderização
void display() {
    glClearColor(0.7f, 0.9f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(cameraDistance * cos(cameraAngleY) * cos(cameraAngleX),
              cameraDistance * sin(cameraAngleX),
              cameraDistance * sin(cameraAngleY) * cos(cameraAngleX),
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    setupLighting();
    drawGround();
    drawFerrisWheel();

    glutSwapBuffers();
}

// Função para atualizar a animação
void update(int value) {
    if (isRotating) {
        wheelRotation += rotationSpeed;
        if (wheelRotation > 360.0f) wheelRotation -= 360.0f;
    }
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

// Função para redimensionar a janela
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
}

// Função de interação com o teclado
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': 
            cameraDistance -= 0.5f;
            break;
        case 's': 
            cameraDistance += 0.5f;
            break;
        case ' ': 
            isRotating = !isRotating;
            break;
        case 'x': 
            rotationSpeed += 0.5f;
            if (rotationSpeed > 10.0f) rotationSpeed = 10.0f;
            break;
        case 'z': 
            rotationSpeed -= 0.5f;
            if (rotationSpeed < 0.1f) rotationSpeed = 0.1f;
            break;
        case 27:
            exit(0);
            break;
    }
    glutPostRedisplay();
}

// Função para interação com o mouse
void mouseMotion(int x, int y) {
    static int lastX = x, lastY = y;
    cameraAngleX += (y - lastY) * 0.01f;
    cameraAngleY += (x - lastX) * 0.01f;
    lastX = x;
    lastY = y;
    glutPostRedisplay();
}

// Função principal
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Roda-Gigante 3D");

    

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMotionFunc(mouseMotion);
    glutTimerFunc(16, update, 0);

    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
