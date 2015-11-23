#ifndef OBSERVADOR_H
#define OBSERVADOR_H

class Observador
{
private:
    //aponta para onde o observador esta olhando
    float frenteObs[3];

    //aponta para a direita da localização do observador
    float direitaObs[3];

    //aponta para cima de onde o observador está
    float upObs[3];

    //posição do observador na cena
    float posicaoObs[3];

    //indice de deslocamento
    float deslocamento;

    //indice de rotação
    float rotacao;
public:
    Observador();

    //Configuração da camera para o observador
    void setOrientacao(void);

    //munda orientação do observador
    void mudaOrientacao(float * ponto);

    //move o observador para a frente
    void frente();//w

    //move o observador para a esquerda
    void esquerda();//a

    //move o observador para a direita
    void direita();//d

    //move o observador para a trás
    void tras();//s

    //rotaciona em z para esquerda
    void rotacionaEsquerda();//j

    //rotaciona em z para direita
    void rotacionaDireita();//l

    //rotaciona em x para cima
    void giraCima();//k

    //rotaciona em x para baixo
    void giraBaixo();//i

    //rotaciona em y para a esquerda
    void viraDireita();//e

    //rotaciona em y para a direita
    void viraEsquerda();//q
};

#endif // OBSERVADOR_H
