#include <iostream>

typedef struct rotacao {
    int  periodo;
    float angulo;
    float x;
    float y;
    float z;
    struct rotacao *proximo;
}*Rotacao, TRotacao;

Rotacao inserirRotacao(float periodo, float angulo, float x, float y, float z, Rotacao rotacoes);
Rotacao reproduzirRotacao(Rotacao rotacao, long currentTime);
