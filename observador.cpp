#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "observador.h"
#include <cmath>
/*
//atribui o vaor de x, y e z para vet
void setVetor(float * vet, float * x, float * y, float * z){
    vet[0] = x;
    vet[1] = y;
    vet[2] = z;
}*/

//inicializa o vetor com os valores passados por parametro
void setVetor(float * vet, float x, float y, float z){
    vet[0] = x;
    vet[1] = y;
    vet[2] = z;
}

//soma v2 a v1
void somaVet(float * vet1, float * vet2){
    vet1[0] += vet2[0];
    vet1[1] += vet2[1];
    vet1[2] += vet2[2];
}

//copia v2 em v1
void copiaVet(float * recebe, float * atribui){
    recebe[0] = atribui[0];
    recebe[1] = atribui[1];
    recebe[2] = atribui[2];
}

//mutiplica um vetor por um fator
void multVet(float * vet1, float fator){
    vet1[0] = vet1[0] * fator;
    vet1[1] = vet1[1] * fator;
    vet1[2] = vet1[2] * fator;
}

//encontra a magnitudo vetor
float magnVet(float * vet){
    return sqrt( vet[0] * vet[0] + vet[1] * vet[1] + vet[2] * vet[2]);
}

//normaliza um vetor para magnitude 1
void normalizaVet(float * vet){
    multVet(vet, 1/magnVet(vet));
}

//rotaciona matrix
void rotacionaMat(float * mat, float * eixoVet, float angulo){
    //https://pt.wikipedia.org/wiki/Matriz_de_rota%C3%A7%C3%A3o
    float cosseno = cos(angulo);
    float subCoss = 1 - cosseno;
    float seno = sin(angulo);

    mat[0]= cosseno + subCoss*eixoVet[0]*eixoVet[0];
    mat[1]= subCoss * eixoVet[1] * eixoVet[0] - seno * eixoVet[2];
    mat[2]= subCoss * eixoVet[2] * eixoVet[0] + seno * eixoVet[1];

    mat[3]= subCoss * eixoVet[0] * eixoVet[1] + seno * eixoVet[2];
    mat[4]= cosseno + subCoss * eixoVet[1] * eixoVet[1];
    mat[5]= subCoss * eixoVet[2] * eixoVet[1] - seno * eixoVet[0];

    mat[6]= subCoss * eixoVet[0] * eixoVet[2] - seno * eixoVet[1];
    mat[7]= subCoss * eixoVet[1] * eixoVet[2] + seno * eixoVet[0];
    mat[8]= cosseno + subCoss * eixoVet[2] * eixoVet[2];
}

//multiplica v1 por uma matriz e coloca em v2
void multVetMat(float * v1, float * mat, float * v2){
    v2[0]= v1[0] * mat[0] + v1[1] * mat[1] + v1[2] * mat[2];
    v2[1]= v1[0] * mat[3] + v1[1] * mat[4] + v1[2] * mat[5];
    v2[2]= v1[0] * mat[6] + v1[1] * mat[7] + v1[2] * mat[8];
}

//rotaciona v1 em torno de v2 por um angulo e armazena em v3
void rotacionaVet(float * v1, float * v2, float angulo, float * v3){
    //matriz de rotaçao
    float mat[16];
    rotacionaMat(mat, v2, angulo);

    //multiplica o vetor pela matriz obitida
    multVetMat(v1, mat, v3);
}

//Construtor
Observador::Observador()
{
    //inicializa os valores da rotação e do deslocamento
    deslocamento = 0.005f;
    rotacao = 0.01f;
    //Inicializa os vetores com as coordenados do observador
    //Esses valores são aleatórios
    setVetor(posicaoObs,0.764331460f, -1.66760659f, 0.642456770);
    setVetor(frenteObs, -0.398769796f, 0.763009906f, -0.508720219f);
    setVetor(direitaObs, 0.886262059f, 0.463184059f, 0.000000000f);
    setVetor(upObs, -0.235630989f, 0.450859368f, 0.860931039f);
}

//transformação da visualização da cena
void Observador::setOrientacao(){
    //define a transformação de visualização
    gluLookAt(0,0,0,frenteObs[0], frenteObs[1], frenteObs[2], upObs[0], upObs[1], upObs[2]);
}

//funçao para mudar a orientaçao do observador
void Observador::mudaOrientacao(float *ponto){
    float temp[3];
    float up[3] = {0.0f, 0.0f, 1.0f};//eixo z

    //primeiro mudamos a orientaçao do observador
    frenteObs[0] = ponto[0] - posicaoObs[0];
    frenteObs[1] = ponto[1] - posicaoObs[1];
    frenteObs[2] = ponto[2] - posicaoObs[2];

    //naormalizamos o vetor calculado para frenteObs
    normalizaVet(frenteObs);

    //agora rotacionamos o frenteObs em -pi/2 em torno do eixo z
    rotacionaVet(frenteObs, up, -1.57079632679f, temp);

    //remove y para
    temp[2] = 0;

    //nomalizamos temp
    normalizaVet(temp);

    //e atribui-o a direitaObs
    copiaVet(direitaObs, temp);

    //por ultimo rotacionamos o vetor frenteObs em pi/2 em torno do direitaObs
    rotacionaVet(frenteObs, direitaObs, 1.57079632679f, temp);
    copiaVet(upObs, temp);
}

/**Comentar melhor*/
//move observador para frente
void Observador::frente(){
    float vet[3];

    copiaVet(vet, frenteObs);
    multVet(vet, deslocamento);

    somaVet(posicaoObs, vet);
}

//move observador para trás
void Observador::tras(){
    float vet[3];

    copiaVet(vet, frenteObs);
    multVet(vet, -deslocamento);

    somaVet(posicaoObs, vet);
}

//move observador para esquerda
void Observador::esquerda(){
    float vet[3];

    copiaVet(vet, direitaObs);
    multVet(vet, -deslocamento);

    somaVet(posicaoObs, vet);
}

//move observador para direita
void Observador::direita(){
    float vet[3];

    copiaVet(vet, direitaObs;
    multVet(vet, deslocamento);

    somaVet(posicaoObs, vet);
}



























