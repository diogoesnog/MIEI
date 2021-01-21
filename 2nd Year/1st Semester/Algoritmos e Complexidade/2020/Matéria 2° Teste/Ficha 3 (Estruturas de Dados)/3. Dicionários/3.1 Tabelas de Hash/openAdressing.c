#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "openAdressing.h"

void inicializarTabela(HashTable tabelaHash){

    for(int i = 0; i < HASHSIZE; i++){
        strcpy(tabelaHash[i].chave,EMPTY);
        tabelaHash[i].informacao = EMPTY;
    }
}

void limparTabela(HashTable tabelaHash){
    inicializarTabela(tabelaHash);
}

// Linear Probing

/** No caso do Linear Probing calculamos a posição pelo hash dito normal.
 * É então no método do insert que vamos sempre colocando na posição seguinte
 * caso a calculada pelo método hash já se encontre ocupada. **/
int hashLP(KeyType chave){

    int i;
    int somaCaracteres;

    for(i=0; i<9 && chave[i]; i++){
        somaCaracteres = somaCaracteres + chave[i];
    }

    return (somaCaracteres%HASHSIZE);
}

void inserirTabelaLP(HashTable tabelaHash, KeyType chave, Info informacao){

    int indiceInserir = hashLP(chave);
    int flag = 0;
    int i = 0;

    while(i<HASHSIZE && flag!=1){

        if(strcmp(tabelaHash[indiceInserir].chave,EMPTY) == 0 
        || strcmp(tabelaHash[indiceInserir].chave,DELETED) == 0){
            strcpy(tabelaHash[indiceInserir].chave,chave);
            tabelaHash[indiceInserir].informacao = informacao;
            flag = 1;
        }
        else if(indiceInserir == (HASHSIZE-1)) indiceInserir = 0;
        else indiceInserir++;

        i++;
    }
}

void eliminarTabelaLP(HashTable tabelaHash, KeyType chave){

    int indiceEliminar = hashLP(chave);
    int flag = 0;
    int i = 0;

    while(i<HASHSIZE && flag!=1){

        if((strcmp(tabelaHash[indiceEliminar].chave,chave)) == 0){
            strcpy(tabelaHash[indiceEliminar].chave,DELETED);
            flag = 1;
        }
        else if(indiceEliminar == (HASHSIZE-1)) indiceEliminar = 0;
        else indiceEliminar++;

        i++;
    }
}

int procurarTabelaLP(HashTable tabelaHash, KeyType chave){

    int indiceProcurar = hashLP(chave);
    int flag = 0;
    int i = 0;

    int posicao = -1; // Retorna -1 caso não exista na Tabela Hash.

    while(i<HASHSIZE && flag!=1){

        if(strcmp(tabelaHash[indiceProcurar].chave,chave) == 0){
            posicao = indiceProcurar;
            flag = 1;
        }
        else if(indiceProcurar == (HASHSIZE-1)) indiceProcurar = 0;
        else indiceProcurar++;

        i++;
    }

    return posicao;
}

// Quadratic Probing

int hashQP(KeyType chave, int indice){

    int i;
    int somaCaracteres;

    for(i=0; i<9 && chave[i]; i++){
        somaCaracteres = somaCaracteres + chave[i];
    }

    return ((somaCaracteres + (indice*indice))%HASHSIZE);
}

void inserirTabelaQP(HashTable tabelaHash, KeyType chave, Info informacao){

    int flag = 0;
    int indiceInserir;

    for(int i=0; i<HASHSIZE && flag==0; i++){

        indiceInserir = hashQP(chave,i);

        if(strcmp(tabelaHash[indiceInserir].chave,EMPTY) == 0 
        || strcmp(tabelaHash[indiceInserir].chave,DELETED) == 0){
            strcpy(tabelaHash[indiceInserir].chave,chave);
            tabelaHash[indiceInserir].informacao = informacao;
            flag = 1;
        }
    }
}

void eliminarTabelaQP(HashTable tabelaHash, KeyType chave){

    int flag = 0;
    int indiceEliminar;

    for(int i=0; i<HASHSIZE && flag==0; i++){

        indiceEliminar = hashQP(chave,i);

        if(strcmp(tabelaHash[indiceEliminar].chave,chave)==0){
            strcpy(tabelaHash[indiceEliminar].chave,DELETED);
            flag = 1;
        }
    }
}

int procurarTabelaQP(HashTable tabelaHash, KeyType chave){
   
    int flag = 0;
    int indiceProcurar;

    int posicao = -1; // Retorna -1 caso não exista na Tabela Hash.

    for(int i=0; i<HASHSIZE && flag==0; i++){

        indiceProcurar = hashQP(chave,i);

        if(strcmp(tabelaHash[indiceProcurar].chave,chave) == 0){
            posicao = indiceProcurar;
            flag = 1;
        }
    }

    return posicao;
}

// Função Main para testes.

int main(void){

    HashTable hash;
	int a = 1, b = 4, c = 15, d = 2, e = 5;

    inicializarTabela(hash);

	inserirTabelaQP(hash, "1", &a);
	inserirTabelaQP(hash, "4", &b);
	inserirTabelaQP(hash, "15", &c);
	inserirTabelaQP(hash, "2", &d);
	inserirTabelaQP(hash, "5", &e);

    printf("O índice calculado pela hash para o elemento 15 é: %d\n", hashQP("15",0));
    printf("Elemento 15 existe? (Retorna -1 caso não exista): %d\n", procurarTabelaQP(hash,"15"));
}