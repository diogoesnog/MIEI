#include <stdlib.h>
#include "FringeMinHeap.h"


typedef struct elem {
	Vertex vertex;
	Weight weight;
} *Elem;


struct fringe {
	int index;
	Elem values;
};


void Swap(Elem h[], int a, int b)
{
	int i = h[a];

	h[a] = h[b];
	h[b] = i;
}


void BubbleUp(Elem h[], int i)
{
	while (i != 0 && h[i]->weight < h[PARENT(i)]->weight) {
		Swap(h, i, PARENT(i));
		i = PARENT(i);
	}
}


void BubbleDown(Elem h[], int n)
{
	int i = 0;
	int min = 0;

	while (LEFT(i) < n) {
		min = h[i]->weight < h[LEFT(i)]->weight ? i : LEFT(i);

		if (RIGHT(i) < n) {
			min = h[min]-> weight< h[RIGHT(i)]->weight ? min : RIGHT(i);
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


Fringe NewFringe(int size)
{
	Fringe f = malloc(sizeof(struct fringe));

	f->index = 0;
	f->values = malloc(size * (sizeof(struct elem)));

	return f;
}


Fringe AddV(Fringe f, Vertex vertex, Weight weight)
{
	if (f != NULL && f->values != NULL) {
		f->values[f->index].vertex = vertex;
		f->values[f->index++].weight = weight;

		BubbleUp(f->values, f->index - 1);
	}

	return f;
}


Fringe UpdateV(Fringe f, Vertex vertex, Weight weight)
{
	int i = 0;
	int updated = 0;

	if (f != NULL && f->values != NULL) {
		for (; i < f->index && updated == 0; i++) {
			if (f->values[i].vertex == vertex) {
				f->values[i].weight = weight;
				updated = 1;
			}
		}

		if (updated == 1) {
			if (i != 0 && f->values[PARENT(i)].weight > f->values[i].weight) {
				BubbleUp(f->values, i);
			}
			else if ((LEFT(i) < f->index && f->values[LEFT(i)].weight < f->values[i].weight) ||
				     (RIGHT(i) < f->index && f->values[RIGHT(i)].weight < f->values[i].weight)) {
				BubbleDown(f->values, f->index);
			}
		}
	}

	return f;
}


Fringe NextV(Fringe f, Vertex *vertex)
{
	if (f != NULL && f->values != NULL && f->index > 0) {
		*vertex = f->values[0].vertex;
		f->values[0] = f->values[f->index - 1];
		(f->index)--;
		BubbleDown(f->values, f->index);
	}

	return f;
}


void ClearFringe(Fringe f)
{
	if (f != NULL) {
		if (f->values != NULL) {
			free(f->values);
			f->values = NULL;
		}

		free(f);
		f = NULL;
	}
}