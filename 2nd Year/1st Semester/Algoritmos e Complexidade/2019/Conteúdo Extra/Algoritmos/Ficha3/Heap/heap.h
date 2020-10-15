#ifndef heap_h
#define heap_h

#define PARENT(i) (i - 1) / 2
#define LEFT(i)   2 * i + 1
#define RIGHT(i)  2 * i + 2


typedef struct heap *Heap;
typedef int Elem;


Heap NewHeap(int size);
int InsertHeap(Heap, Elem);
int ExtractMin(Heap, Elem*);
int MinHeapOK(Heap);
void Destroy(Heap);
void PrintHeap(Heap);

#endif
