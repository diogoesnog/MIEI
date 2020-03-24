#ifndef grafos_h
#define grafos_h

#define NV 6
#define NE 0 // Peso da aresta que não existe

// Para os grafos não orientados (Matriz simétrica)
#define WHITE 0
#define GREY 1
#define BLACK 2

// Estruturas implementadas

// 1. Implementação por Matrizes de Adjacência

typedef int GrafoM[NV][NV];

// 2. Implementação por Listas de Adjacência

typedef struct lista{
    int destinoAresta;
    int pesoAresta;
    struct lista *proximo;
} *Lista;

typedef Lista GrafoL[NV];

// Funções a desenvolver

#endif