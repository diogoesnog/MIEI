#include <stdlib.h>
#include <stdio.h>
#include "grafos.h"
#include "queueBuffer.h"

// Travessias em Grafos

// Verificar se uma sequência de vértices é uma ordenação topológica

// 1. Algoritmo de Tarjan

int cores[NV];

// Esta função apenas vai executando a auxilar que é a que tratra de tudo.
int tarjanLista(GrafoL grafo, int sequencia[]){

    int ciclico = 0;

    // Vértices são marcados inicialmente como não visitados.
    for(int i=0; i<NV; i++) cores[i]=WHITE;

    for(int i=0; i<NV && ciclico==0; i++){
        if(cores[i]==WHITE) ciclico = auxiliarTarjan(grafo,i,sequencia);
    }

    return ciclico;
}

int auxiliarTarjan(GrafoL grafo, int indice, int sequencia[]){

    int ciclico = 0; // Começa com veracidade.
    Lista auxiliar;

    /**
     * Declaramos que o vértice que estamos a estudar
     * está a ser visitado, daí o GREY.
     **/
    cores[indice] = GREY;

    auxiliar = grafo[indice];

    while(auxiliar!=NULL && ciclico==0){

        if(cores[auxiliar->destinoAresta] == GREY) ciclico=1;
        if(cores[auxiliar->destinoAresta] == WHITE){
            int indiceAtual = auxiliar->destinoAresta;
            ciclico = auxiliarTarjan(grafo, indiceAtual, sequencia);
        }

        auxiliar=auxiliar->proximo;
    }

    // Quando termina de ver os sucessores do vértice em questão, marca como visitado.
    cores[indice] = BLACK;
    // Para ser feito como está nas notas.
    sequencia[indice] = indice;
}

// 2. Algoritmo de Kahn

int antecessores[NV];
int visitados[NV];

int kahnLista(GrafoL grafo, int indice, int sequencia[]){

    int ciclico = 0;

    for(int i=0; i<NV; i++){
        // Função já definida no primeiro exercício.
        antecessores[i] = grauEntradaLista(grafo,indice);
        // Coloca todos os vértices como não visitados.
        visitados[i] = 0;
    }

    for(int i=0; i<NV && ciclico==0; i++){
        if(visitados[i]==0){
            ciclico = auxiliarKahn(grafo, i, sequencia);
        }
    }

    return ciclico;    
}

int auxiliarKahn(GrafoL grafo, int indice, int sequencia[]){

    int ciclico = 0;
    Lista auxiliar;

    visitados[indice] = 1;
    
    for(auxiliar=grafo[indice]; auxiliar!=NULL && ciclico==0; auxiliar=auxiliar->proximo){
        if(visitados[auxiliar->destinoAresta]==1) ciclico = 1;
        if(antecessores[indice]>0){
            antecessores[indice]--:
            ciclico=auxiliarKahn(grafo, auxiliar->destinoAresta, sequencia);
        }
    }

    antecessores[indice] = 0;
    sequencia[indice] = indice;
}

// Função que testa se um grafo é acíclico

int grafoCiclico(GrafoL grafo){

    int ciclico = 0;

    for(int i=0; i<NV; i++) visitados[i] = WHITE;

    for(int i=0; i<NV && ciclico==0; i++){
        if(visitados[i]==WHITE){
            ciclico = ciclicoAuxiliar(grafo, i, visitados);
        }
    }

    return ciclico;
}

int ciclicoAuxiliar(GrafoL grafo, int indice){

    int ciclico = 0;
    Lista auxiliar;

    visitados[indice] = 1;

    for(auxiliar=grafo[indice]; auxiliar!=NULL && ciclico==0; auxiliar=auxiliar->proximo){
        if(visitados[auxiliar->destinoAresta==GREY]) ciclico=1;
        if(visitados[auxiliar->destinoAresta==WHITE]){
            ciclico = ciclicoAuxiliar(grafo,auxiliar->destinoAresta);
        }
    }

    visitados[indice] = BLACK;

    return ciclico;     
}

// Função que determina quantos vértices num grafo estão a uma distância menor ou igual a N.

int sucessor(GrafoL grafo, int vertice, int distancia){

    int resultado = 0;

    ListaLigada *listaLigada;
    iniciarLL(listaLigada); 

    for(int i=0; i<NV; i++) cores[i] = WHITE;
    adicionarLL(listaLigada, vertice);

    while()
}


