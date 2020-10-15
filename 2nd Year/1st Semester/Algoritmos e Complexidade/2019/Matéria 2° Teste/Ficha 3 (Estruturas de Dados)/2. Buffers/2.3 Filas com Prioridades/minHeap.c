#include <stdlib.h>
#include <stdio.h>
#include "minHeap.h"

// Funções Essenciais numa Min-Heap

// Swap

void swap(int valores[], int indice, int indicePai){
    
    // Apenas para guardar o valor e não o perder para depois se puder substituir.
    int valorFilho = valores[indice];

    valores[indice] = valores[indicePai];
    valores[indicePai] = valorFilho;
}

// BubbleUp 
void bubbleUp(int valores[], int indice){

    while (indice != 0 && valores[indice] < valores[PARENT(indice)]){
        swap(valores, indice, PARENT(indice));
        indice = PARENT(indice);
    }
}

// BubbleDown

/*
void bubbleDown(int valores[], int indice){

    int i = 0;
    int minimo = 0;

    while(LEFT(i) < indice){

        if(valores[i] < valores[LETF(i)]) minimo = i;
        if(valores[i] > valores[LETF(i)]) minimo = LETF(i);

        if (RIGHT(i) < indice){
            if(valores[minimo])
        }


    }
}
*/

Heap* newHeap(int tamanho){

    Heap *heap = malloc(sizeof(struct heap));

    heap->tamanho = tamanho;
    heap->usados = 0;
    heap->valores = malloc(tamanho*sizeof(int));

    return heap;
}

int insertHeap(Heap *heap, int elemento){
    
    int resultado = 0;

    // Caso o array já esteja cheio, realocamos memória.
    // Realloc muda o tamanho do array (valores) para o novo tamanho que foi duplicado primeiro.
    if(heap->tamanho == heap->usados){
        heap->tamanho = heap->tamanho*2;
        heap->valores = realloc(heap->valores, heap->tamanho);
    }
    
    heap->valores[heap->usados] = elemento;
    heap->usados++;

    bubbleUp(heap->valores, heap->usados-1);

    resultado = 1;

    return resultado;
}

int extractMin(Heap *heap, int *elemento){

    int resultado = 0;

    if(heap->tamanho == 0) resultado = 1;
    else{
        *elemento = heap->valores[0];
        heap->valores[0] = heap->valores[heap->usados-1];
        // Ao diminuirmos o usados é como esse elemnto deixasse de existir.
        (heap->usados)--;

        // bubbleDown(heap->valores,heap->usados);
    }

    return resultado;
}

// Função Main para testes.

int main(void){

    Heap *heap = newHeap(20);

    insertHeap(heap, 10);
    insertHeap(heap, 20);
	insertHeap(heap, 30);
	insertHeap(heap, 40);
	insertHeap(heap, 60);
	insertHeap(heap, 50);
	insertHeap(heap, 70);

}