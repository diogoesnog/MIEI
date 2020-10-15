#include "queue.h"

// 1. Modo Linear do Array.

// Função para iniciar a Queue.
void initQueue (QUEUE *q) {
    q->tamanho = 0;
    q->posicaoInicio = 0;
}

// Função para inserir na Queue no modo Linear.
int enqueue (QUEUE *q, int elemento) {

    // Caso esteja cheia, retorna-se logo 1.
    if(q->tamanho == MAX) {
        printf("Queue CHEIA. Impossível inserir mais elementos.\n"); 
        return 1;
    }

    // Caso não esteja cheia, insere-se.
    (q->valores)[q->posicaoInicio + q->tamanho] = elemento;
    (q->tamanho)++;
    
    return 0;
}
// Função para remover da Queue no modo Linear.
int dequeue (QUEUE *q, int *x) {

    // Caso esteja vazia, retorna-se logo 1.
    if(q->tamanho == 0) {
        printf("Queue VAZIA. Impossível remover mais elementos.\n"); 
        return 1;
    }

    // Caso não esteja vazia, remove-se o elemento FRONTAL.
    // Guarda-se esse elemento em x.
    (*x) = (q->valores)[q->posicaoInicio];
    q->posicaoInicio++;
    q->tamanho--;
    
    return 0;
}

// 2. Modo Circular do Array.

// Função para iniciar a Queue.
void initQueueCircular (QUEUECIRCULAR *q) {
    q->tamanho = 0;
    q->posicaoPrimeiro = -1;
    q->posicaoUltimo = -1;
}

// Função para inserir na Queue no modo Circular.
int enqueueCircular(QUEUECIRCULAR *q, int elemento)  {

    // Queue cheia.
    if(q->tamanho == MAX) {
        printf("Queue CHEIA. Impossível inserir mais elementos.\n"); 
        return 1;
    }

    // Primeiro Elemento.
    else if(q->posicaoPrimeiro == -1 && q->posicaoUltimo == -1) {
        q->posicaoPrimeiro = 0;
        q->posicaoUltimo = 0;
        q->tamanho++;
        q->valores[0] = elemento;
    }

    // Quando a Queue tem elementos vazios antes, sem falhas na Heap.
    // Ex: [ ] [ ] [ ] [1] [2] [3]
    else if(q->posicaoUltimo == MAX-1 && q->posicaoPrimeiro != 0) {
        q->posicaoUltimo = 0;
        q->tamanho++;
        q->valores[0] = elemento;
    }

    // Quando a Queue tem quebras ou o restante das opções.
    // Ex: [2] [3] [ ] [ ] [6] [7]
    // O 3 é o último elemento e o 6 é o primeiro elemento.
    else {
        q->posicaoUltimo++;
        q->tamanho++;
        q->valores[q->posicaoUltimo] = elemento;
    }

    return 0;
}

int dequeueCircular (QUEUECIRCULAR *q, int *x) {

    if(q->tamanho == 0) {
        printf("Queue VAZIA. Impossível remover.\n"); 
        return 1;
    }

    // Só tem 1 Elemento.
    else if(q->posicaoPrimeiro == q->posicaoUltimo){
        (*x) = q->valores[q->posicaoPrimeiro];
        q->posicaoPrimeiro = -1;
        q->posicaoUltimo = -1;
        q->tamanho--;
    }

    // Ex: [1] [2] [ ] [ ] [5] 
    else if(q->posicaoPrimeiro == MAX-1) {
        (*x) = q->valores[q->posicaoPrimeiro];
        q->posicaoPrimeiro = 0;
        q->tamanho--;
    }

    // Ex: [1] [2] [3] [ ] [5]
    else {
        (*x) = q->valores[q->posicaoPrimeiro];
        q->posicaoPrimeiro++;
        q->tamanho--;
    }

    return 0;
}

void imprimeQueueCircular(QUEUECIRCULAR *q) {
    
    int i = 0;
    
    while(i != q->tamanho) {
        printf("Elemento nº %d. Valor: %d.\n", i, q->valores[i]);
        i++;
    }
}

// Main para Teste.
int main() {

    QUEUECIRCULAR q;
    int a, i, j, empty, full, error;

    initQueueCircular(&q);

    i = 10;
    full = enqueueCircular(&q, i);
    while (!full) {
        printf("enqueued %d\n", i);
        i += 10;
        full = enqueueCircular(&q, i);
    }
    
    for (j=0; j<MAX/2; j++) {
        dequeueCircular(&q, &a);
        printf("dequeued %d\n", a);
    }
    
    //  first half of array now empty
    
    full = enqueueCircular(&q, i);
    while (!full) {
        printf("enqueued %d\n", i);
        i += 10;
        full = enqueueCircular(&q, i);
    }
    
    empty = dequeueCircular(&q, &a);
    while (!empty) {
        printf("dequeued %d\n", a);
        empty = dequeueCircular(&q, &a);
    }
}