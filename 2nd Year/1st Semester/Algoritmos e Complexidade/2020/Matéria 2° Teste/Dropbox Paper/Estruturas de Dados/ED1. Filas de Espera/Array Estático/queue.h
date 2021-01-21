    #include <stdio.h>
    #include <stdlib.h>

    // Limite Máximo da Fila de Espera.
    #define MAX 10

    // 1. Modo Linear do Array.

    // Estrutura de Dados.
    typedef struct queue {
        int posicaoInicio, tamanho;
        int valores[MAX]; 
    } QUEUE;

    // Funções a Implementar.
    void initQueue (QUEUE *q);
    int enqueue (QUEUE *q, int x); 
    int dequeue (QUEUE *q, int *x);


    // 2. Modo Circular do Array.

    // Estrutura de Dados.
    typedef struct queueCircular {
        int posicaoPrimeiro, posicaoUltimo, tamanho;
        int valores[MAX]; 
    } QUEUECIRCULAR;

    // Funções a Implementar.
    void initQueueCircular (QUEUECIRCULAR *q);
    int enqueueCircular (QUEUECIRCULAR *q, int x);
    int dequeueCircular (QUEUECIRCULAR *q, int *x);