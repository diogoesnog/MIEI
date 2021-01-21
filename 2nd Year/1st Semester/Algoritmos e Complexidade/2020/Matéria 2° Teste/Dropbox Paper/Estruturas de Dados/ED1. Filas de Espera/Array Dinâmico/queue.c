#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

void initQueueDinamicaCircular (QUEUEDINAMICACIRCULAR *q) {
    q->primeiroElemento = -1;
    q->ultimoElemento = -1;
    q->tamanho = 0;
    q->capacidade = 2;
    q->valores = malloc(2 * sizeof(int));
}
    
void ordenarQueue (QUEUEDINAMICACIRCULAR *q) {

    int novaCapacidade = q->tamanho * 2;
    int *novosValores = malloc(novaCapacidade * sizeof(int));

    int i = q->primeiroElemento;
    int indice = 0;

    while(i != q->tamanho) {
        novosValores[indice] = q->valores[i];
        i++;
        indice++;
    }

    int j = 0;
    
    while(j != q->primeiroElemento){
        novosValores[indice] = q->valores[j];
        j++;
        indice++;
    }

    q->valores = novosValores;
    q->capacidade = novaCapacidade;
    q->tamanho = indice;
    q->primeiroElemento = 0;
    q->ultimoElemento = q->tamanho-1;
}

int enqueueDinamicaCircular (QUEUEDINAMICACIRCULAR *q, int elemento) {
    
    // 1. Se já ocupou o tamanho todo e se primeiro elemento esta na posicao 0 - apenas realocar.
    // 1. Se já ocupou o tamanho todo e o primeiro elemento nao esta na poiscoa 0 - realocar e ordenar array.
    if(q->tamanho == q->capacidade) {
        printf("Queue CHEIA. Vamos aumentar o seu espaço.\n"); 

        if(q->primeiroElemento == 0) {
            q->capacidade = 2 * q->capacidade;
            q->valores = realloc(q->valores, q->capacidade * sizeof(int));
        }
        else {
            printf("Queue CHEIA. Vamos aumentar o seu espaço.\n"); 
            printf("Vamos inserir o elemento %d.\n", elemento);
            ordenarQueue(q);
        }
        q->ultimoElemento++;
        q->valores[q->ultimoElemento] = elemento;
        q->tamanho++;
    }
    
    // 2. Se é o primeiro elemento a ser inserido.
    else if(q->primeiroElemento == -1 && q->ultimoElemento == -1) {
        q->primeiroElemento = 0;
        q->ultimoElemento= 0;
        q->tamanho++;
        q->valores[0] = elemento;
    }

    // 3. [ ][ ][10][20][30][40]
    else if(q->ultimoElemento == q->capacidade-1 && q->primeiroElemento != 0) {
        q->ultimoElemento =  0;
        q->tamanho++;
        q->valores[0] = elemento;

    }

    // 4. Restantes das opções.
    else {
        q->ultimoElemento++;
        q->valores[q->ultimoElemento] = elemento;
        q->tamanho++;
    }
    
    return 0;
}

int dequeueDinamicaCircular (QUEUEDINAMICACIRCULAR *q, int *elemento) {

    if(q->tamanho == 0) {
        printf("Queue VAZIA. Impossível remover.\n"); 
        return 1;
    }

    // Só tem 1 Elemento.
    else if(q->primeiroElemento == q->ultimoElemento){
        (*elemento) = q->valores[q->primeiroElemento];
        q->primeiroElemento = -1;
        q->ultimoElemento = -1;
        q->tamanho--;
    }

    // Ex: [1] [2] [ ] [ ] [5] 
    else if(q->primeiroElemento == q->capacidade-1) {
        (*elemento) = q->valores[q->primeiroElemento];
        q->primeiroElemento = 0;
        q->tamanho--;
    }

    // Ex: [1] [2] [3] [ ] [5]
    else {
        (*elemento) = q->valores[q->primeiroElemento];
        q->primeiroElemento++;
        q->tamanho--;
    }

    return 0;
}

// Main para Teste.
int main() {

    // Main do Professor
    
    QUEUEDINAMICACIRCULAR queueCircular;
    int a, i, j, empty, full, error;

    initQueueDinamicaCircular(&queueCircular);

    
    // Inserir 10 elementos. 
    // Tamanho do Array ficará em 16.
    // [10][20][30][40][50][60][70][80][90][100][ ][ ][ ][ ][ ][ ]  
    error = 0;
    for (i=10; i<=100 && !error; i+=10) {
        error = enqueueDinamicaCircular(&queueCircular, i);
        printf("enqueued %d\n", i);
    }
    
    // dequeue first 5 elements; there will be room for 11 elements
    // |__|__|__|__|__|60|70|80|90|100|__|__|__|__|__|__|
    empty = dequeueDinamicaCircular(&queueCircular, &a);
    if (!empty) printf("dequeued %d\n", a);
    for (j=0; j<4 && !empty; j++) {
        empty = dequeueDinamicaCircular(&queueCircular, &a);
        if (!empty) printf("dequeued %d\n", a);
    }

    // insert 20 more elements; first 11 will still fit, inserted with circularity
    // the remainining will cause reallocation with length 32 after insertion of 210
    // |170|180|190|200|210|60|70|80|90|100|110|120|130|140|150|160|
    // |60|70|80|90|100|110|120|130|140|150|160|170|180|190|200|210|220|230|240|250|260|270|280|290|300|__|__|__|__|__|__|__|
    
    for (; i<=300 && !error; i+=10) {
        error = enqueueDinamicaCircular(&queueCircular, i);
        printf("enqueued %d\n", i);
    }

    // dequeue all elements
    
    empty = dequeueDinamicaCircular(&queueCircular, &a);
    if (!empty) printf("dequeued %d\n", a);
    for (; !empty; i++) {
        empty = dequeueDinamicaCircular(&queueCircular, &a);
        if (!empty) printf("dequeued %d\n", a);
    }

    
    return 0;
}