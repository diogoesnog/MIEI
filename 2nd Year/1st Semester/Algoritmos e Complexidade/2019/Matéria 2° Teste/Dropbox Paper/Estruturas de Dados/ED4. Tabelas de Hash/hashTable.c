#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hashTable.h"

// 1. Open Addressing

// 1.1. Linear Probing

int hashLP(int chave) {
    return (chave%CAPACIDADE);
}

int iniciarHashLP(HashTableOpen tabelaHash) {

    for(int i = 0; i < CAPACIDADE; i++) {
        tabelaHash[i].chave = LIVRE;
        tabelaHash[i].valor = LIVRE;
    }
}

void inserirHashLP(HashTableOpen tabelaHash, int chave, int valor){

    int indiceInserir = hashLP(chave);
    int flag = 0;
    int i = 0;

    while(i<CAPACIDADE && flag!=1){

        // Caso esteja livre ou tenha sido apagado, podemos inserir.
        if( tabelaHash[indiceInserir].chave == LIVRE || 
            tabelaHash[indiceInserir].chave == APAGADO
        ){
            tabelaHash[indiceInserir].chave = chave;
            tabelaHash[indiceInserir].valor = valor;
            flag = 1;
        }
        // Caso não, tenta-se inserir na seguinte posição.
        else indiceInserir++;

        i++;
    }
}

void eliminarHashLP(HashTableOpen tabelaHash, int chave){

    int indiceEliminar = hashLP(chave);
    int flag = 0;
    int i = 0;

    while(i<CAPACIDADE && flag!=1){

        if(tabelaHash[indiceEliminar].chave == chave){
            tabelaHash[indiceEliminar].chave = APAGADO;
            flag = 1;
        }
        else indiceEliminar++;

        i++;
    }
}

int procurarHashLP(HashTableOpen tabelaHash, int chave){

    int indiceProcurar = hashLP(chave);
    int flag = 0;
    int i = 0;

    int posicao = -1; // Retorna -1 caso não exista na Tabela Hash.

    while(i<CAPACIDADE && flag!=1){

        if(tabelaHash[indiceProcurar].chave == chave){
            posicao = indiceProcurar;
            flag = 1;
        }
        else indiceProcurar++;

        i++;
    }
    
    return posicao;
}

// 1.2. Quadratic Probing

int hashQP(int chave, int indice) {
    return (chave + (indice*indice))%CAPACIDADE;
}

void inserirHashQP(HashTableOpen tabelaHash, int chave, int valor){

    // Usamos inicialmente a função de Hash normal.
    int indiceInserir = hashLP(chave);
    int flag = 0;
    int i = 0;

    while(i<CAPACIDADE && flag!=1){

        // Caso esteja livre ou tenha sido apagado, podemos inserir.
        if( tabelaHash[indiceInserir].chave == LIVRE || 
            tabelaHash[indiceInserir].chave == APAGADO
        ){
            tabelaHash[indiceInserir].chave = chave;
            tabelaHash[indiceInserir].valor = valor;
            flag = 1;
        }
        // Caso não, vamos começar a usar a função de Hash com Quadratic Probing.
        else indiceInserir = hashQP(chave, i+1);

        i++;
    }
}

void eliminarHashQP(HashTableOpen tabelaHash, int chave){

    int indiceEliminar = hashLP(chave);
    int flag = 0;
    int i = 0;

    while(i<CAPACIDADE && flag!=1){

        if(tabelaHash[indiceEliminar].chave == chave){
            tabelaHash[indiceEliminar].chave = APAGADO;
            flag = 1;
        }
        else indiceEliminar = hashQP(chave, i+1);

        i++;
    }
}

int procurarHashQP(HashTableOpen tabelaHash, int chave){

    int indiceProcurar = hashLP(chave);
    int flag = 0;
    int i = 0;

    int posicao = -1; // Retorna -1 caso não exista na Tabela Hash.

    while(i<CAPACIDADE && flag!=1){

        if(tabelaHash[indiceProcurar].chave == chave){
            posicao = indiceProcurar;
            flag = 1;
        }
        else indiceProcurar = hashQP(chave, i+1);

        i++;
    }
    
    return posicao;
}

// 2. Close Addressing


int hash(int chave) {
    return (chave%CAPACIDADE);
}

void inicializarHash(HashTableClose tabelaHash){

    for(int i = 0; i<CAPACIDADE; i++){
        tabelaHash[i] = NULL;
    }
}

void inserirHash(HashTableClose tabelaHash, int chave, int valor){

    int indiceInserir = hash(chave);

    hashClose *novaEntrada;
    novaEntrada = malloc(sizeof(struct hashClose));
    novaEntrada->chave = chave;
    novaEntrada->valor = valor;

    if(tabelaHash[indiceInserir] == NULL) novaEntrada->proximo = NULL;
    else novaEntrada->proximo = tabelaHash[indiceInserir];

    tabelaHash[indiceInserir] = novaEntrada;

}

void procurarHash(HashTableClose tabelaHash, int chave){

    int indiceInserir = hash(chave);

    hashClose *entrada = tabelaHash[indiceInserir];

    while(entrada!=NULL){
        printf("%d\n",entrada->valor);
        entrada = entrada->proximo;
    }

}

int main(void){

    HashTableClose hash;

    inicializarHash(hash);

	inserirHash(hash, 2, 10);
    inserirHash(hash, 22, 20);

    procurarHash(hash, 2);
}