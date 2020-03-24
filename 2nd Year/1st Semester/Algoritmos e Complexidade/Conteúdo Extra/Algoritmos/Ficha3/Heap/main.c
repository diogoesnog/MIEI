#include <stdio.h>
#include "heap.h"


int main(void)
{
	Heap(h) = NewHeap(50);
	int ok = 0;
	int min = 0;

	InsertHeap(h, 10);
	InsertHeap(h, 20);
	InsertHeap(h, 30);
	InsertHeap(h, 40);
	InsertHeap(h, 60);
	InsertHeap(h, 50);
	InsertHeap(h, 70);

	ok = MinHeapOK(h);

	printf("MinHeapOk: %d\n", ok);

	PrintHeap(h);

	ExtractMin(h, &min);

	printf("Min: %d\n", min);

	PrintHeap(h);

	ok = MinHeapOK(h);

	printf("MinHeapOk: %d\n", ok);

	ExtractMin(h, &min);

	PrintHeap(h);

	ExtractMin(h, &min);

	PrintHeap(h);

	ok = MinHeapOK(h);

	printf("MinHeapOk: %d\n", ok);*/

	for (i = 0;)

	Destroy(h);
	getchar();

	return 0;
}