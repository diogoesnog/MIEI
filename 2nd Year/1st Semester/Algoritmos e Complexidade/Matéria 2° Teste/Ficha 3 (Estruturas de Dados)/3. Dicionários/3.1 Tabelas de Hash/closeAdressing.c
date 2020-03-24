#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "closeAdressing.h"

int hash(KeyType chave){

    int i;
    int somaCaracteres;

    for(i=0; i<9 && chave[i]; i++){
        somaCaracteres = somaCaracteres + chave[i];
    }

    return (somaCaracteres%HASHSIZE);
}

void inicializarTabela(HashTable tabelaHash){

    for(int i = 0; i<HASHSIZE; i++){
        tabelaHash[i] = NULL;
    }
}

void limparTabela(HashTable tabelaHash){
    inicializarTabela(tabelaHash);
}

void inserirTabela(HashTable tabelaHash, KeyType chave, Info informacao){

    int indiceInserir = hash(chave);

    // Uma vez que Entry não está definido na estrutura como apontador, tem de se criar aqui como sendo um.
    Entry *entrada;

    entrada = malloc(sizeof(struct entry));
    strcpy(entrada->chave,chave);
    entrada->informacao = informacao;
    entrada->proximo = tabelaHash[indiceInserir];
    tabelaHash[indiceInserir] = entrada;
}

Entry* procurarTabela(HashTable tabelaHash, KeyType chave){

    int indiceInserir = hash(chave);
    Entry *resultado = NULL;

    Entry *entrada = tabelaHash[indiceInserir];

    while(entrada!=NULL && strcmp(entrada->chave,chave)!=0){
        entrada = entrada->proximo;
    }

    resultado = entrada;

    return resultado;
}

// Função Main para testes.

int main(void){

    HashTable hash;
	int x = 2, y = 1, z = 10, a = 11, b = 1204, c = 7, g = 8;

    inicializarTabela(hash);

	inserirTabela(hash, "2", &x);
	inserirTabela(hash, "1", &y);
	inserirTabela(hash, "10", &z);
	inserirTabela(hash, "11", &a);
	inserirTabela(hash, "20", &b);
	inserirTabela(hash, "7", &c);
	inserirTabela(hash, "8", &g);

}