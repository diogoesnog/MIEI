#include <stdlib.h>
#include <stdio.h>
#include "queueBuffer.h"

// Queues - FIFO (First In Fisrt Out)
// O próximo a ser removido é o primeiro que foi inserido.

// Implementação com Listas Ligadas

void iniciarLL(QueueListaLigada *queue){
    queue->lista = NULL;
    queue->tamanhoQueue = 0;
}

int vaziaLL(QueueListaLigada *queue){
    
    if(queue->tamanhoQueue == 0) return 1;
    else return 0;
}

// Vamos adicionar no final de modo a facilitar depois a remoção.
void adicionarLL(QueueListaLigada *queue, int elemento){
    
    ListaLigada *novaLista = malloc(sizeof(ListaLigada));
    ListaLigada *listaAtual = queue->lista;

    novaLista->valor = elemento;
    novaLista->proximo = NULL;

    if(listaAtual == NULL){
        queue->lista = novaLista;
        queue->tamanhoQueue++;
    }
    else{
        while(listaAtual->proximo != NULL){
            listaAtual = listaAtual->proximo;
        }
        listaAtual->proximo = novaLista;
        queue->tamanhoQueue++;
    }

}

int proximoLL(QueueListaLigada *queue, int *elemento){

    int resultado = 0;

    *elemento = queue->lista->valor;
    resultado = queue->lista->valor;

    return resultado;
}

int removerLL(QueueListaLigada *queue, int *elemento){

    int resultado = 0;
    ListaLigada *auxiliar = queue->lista;

    *elemento = auxiliar->valor;
    queue->lista = auxiliar->proximo;

    free(auxiliar);

    queue->tamanhoQueue--;
    
    resultado = queue->lista->valor;

    return resultado;
}

// Implementação com Arrays

void iniciarA(QueueArray *queue, int capacidadeBuffer){

    queue = malloc(sizeof(QueueArray));

    queue->cabeca = 0;
    queue->cauda = 0;
    queue->tamanhoArray = 0;
    queue->capacidadeBuffer = capacidadeBuffer;
    queue->valores = malloc(capacidadeBuffer*sizeof(int));

}

int vaziaA(QueueArray *queue){
    
    if(queue->tamanhoArray == 0) return 1;
    else return 0;
}

void adicionarA(QueueArray *queue, int elemento){

    if(queue->tamanhoArray < queue->capacidadeBuffer){
        queue->valores[queue->cauda] = elemento;
        queue->tamanhoArray++;
        queue->cauda++;
    }
}

int proximoA(QueueArray *queue, int *elemento){

    int resultado = 0;

    *elemento = queue->valores[queue->cabeca];
    resultado = queue->valores[queue->cabeca];

    return resultado;
}

int removerA(QueueArray *queue, int *elemento){

    int resultado = 0;

    if(queue->tamanhoArray > 0){
        *elemento = queue->valores[queue->cabeca];
        queue->cabeca++;
        queue->tamanhoArray--;

        if(queue->cabeca == queue->capacidadeBuffer) queue->cabeca = 0;

    }

    // Retorna o próximo a ser removido.
    return queue->valores[queue->cabeca];
}

// Função Main para testes.

int main(void){

    // Lista Ligada

    QueueListaLigada queue;
    int elementoL;

    iniciarLL(&queue);

	adicionarLL(&queue, 112);
	adicionarLL(&queue, 5);
	adicionarLL(&queue, 1);
	adicionarLL(&queue, 6);
	adicionarLL(&queue, 8);
	adicionarLL(&queue, 10);

	printf("Vazia: %d\n", vaziaLL(&queue));
	printf("Proximo: %d\n", proximoLL(&queue,&elementoL));
	printf("Remover: %d\n", removerLL(&queue,&elementoL));

    // Array

    QueueArray array;
    int elementoA;

    iniciarA(&array,6);

    adicionarA(&array, 1);
	adicionarA(&array, 5);
	adicionarA(&array, 1);
	adicionarA(&array, 6);
	adicionarA(&array, 8);
	adicionarA(&array, 15);

    printf("Vazia: %d\n", vaziaA(&array));
	printf("Proximo: %d\n", proximoA(&array,&elementoA));
    printf("Remover: %d\n", removerA(&array,&elementoA));

}