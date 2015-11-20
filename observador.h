#ifndef OBSERVADOR_H
#define OBSERVADOR_H

class Observador
{
private:
    //aponta para onde o observador esta olhando
    float orientObs[3];

    //aponta para a direita da localização do observador
    float direitaObs[3];

    //aponta para cima de onde o observador está
    float acimaObs[3];

    //posição do observador na cena
    float posicaoObs[3];
public:
    Observador();

    //Configuração da camera para o observador
    void setOrientacao(void);

    //munda orientação do observador
    void mudaOrientacao(float * ponto);

    //muda o observador para a frente
    void frente();//w

    void esquerda();//a

    void direita();//d

    void tras();//s

    void giraEsquerda();//j

    void giraDireita();//l

    void giraCima();//k

    void giraBaixo();//i




};

#endif // OBSERVADOR_H

























