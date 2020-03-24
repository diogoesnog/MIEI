#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graphO.h"

// Funções de Grafos Orientados
// Grafos que podem ser bidirecionais
// Grafos sem peso

// 1. Matriz de Adjacência

// Iniciar Grafo Matriz.
void iniciarGraphM(GraphM grafo) {

    for(int i = 0; i < MAX; i++) {
        for(int j = 0; j < MAX; j++) {
            // Colocamos a 0 para iniciar.
            // Como se não tivessem ligações.
            grafo[i][j] = 0;
        }
    }
}

// Transformar Grafo Matriz para Lista.
void matrizParaListas(GraphM grafoMatriz, GraphL grafoLista) {

    for(int i = 0; i < MAX; i++) {

        // Inicializamos a NULL.
        grafoLista[i] = NULL;
        
        for(int j = 0; j < MAX; j++) {
            
            if(grafoMatriz[i][j] != 0) {
                struct bloco *auxiliar = malloc(sizeof(struct bloco));
                auxiliar->destino = j;
                auxiliar->proximo = grafoLista[i];
            }
        }
    }
}

// Grau de Entrada de um dado vértice de um Grafo Matriz.
int grauEntradaGraphM(GraphM grafo, int vertice) {

    int resultado = 0;

    for(int i = 0; i < MAX; i++) {
        
        if(grafo[i][vertice] == 1) resultado++;
    }

    return resultado;
}

// Grau de Saída de um dado vértice de um Grafo Matriz.
int grauSaidaGraphM(GraphM grafo, int vertice) {

    int resultado = 0;

    for(int i = 0; i < MAX; i++) {
        
        if(grafo[vertice][i] == 1) resultado++;
    }

    return resultado;
}

// 2. Lista de Adjacência

// Iniciar Grafo Lista.
void iniciarGraphL(GraphL grafo) {

    for(int i = 0; i < MAX; i++) {
        grafo[i] = NULL;
    }
}

// Transformar Grafo Lista para Matriz.
void listaParaMatriz(GraphM grafoMatriz, GraphL grafoLista) {

    for(int i = 0; i < MAX; i++){
        
        struct bloco *auxiliar = grafoLista[i];

        while(auxiliar != NULL) grafoMatriz[i][auxiliar->destino] = 1;
    }
}

// Grau de Entrada de um dado vértice de um Grafo Matriz.
int grauEntradaGraphM(GraphM grafo, int vertice) {

    int resultado = 0;

    for(int i = 0; i < MAX; i++) {

        struct bloco *auxiliar = grafo[i];

        while(auxiliar != NULL) 
            if(auxiliar->destino == vertice) resultado++;
    }

    return resultado;
}

// Grau de Saída de um dado vértice de um Grafo Matriz.
int grauSaidaGraphM(GraphM grafo, int vertice) {

    int resultado = 0;

    struct bloco *auxiliar = grafo[vertice];

    while(auxiliar != NULL) resultado++;

    return resultado;
}