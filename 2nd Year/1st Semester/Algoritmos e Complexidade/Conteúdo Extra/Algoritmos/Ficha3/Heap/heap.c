#include <stdlib.h>
#include <stdio.h>
#include "heap.h"


struct heap {
	int size;
	int used;
	Elem *values;
};


void Swap(Elem h[], int a, int b)
{
	int i = h[a];

	h[a] = h[b];
	h[b] = i;
}


void BubbleUp(Elem h[], int i)
{
	while (i != 0 && h[i] < h[PARENT(i)]) {
		Swap(h, i, PARENT(i));
		i = PARENT(i);
	}
}


void BubbleDown(Elem h[], int n)
{
	int i = 0;
	int min = 0;

	while (LEFT(i) < n) {
		min = h[i] < h[LEFT(i)] ? i : LEFT(i);

		if (RIGHT(i) < n) {
			min = h[min] < h[RIGHT(i)] ? min : RIGHT(i);
		}

		if (min != i) {
			Swap(h, i, min);
			i = min;
		}
		else {
			break;
		}
	}
}


int MinHeapOKAux(Elem h[], int i, int n)
{
	int okL = 0;
	int okR = 0;

	if (LEFT(i) >= n) {
		okL = 1;
		okR = 1;
	}
	else {
		if (h[i] <= h[LEFT(i)]) {
			okL = MinHeapOKAux(h, LEFT(i), n);

			if (RIGHT(i) < n) {
				if (h[i] <= h[RIGHT(i)]) {
					okR = MinHeapOKAux(h, RIGHT(i), n);
				}
				else {
					okR = 0;
				}
			}
			else {
				okR = 1;
			}
		}
		else {
			okL = 0;
		}
	}

	return ((okL == 1 && okR == 1) ? 1 : 0); 
}


Heap NewHeap(int size)
{
	Heap h = malloc(sizeof(struct heap));

	h->size = size;
	h->used = 0;
	h->values = calloc(size, sizeof(Elem));

	return h;
}


int InsertHeap(Heap h, Elem e)
{
	int r = 0;

	if (h != NULL && h->values != NULL) {
		if (h->used == h->size) {
			h->size *= 2;
			h->values = realloc(h->values, h->size * sizeof(Elem));
		}

		h->values[h->used++] = e;

		BubbleUp(h->values, h->used - 1);

		r++;
	}

	return r;
}


int ExtractMin(Heap h, Elem *e)
{
	int r = 0;

	if (h != NULL && h->values != NULL && h->used > 0) {
		r++;
		*e = h->values[0];
		h->values[0] = h->values[h->used - 1];
		(h->used)--;
		BubbleDown(h->values, h->used);
	}

	return 0;
}


int MinHeapOK(Heap h)
{
	int r = 1;

	if (h != NULL && h->values != NULL && h->used > 0) {
		r = MinHeapOKAux(h->values, 0, h->used);
	}

	return r;
}


void Destroy(Heap h)
{
	if (h != NULL) {
		if (h->values != NULL) {
			free(h->values);
			h->values = NULL;
		}

		free(h);
		h = NULL;
	}
}


void PrintHeap(Heap h)
{
	int i = 0;

	if (h != NULL && h->values != NULL) {
		for (; i < h->used; i++) {
			printf("%d ", h->values[i]);
		}

		printf("\n");
	}
}