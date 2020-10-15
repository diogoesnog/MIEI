#include <stdio.h>
#include <stdlib.h>

typedef struct queueDinamicaCircular {
    int primeiroElemento, ultimoElemento;
    int tamanho, capacidade; 
    int *valores;
} QUEUEDINAMICACIRCULAR;


void initQueueDinamicaCircular (QUEUEDINAMICACIRCULAR *q);
int enqueueDinamicaCircular (QUEUEDINAMICACIRCULAR *q, int elemento); 
int dequeueDinamicaCircular (QUEUEDINAMICACIRCULAR *q, int *elemento);