#define GL_SILENCE_DEPRECATION

#include <GLFW/glfw3.h>
#include <math.h>

void desenhaQuadrado(float largura, float altura, float r, float g, float b) {
    glColor3f(r, g, b); 
    glBegin(GL_QUADS);
    glVertex2f(-largura / 2, 0.0f);       // Inferior esquerdo
    glVertex2f(largura / 2, 0.0f);        // Inferior direito
    glVertex2f(largura / 2, altura);      // Superior direito
    glVertex2f(-largura / 2, altura);     // Superior esquerdo
    glEnd();
}

void desenhaCirculo(float x, float y, float raio)  // pra tentar fazer as "articulações"
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float angulo = i * (3.14159f / 180.0f);
        float dx = cos(angulo) * raio;
        float dy = sin(angulo) * raio;
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

int main() {
    // Inicialização do GLFW
    if (!glfwInit()) {
        return -1;
    }

    // Configuração da janela
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    GLFWwindow* window = glfwCreateWindow(800, 800, "Braço Mecânico", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);

    // Loop principal
    while (!glfwWindowShouldClose(window)) {
        // Limpa a tela
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // Base fixa
        glPushMatrix();
        glTranslatef(0.0f, -0.5f, 0.0f);  // Posição fixa na base da tela
        desenhaQuadrado(0.2f, 0.1f, 1.0f, 1.0f, 0.0f); // Base amarelaaa
        glPopMatrix();
    
        // Movimento oscilante do braço inferior
        float anguloInferior = sin(glfwGetTime()) * 60.0f; 

        glPushMatrix();
        glTranslatef(0.0f, -0.4f, 0.0f);   // Alinhado ao topo da base
        glRotatef(anguloInferior, 0.0f, 0.0f, 1.0f); // Rotação do braço inferior
        
        desenhaQuadrado(0.1f, 0.4f, 0.52f, 0.81f, 0.98f); // Braço inferior azul 

        // Articulação inferior
        glColor3f(1.0f, 1.0f, 1.0f);  // Cor branca
        desenhaCirculo(0.0f, 0.4f, 0.05f);  

        // Movimento oscilante do braço superior
        float anguloSuperior = sin(glfwGetTime() * 2) * 60.0f; 
        glTranslatef(0.0f, 0.4f, 0.0f); // Alinhado ao topo do braço inferior
        glRotatef(anguloSuperior, 0.0f, 0.0f, 1.0f); // Rotação do braço superior
        desenhaQuadrado(0.1f, 0.3f, 1.0f, 0.41f, 0.69f); // Braço superior rosinha claro

        // Articulação superior
        glColor3f(1.0f, 1.0f, 1.0f);
        desenhaCirculo(0.0f, 0.4f, 0.05f);  

        glPopMatrix();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Finalizando o GLFW
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
