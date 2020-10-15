#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "exerciciosAdicionais.h"

// 1. Calcular Capacidade de um Vértice.
// Capacidade = (soma pesos arestas V destino) - (soma pesos arestas V origem)

int capacidade(GrafoL grafo, int vertice) {

    // Primeiro ciclo para as Entradas.
    int entradas = 0;

    for(int i = 0; i < MAX; i++) {
        
        struct bloco *auxiliar = grafo[i];

        while(auxiliar){

            if(auxiliar->destino == vertice) entradas += auxiliar->peso; break;
            auxiliar = auxiliar->proximo;
        }
    }

    // Segundo ciclo para as Saídas.
    int saidas = 0;

    struct bloco *auxiliar = grafo[vertice];

    while(auxiliar){
        saidas += auxiliar->peso;
        auxiliar = auxiliar->proximo;
    }

    return (entradas - saidas);
}

// 2. Calcular o vértice com maior capacidade.
int maxCapV1(GrafoL grafo) {

    // Vamos colocar num array as capacidades dos MAX vértices.
    int capacidades[MAX];
    for(int j = 0; j < MAX; j++) capacidades[j] = 0;

    for(int i = 0; i < MAX; i++) {
        
        struct bloco *vertice = grafo[i];

        while(vertice) {

            capacidades[i] -= vertice->peso;
            capacidades[vertice->destino] += vertice->peso;
        } 
    }

    // Retirar o maior do Array de Capacidades.
}

int maxCapV2(GrafoL grafo) {

    // Vamos colocar num array as capacidades dos MAX vértices.
    int capacidades[MAX];
    for(int j = 0; j < MAX; j++) capacidades[j] = 0;

    for(int i = 0; i < MAX; i++) {
        capacidades[i] = capacidade(grafo, i);
    }
    
    // Fazemos o resto em si.    
}

// 3. Verificar se uma coloração é válida para um determinado Grafo.
// Sse vértices adjacentes têm cores diferentes.
int colorOK(GrafoL grafo, int cores[]) {

    for(int i = 0; i < MAX; i++){

        struct bloco *auxiliar = grafo[i];

        while(auxiliar) {

            if(cores[i] == cores[auxiliar->destino]) return 0;
            auxiliar = auxiliar->proximo;
        }
    }

    return 1;
}