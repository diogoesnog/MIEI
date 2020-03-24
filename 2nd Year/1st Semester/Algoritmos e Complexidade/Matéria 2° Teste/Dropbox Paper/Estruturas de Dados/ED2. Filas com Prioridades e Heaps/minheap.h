#define PARENT(i) (i-1)/2  // Os índices do array começam em 0 
#define LEFT(i) 2*i + 1
#define RIGHT(i) 2*i + 2

typedef int Elem;  // Elementos da Heap em si

typedef struct heap {
 int   size;
 int   used;
 Elem  *values;
} Heap;

void initHeap (Heap *h, int size); 
int  insertHeap (Heap *h, Elem x);
int  extractMin (Heap *h, Elem *x);
int minHeapOK (Heap h); 