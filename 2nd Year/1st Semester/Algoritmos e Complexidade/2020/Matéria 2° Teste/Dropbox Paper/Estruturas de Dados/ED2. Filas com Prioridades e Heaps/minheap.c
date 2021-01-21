#include <stdio.h>
#include <stdlib.h>

#include "minheap.h"

void trocaElementos(Elem elementos[], int indice1, int indice2) {
    Elem guarda = elementos[indice1];
    
    elementos[indice1] = elementos[indice2];
    elementos[indice2] = guarda;
}

void bubbleUp (Elem *elementos, int i) {
    
    // O valor de i corresponde ao valor de used.
    // Dessa forma, conseguimos ter o valor do índice máximo atual do array.
    while(i != 0){
        
        int indiceNoAtual = i;
        int indicePai = PARENT(i);
        
        if(elementos[indiceNoAtual] < elementos[indicePai]) 
            trocaElementos(elementos, indiceNoAtual, indicePai);
        
        i = indicePai;
    }
}

int minimo (Elem elementos[], int indiceDireita, int indiceEsquerda) {
    
    if(elementos[indiceDireita] > elementos[indiceEsquerda]) return indiceEsquerda;
    else return indiceDireita;
}

void bubbleDown (Elem *elementos, int tamanhoHeap) {
    
    int i = 0;
    
    while(RIGHT(i) < tamanhoHeap) {
    
        int indiceFilhoMinimo = minimo(elementos, RIGHT(i), LEFT(i));
        
        trocaElementos(elementos, i, indiceFilhoMinimo);
        
        i = indiceFilhoMinimo;
    }
    
}

void initHeap (Heap *heap, int size) {
    
    // Calloc igual a malloc.
    // A única diferença é que atribui o valor de 0 a todos os elementos que está a "inicializar".
    heap->values = calloc(size, sizeof(Elem));
    heap->size = size;
    heap->used = 0;
}

// Não é necessário devolver erro dado que quando a Heap está cheia, fazemos o realloc.
int  insertHeap (Heap *heap, Elem x) {

    // Verificar se existe espaço suficiente para inserir um novo.
    if(heap->size == heap->used) {
        heap->values = realloc(heap->values, 2*(heap->size)*sizeof(Elem));
        heap->size = heap->size*2;
    }
    
    int indiceAtual = heap->used;
    
    heap->values[indiceAtual] = x;
    (heap->used)++;
    
    // Used-1 dado que o valor de Used corresponde ao tamanheapo atual da Heap.
    bubbleUp(heap->values, heap->used-1);
    
    return 1;
}

// Caso a Heap esteja vazia devolvemos o 0 como forma de erro.
int  extractMin (Heap *heap, Elem *x) {

    if(heap->used > 0) {
        (*x) = heap->values[0];
        
        // Pegamos no último da Heap e colocamos na raiz.
        // Eliminamos assim esse último elemento depois.
        heap->values[0] = heap->values[heap->used-1];
        (heap->used)--;
        
        bubbleDown(heap->values, heap->used);

        return 1;
    }
    
    else return 0;
}

int minHeapOK (Heap h) {

    int tamanhoHeap = h.used;
    int i = 0;

    while(LEFT(i) <= tamanhoHeap || RIGHT(i) <= tamanhoHeap) {

        if(h.values[i] <= h.values[LEFT(i)] && h.values[i] <= h.values[RIGHT(i)]) {
            i++;
            printf("\nLOOOL %d LOOOOL\n", h.values[i] < h.values[LEFT(i)] && h.values[i] < h.values[RIGHT(i)]);
        }
        else return 0;
    }

    return 1;
}

// Main para Teste.
int main() {

    Heap h;
    int i, x;

    // Iniciar a Heap.
    initHeap(&h, 1);
    
    // Inserir Elementos na Heap.
    insertHeap(&h, 30);
    insertHeap(&h, 60);
    insertHeap(&h, 40);
    insertHeap(&h, 10);
    insertHeap(&h, 100);
    insertHeap(&h, 20);
    insertHeap(&h, 90);
    insertHeap(&h, 50);
    insertHeap(&h, 80);
    insertHeap(&h, 70);
  
    // Imprimir Elementos da Heap.
    printf("Heap construída (Capacidade %d):\n", h.size);
    for (i = 0; i < h.used; i++)
        printf("%d\n", h.values[i]);

    // Verificar se Heap é OK.
    printf("\nHeap OK se 1. Não OK se 0.\nResultado: %d\n\n", minHeapOK(h));
    
    // Eliminar Elementos da Heap.
    printf("Extracção de Elmentos:\n");
    while (extractMin(&h, &x)) 
        printf("%d\n", x);    
}
