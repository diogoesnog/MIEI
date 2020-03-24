#include <stdlib.h>
#include <stdio.h>
#include "grafos.h"

// Funções de Conversão

void matrizParaLista(GrafoM matriz, GrafoL lista){

    int i;
    int j;

    // Ter em conta que a Lista já está definida como um apontador.
    Lista auxiliar = NULL;

    for(i=0; i<NV; i++){

        // Cada elemento de um GrafoL é um tipo Lista que já é um apontador.
        lista[i] = NULL;

        for(j=NV-1; j>+0; j--){

            if(matriz[i][j] != NE){
                auxiliar = malloc(sizeof(struct lista));
                auxiliar->destinoAresta = j;
                auxiliar->pesoAresta = matriz[i][j];
                auxiliar->proximo = lista[i];
                lista[i] = auxiliar;
            }
        }
    }
}

void listaParaMatriz(GrafoM matriz, GrafoL lista){

    int i;
    int j;

    Lista auxiliar = NULL;

    for(i=0; i<NV; i++){

        for(j=0; j<NV; j++){

            auxiliar = lista[i];

            if(auxiliar!=NULL && auxiliar->destinoAresta == j){
                matriz[i][j] = auxiliar->pesoAresta;
                auxiliar = auxiliar->proximo;
            }
            else matriz[i][j] = NE;
        }
    }
}

// Cálculo dos Graus de Entrada e Saída

void grauEntradaMatriz(GrafoM matriz, int nVertice){

    int resultado = 0;

    for(int i=0; i<NV; i++){
        if(matriz[i][nVertice] != NE) resultado++;
    }

    return resultado;
}

void grauEntradaLista(GrafoL lista, int nVertice){

    int resultado = 0;

    Lista auxiliar;

    for(int i=0; i<NV; i++){

        auxiliar = lista[i];

        while(auxiliar!=NULL && auxiliar->destinoAresta<=nVertice){
            if(auxiliar->destinoAresta == nVertice) resultado++;
        }
    }

    return resultado;
}

grauSaidaMatriz(GrafoM matriz, int nVertice){

    int resultado = 0;

    for(int i=0; i<NV; i++){
        if(matriz[i][nVertice] != NE) resultado++;
    }

    return resultado;
}

grauSaida(GrafoL lista, int nVertice){

    int resultado = 0;
    Lista auxiliar;

    auxiliar = lista[nVertice];

    while(auxiliar!=NULL){
        resultado++;
        auxiliar=auxiliar->proximo;
    }

    return resultado;
}

// Cálculo da capacidade de um vértice (assumindo vértice como sendo o a)

/**
 * capacidade = (soma pesos arestas que têm a como destino)
 *            - (soma pesos arestas que têm a como origem)
 * ou seja,
 * 
 * capacidade = vComoDestino + vComoDestino + ... - vComoOrigem - vComoOrigem (...)
 **/

int capacidadeVerticeMatriz(GrafoM matriz, int nVertice){

    int resultado = 0;

    for(int i=0; i<NV; i++){

        // Significa que o i é o vértice origem.
        // Logo, necessário contar todos os pesos das arestas dessa linha.
        if(i==nVertice){
            for(int j=0; j<NV; j++){
                if(matriz[nVertice][i] != NE) resultado -= matriz[nVertice][j];
            }
        }
        else if(matriz[i][nVertice] != NE) resultado += matriz[i][nVertice];
    }

    return resultado;
}

int capacidadeVerticaLista(GrafoL lista, int nVertice){

    int resultado = 0;
    Lista auxiliar;

    for(int i=0; i<NV; i++){

        if(i==nVertice){
            auxiliar = lista[i];
            while(auxiliar!=NULL){
                resultado -= auxiliar->pesoAresta;
                auxiliar=auxiliar->proximo;
            }
        }
        else{
            auxiliar = lista[i];
            while(auxiliar!=NULL && auxiliar->destinoAresta<=nVertice){
                if(auxiliar->destinoAresta==nVertice) resultado += auxiliar->pesoAresta; 
                auxiliar=auxiliar->proximo;
            }
        }

    }

    return resultado;
}

// Cálculo do vérice com maior capacidade

int verticeMaiorCapacidadeMatriz(GrafoM matriz){

    // Criamos um array para guardar as capacidades de todos os vértices.
    // Daí o tamanho ser NV.
    int *arrayCapacidades = malloc(NV*sizeof(int));

    int resultado = 0;

    // Preenchemos o array todo a zero.
    for(int i=0; i<NV; i++) arrayCapacidades[i] = 0;


    for(int i=0; i<NV; i++){
        for(int j=0; j<NV; j++){
            if(matriz[i][j]!=NE){
                arrayCapacidades[i] -= matriz[i][j];
                arrayCapacidades[j] += matriz[i][j];
            }
        }
    }

    resultado = arrayCapacidades[0];

    for(int i=1; i<NV; i++){
        if(resultado<arrayCapacidades[i]) resultado = i;
    }

    free(arrayCapacidades);
    arrayCapacidades=NULL;

    return resultado;
}

int verticeMaiorCapacidadeLista(GrafoL lista){

    int *arrayCapacidades = malloc(NV*sizeof(int));

    int resultado = 0;
    Lista auxiliar;

    for(int i=0; i<NV; i++) arrayCapacidades[i] = 0;

    for(int i=0; i<NV; i++){

        auxiliar = lista[i];

        while(auxiliar!=NULL){
            arrayCapacidades[i] -= auxiliar->pesoAresta;
            arrayCapacidades[auxiliar->destinoAresta] += auxiliar->pesoAresta;
            auxiliar=auxiliar->proximo;
        }
    }

    resultado = arrayCapacidades[0];

    for(int i=1; i<NV; i++){
        if(resultado<arrayCapacidades[i]) resultado = i;
    }

    free(arrayCapacidades);
    arrayCapacidades=NULL;

    return resultado;
}

// Verifica se uma coloração é válida para um dado grafo ORIENTADO (Matriz Simétrica)

int coloracaoValidaMatriz(GrafoM matriz, int color[]){

    int resultado = 1; // Começa como válido.

    for(int i=0; i<NV && resultado==1; i++){
        for(int j=0; j<NV && resultado==1; j++){
            if(matriz[i][j]!=NE
            && color[i]==color[j]) resultado=0;
        }
    }

    return resultado;
}

int coloracaoValidaLista(GrafoL lista, int color[]){

    int resultado = 1;
    Lista auxiliar;

    for(int i=0; i<NV && resultado==1; i++){

        auxiliar = lista[i];

        while(auxiliar!=NULL && resultado==1){
            if(color[i]==color[auxiliar->destinoAresta]) resultado=0;
            auxiliar=auxiliar->proximo;
        }
    }
    
    return resultado;
}

// Funções do Inverso

void inversoMatriz(GrafoM matriz, GrafoM inversa){

    for(int i=0; i<NV; i++){
        for(int j=0; j<NV; j++){
            inversa[j][i] = matriz[i][j];
        }
    }
}