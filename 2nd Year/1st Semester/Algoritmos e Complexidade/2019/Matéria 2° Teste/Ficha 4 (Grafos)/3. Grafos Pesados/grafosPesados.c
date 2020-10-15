#include <stdlib.h>
#include <stdio.h>
#include "grafosPesados.h"

void newFringe(Fringe fringe){
    // Inicializa os pesos de cada vértice na Orla com -1.
    for(int i=0; i<NV; i++) fringe[i] = -1;
}

// Adiciona um custo a um vértice da Orla.
int adicionarCusto(Fringe fringe, int nVertice, int custo){
    fringe[nVertice] = custo;
}

// Atualiza o custo de um vértice da Orla.
int atualizarCusto(Fringe fringe, int nVertice, int custo){
    fringe[nVertice] = custo;
}

// Removemos o vértice com custo menor da Orla
// Devolve o índice do vértice com menos custo
int nextFringe(Fringe fringe){

    int indiceMinimo = -1;

    for(int i=0; i<NV; i++){
        if(fringe[i]>=0){
            if(indiceMinimo<0 || fringe[i]<fringe[indiceMinimo]) indiceMinimo = i;
        }
    }

    // Ao colocar com peso -1 é como se não estivesse na Orla.
    if(indiceMinimo>=0) fringe[indiceMinimo] = -1;

    return indiceMinimo;
}

// Algoritmo de Prim para gerar à árvore de custo minímo.
int algoritmoPrim(Lista lista, int *vertices, int *custos){

    int vertice;
    int tamanhoFringe;
    int cores[NV];

    Fringe fringe;
    newFringe(fringe);

    vertices = malloc(NV*sizeof(int));
    custos = malloc(NV*(sizeof(int));

    for(int i=0; i<NV; i++){

    }

    cores[0] = GREY;
    custos[0] = 0;

    adicionarCusto(fringe,0,0);
    tamanhoFringe = 1;

    while(tamanhoFringe!=0){
        // Procuramos a próxima posição com menor peso.
        vertice = nextFringe(fringe);
        tamanhoFringe--;
        cores[vertice] = BLACK;

        Nodo *auxiliar;

        for(auxiliar=lista[vertice]; auxiliar!=NULL; auxiliar=auxiliar->proximo){

            switch(cores[auxiliar->destinoAresta])
        }
    }
}