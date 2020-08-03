#include <iostream>

typedef struct escala {
    float x;
    float y;
    float z;
    struct escala *proximo;
}*Escala, TEscala;

Escala inserirEscala(float x, float y, float z, Escala escalas);
Escala reproduzirEscala(Escala escala);
