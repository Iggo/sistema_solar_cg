#include <QApplication>
#include <GL/glut.h>
#include <GL/glu.h>
#include <observador.h>

struct obs{
    bool frente, tras, esquerda, direita, viraEsquerda, viraDireita, giraCima, giraBaixo, rotacionaDireita, rotacionaEsquerda;
}obs;

Observador obeservador;

// Função callback chamada para fazer o desenho
void Desenha(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //Limpa a janela de visualização com a cor de fundo especificada

    if (obs.frente) obeservador.frente();		if (obs.tras) obeservador.tras();
    if (obs.esquerda) obeservador.esquerda();			if (obs.direita) obeservador.direita();
    if (obs.viraEsquerda) obeservador.viraEsquerda();		if (obs.rotacionaDireita) obeservador.rotacionaDireita();
    if (obs.rotacionaEsquerda) obeservador.rotacionaEsquerda();	if (obs.rotacionaDireita) obeservador.rotacionaDireita();
    if (obs.giraCima) obeservador.giraCima();		if (obs.giraBaixo) obeservador.giraBaixo();

    glClear(GL_COLOR_BUFFER_BIT);

    // Especifica que a cor corrente é vermelha
    //         R     G     B
    glColor3f(1.0f, 0.0f, 0.0f);

    // Desenha um quadrado preenchido com a cor corrente
         glBegin(GL_QUADS);
                   glVertex2i(100,150);
                   glVertex2i(100,100);
                   // Especifica que a cor corrente é azul
                   glColor3f(0.0f, 0.0f, 1.0f);
                   glVertex2i(150,100);
                   glVertex2i(150,150);
         glEnd();

    //Executa os comandos OpenGL
    glFlush();
}

// Inicializa parâmetros de rendering
void Inicializa (void)
{
    // Define a cor de fundo da janela de visualização como preta
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
                   // Evita a divisao por zero
                   if(h == 0) h = 1;

                   // Especifica as dimensões da Viewport
                   glViewport(0, 0, w, h);

                   // Inicializa o sistema de coordenadas
                   glMatrixMode(GL_PROJECTION);
                   glLoadIdentity();

                   // Estabelece a janela de seleção (left, right, bottom, top)
                   if (w <= h)
                           gluOrtho2D (0.0f, 250.0f, 0.0f, 250.0f*h/w);
                   else
                           gluOrtho2D (0.0f, 250.0f*w/h, 0.0f, 250.0f);
}

void keyDown(unsigned char key, int x, int y)
{
    switch (key)
    {

        // these are all camera controls
    case 'w':
        obs.frente = true;
        break;
    case 's':
        obs.tras = true;
        break;
    case 'a':
        obs.esquerda = true;
        break;
    case 'd':
        obs.direita = true;
        break;
    case 'l':
        obs.rotacionaDireita = true;
        break;
    case 'j':
        obs.rotacionaEsquerda = true;
        break;
    case 'i':
        obs.giraBaixo = true;
        break;
    case 'k':
        obs.giraCima = true;
        break;
    case 'q':
        obs.viraEsquerda = true;
        break;
    case 'e':
        obs.viraDireita = true;
        break;
    }

}

void keyUp(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
        obs.frente = false;
        break;
    case 's':
        obs.tras = false;
        break;
    case 'a':
        obs.esquerda = false;
        break;
    case 'd':
        obs.direita = false;
        break;
    case 'l':
        obs.rotacionaDireita = false;
        break;
    case 'j':
        obs.rotacionaEsquerda = false;
        break;
    case 'i':
        obs.giraBaixo = false;
        break;
    case 'k':
        obs.giraCima = false;
        break;
    case 'q':
        obs.viraEsquerda = false;
        break;
    case 'e':
        obs.viraDireita = false;
        break;
    }
}


// Programa Principal
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Sistema Solar");
    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
    Inicializa();
    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);
    glutMainLoop();
    return a.exec();
}
