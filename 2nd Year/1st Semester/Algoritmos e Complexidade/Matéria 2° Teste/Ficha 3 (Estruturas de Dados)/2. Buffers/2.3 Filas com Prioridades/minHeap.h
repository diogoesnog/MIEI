#ifndef minHeap_h
#define minHeap_h

// Estruturas definidas

#define PARENT(i) (i - 1) / 2
#define LEFT(i)   2 * i + 1
#define RIGHT(i)  2 * i + 2


typedef struct heap{
	int tamanho;
	int usados;
	int *valores;
} Heap;

// Métodos a Implementar

Heap* newHeap(int tamanho);
int insertHeap(Heap*, int elemento);
int extractMin(Heap*, int *elemento);

#endif 

