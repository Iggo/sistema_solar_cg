#include "observador.h"

Observador::Observador()
{
}

//configura a posiçao do observador de acordo com os valores definidos
void setPosicao(void);

//inicializa o vetor com os valores passados por parametro
void setVetor(float * vet, float x, float y, float z);

//soma dois vetores
void somaVet(float * vet1, float vet2);

//copia vetor
void copiaVet(float * vet1, float vet2);

//mutiplica um vetor por um fator
void multVet(float * vet1, float fator);

//encontra a magnitudo vetor
float magnVet(float * vet);

//normaliza um vetor para magnitude 1
void normalizaVet(float * vet);

//rotaciona matrix
void rotavionaMat(float * mat, float * eixoVet, float angulo);
//https://pt.wikipedia.org/wiki/Matriz_de_rota%C3%A7%C3%A3o

//multiplica v1 por uma matriz e coloca em v2
void multVetMat(float * v1, float * mat, float * v2);

//rotaciona v1 em torno de v2 por um angulo e armazena em v3
void rotacionaVet(float * v1, float * v2, float angulo, float * v3);
