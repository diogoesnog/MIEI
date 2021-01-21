#include <stdlib.h>
#include <stdio.h>
#include "stackBuffer.h"

// Stacks - LIFO (Last In Fisrt Out)
// O próximo a ser removido é o último que foi inserido.

// Implementação com Listas Ligadas

void iniciarLL(ListaLigada *lista){
    (*lista) == NULL;
}

int vaziaLL(ListaLigada lista){
    return (lista == NULL);
}

int adicionarLL(ListaLigada *lista, int elemento){
    
    int resultado = 0;

    Lista *novaLista = malloc(sizeof(Lista));

    if((*lista)==NULL) resultado = 1;
    else{
        novaLista->valor = elemento;
        novaLista->proximo = *lista;
        (*lista) = novaLista;
    }

    return resultado;
}

int proximoLL(ListaLigada lista, int *elemento){
    
    int resultado = 0;

    if(lista != NULL && lista->proximo != NULL){
        *elemento = lista->valor;
        resultado = lista->valor;
    }

    return resultado;
}

int removerLL(ListaLigada *lista, int *elemento){

    int resultado = 0;
    
    Lista *auxiliar = malloc(sizeof(Lista));

    if(*lista != NULL && (*lista)->proximo != NULL){
        auxiliar = *lista;
        *elemento = auxiliar->valor;
        *lista = (*lista)->proximo;
        resultado = auxiliar->valor;
        free(auxiliar);
    }

    return resultado;
}

// Implementação com Array

void iniciarA(ArrayBuffer *array, int capacidadeBuffer){

    array->valores = malloc(capacidadeBuffer*sizeof(int));
    array->tamanhoArray = 0;
    array->capacidadeBuffer = capacidadeBuffer;
}

int vaziaA(ArrayBuffer *array){
    return (array->tamanhoArray == 0);
}

int duplicarTamanho(ArrayBuffer *array){

    int resultado = 0; 

    array->tamanhoArray = array->tamanhoArray*2;
    array->valores = realloc(array->valores, array->tamanhoArray);

    return resultado;
}

int adicionarA(ArrayBuffer *array, int elemento){

    int resultado = 0;

    if(array->tamanhoArray == array->capacidadeBuffer) resultado = duplicarTamanho(array);
    if(resultado == 0){
        array->valores[array->tamanhoArray++] == elemento;
    }

    return resultado;

}

int proximoA(ArrayBuffer *array, int *elemento){

    int resultado = 0;

    if(array->tamanhoArray == 0){
        *elemento = array->valores[array->tamanhoArray-1];
        resultado = array->valores[array->tamanhoArray-1];
    }

    return resultado;
}

int removerA(ArrayBuffer *array, int *elemento){

    int resultado = 0;

    if(array->capacidadeBuffer == 0) resultado = 1;
    else {
        *elemento = array->valores[--array->tamanhoArray];
        resultado = array->valores[--array->tamanhoArray];
    }

    return resultado;
}

// Função Main para testes.

int main(void){

    // Lista Ligada

    ListaLigada lista;
    int elementoL;

    iniciarLL(&lista);

	adicionarLL(&lista, 12);
	adicionarLL(&lista, 5);
	adicionarLL(&lista, 1);
	adicionarLL(&lista, 6);
	adicionarLL(&lista, 8);
	adicionarLL(&lista, 10);

	printf("Vazia: %d\n", vaziaLL(lista));
	printf("Proximo: %d\n", proximoLL(lista,&elementoL));
	printf("Remover: %d\n", removerLL(&lista,&elementoL));

    // Array

    ArrayBuffer *array;
    int elementoA;

    iniciarA(array,6);

    adicionarA(array, 1);
	adicionarA(array, 5);
	adicionarA(array, 1);
	adicionarA(array, 6);
	adicionarA(array, 8);
	adicionarA(array, 15);

    printf("Vazia: %d\n", vaziaA(array));
	printf("Proximo: %d\n", proximoA(array,&elementoA));
    printf("Remover: %d\n", removerA(array,&elementoA));
}