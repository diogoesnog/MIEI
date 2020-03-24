#ifndef grafos_h
#define grafos_h

#define NV 6
#define NE 0 // Peso da aresta que não existe

// Para os grafos não orientados (Matriz simétrica)
#define WHITE 0
#define GREY 1
#define BLACK 2

// Estruturas implementadas

typedef struct lista{
    int destinoAresta;
    int pesoAresta;
    struct lista *proximo;
} *Lista;

typedef int Fringe[NV];

#endif