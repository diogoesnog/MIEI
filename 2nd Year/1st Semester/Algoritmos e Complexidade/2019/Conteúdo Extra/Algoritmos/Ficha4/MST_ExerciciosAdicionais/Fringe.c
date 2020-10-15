#include <stdlib.h>
#include <stdio.h>
#include "Fringe.h"


typedef struct elem {
	Vertex vertex;
	Weight weight;
} Elem;


// Fringe Vector

struct fringeVector {
	int size;
	int index;
	Elem *vec;
};


void LeftShift(Elem *vec, int begin, int end)
{
	for (; begin < end; begin++) {
		vec[begin] = vec[begin + 1];
	}
}


void RightShift(Elem *vec, int begin, int end)
{
	for (; end >= begin; end--) {
		vec[end] = vec[end - 1];
	}
}


void OrdVec(Elem *vec, int size)
{
	Vertex auxV = 0;
	Weight auxW = 0;
	int i = 0;
	int j = 0;

	for (; i < size - 1; i++) {
		for (j = i + 1; j < size; j++)
		if (vec[j].weight < vec[i].weight) {
			auxV = vec[i].vertex;
			auxW = vec[i].weight;
			vec[i].vertex = vec[j].vertex;
			vec[i].weight = vec[j].weight;
			vec[j].vertex = auxV;
			vec[j].weight = auxW;
		}
	}
}


FringeV NewFringeV(int size)
{
	FringeV f = malloc(sizeof(struct fringeVector));

	f->size = size;
	f->index = 0;
	f->vec = malloc(size * sizeof(struct elem));

	return f;
}


FringeV NextFringeV(FringeV f, Vertex *vertex)
{
	if (f != NULL && f->vec != NULL) {
		*vertex = f->vec[0].vertex;
		LeftShift(f->vec, 0, --f->index);
	}

	return f;
}


FringeV AddFringeV(FringeV f, Vertex vertex, Weight weight)
{
	int i = 0;

	if (f != NULL && f->vec != NULL && f->index < f->size) {
		for (; i < f->index; i++) {
			if (f->vec[i].weight >= weight) {
				break;
			}
		}

		RightShift(f->vec, i + 1, f->index++);
		f->vec[i].vertex = vertex;
		f->vec[i].weight = weight;
	}

	return f;
}


FringeV UpdateFringeV(FringeV f, Vertex vertex, Weight weight)
{
	int i = 0;

	if (f != NULL && f->vec != NULL) {
		for (; i < f->index; i++) {
			if (f->vec[i].vertex == vertex) {
				f->vec[i].weight = weight;
				OrdVec(f->vec, f->index);
				break;
			}
		}
	}

	return f;
}


void PrintFringeV(FringeV f)
{
	int i = 0;

	if (f != NULL && f->vec != NULL) {
		for (; i < f->index; i++) {
			printf("Vertex: %d - Weight: %d\n", 
				   f->vec[i].vertex, f->vec[i].weight);
		}

		printf("\n");
	}
}


void ClearFringeV(FringeV f)
{
	if (f != NULL) {
		if (f->vec != NULL) {
			free(f->vec);
			f->vec = NULL;
		}

		free(f);
		f = NULL;
	}
}


// Fringe List


typedef struct list {
	Vertex vertex;
	Weight weight;
	struct list *next;
} *List;


struct fringeList {
	int size;
	int used;
	List list;
};


FringeL NewFringeL(int size)
{
	FringeL f = malloc(sizeof(struct fringeList));

	f->size = size;
	f->used = 0;
	f->list = NULL;

	return f;
}


FringeL NextFringeL(FringeL f, Vertex *vertex)
{
	List aux = NULL;

	if (f != NULL && f->list != NULL) {
		aux = f->list;
		*vertex = f->list->vertex;
		f->list = f->list->next;
		free(aux);
		aux = NULL;
		f->used--;
	}

	return f;
}


FringeL AddFringeL(FringeL f, Vertex vertex, Weight weight)
{
	List p = NULL;
	List previous = NULL;
	List newNode = NULL;

	if (f != NULL && f->used < f->size) {
		p = f->list;
		newNode = malloc(sizeof(struct list));
		newNode->vertex = vertex;
		newNode->weight = weight;

		for (; p != NULL && p->weight < weight; previous = p, p = p->next);

		if (previous == NULL) {
			f->list = newNode;
		}
		else {
			previous->next = newNode;
		}

		newNode->next = p;
		f->used++;
	}

	return f;
}


FringeL UpdateFringeL(FringeL f, Vertex vertex, Weight weight)
{
	List p = NULL;
	List previous = NULL;

	if (f != NULL && f->list != NULL) {
		p = f->list;

		for (; p != NULL && p->vertex != vertex; previous = p, p = p->next);

		if (p != NULL) {
			f->used--;

			if (previous == NULL) {
				f->list = p->next;
			}
			else {
				previous->next = p->next;
			}

			f = AddFringeL(f, vertex, weight);

			free(p);
			p = NULL;
		}
	}

	return f;
}


void PrintFringeL(FringeL f)
{
	List p = NULL;

	if (f != NULL && f->list != NULL) {
		p = f->list;

		for (; p != NULL; p = p->next) {
			printf("Vertex: %d - Weight: %d\n", p->vertex, p->weight);
		}

		printf("\n");
	}
}


void ClearFringeL(FringeL f)
{
	List p = NULL;

	if (f != NULL) {
		if (f->list != NULL) {
			while (f->list != NULL) {
				p = f->list;
				f->list = f->list->next;
				free(p);
				p = NULL;
			}
		}

		free(f);
		f = NULL;
	}
}


// Fringe Heap


struct fringeHeap {
	int size;
	int index;
	Elem *h;
};


void Swap(Elem *h, int a, int b)
{
	Vertex v = h[a].vertex;
	Weight w = h[a].weight;

	h[a].vertex = h[b].vertex;
	h[a].weight = h[b].weight;
	h[b].vertex = v;
	h[b].weight = w;
}


void BubbleUp(Elem *h, int i)
{
	while (i != 0 && h[i].weight < h[PARENT(i)].weight) {
		Swap(h, i, PARENT(i));
		i = PARENT(i);
	}
}


void BubbleDown(Elem *h, int n)
{
	int i = 0;
	int min = 0;

	while (LEFT(i) < n) {
		min = h[i].weight < h[LEFT(i)].weight ? i : LEFT(i);

		if (RIGHT(i) < n) {
			min = h[min].weight < h[RIGHT(i)].weight ? min : RIGHT(i);
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


FringeH NewFringeH(int size)
{
	FringeH f = malloc(sizeof(struct fringeHeap));

	f->size = size;
	f->index = 0;
	f->h = malloc(size * sizeof(struct elem));

	return f;
}


FringeH NextFringeH(FringeH f, Vertex *vertex)
{
	if (f != NULL && f->h != NULL) {
		*vertex = f->h[0].vertex;
		f->h[0].vertex = f->h[f->index - 1].vertex;
		f->h[0].weight = f->h[--f->index].weight;
		BubbleDown(f->h, f->index);
	}

	return f;
}


FringeH AddFringeH(FringeH f, Vertex vertex, Weight weight)
{
	if (f != NULL && f->h != NULL && f->index < f->size) {
		f->h[f->index].vertex = vertex;
		f->h[f->index++].weight = weight;
		BubbleUp(f->h, f->index - 1);
	}

	return f;
}


FringeH UpdateFringeH(FringeH f, Vertex vertex, Weight weight)
{
	int i = 0;

	if (f != NULL && f->h != NULL) {
		for (; i < f->index; i++) {
			if (f->h[i].vertex == vertex) {
				f->h[i].weight = weight;

				if (PARENT(i) >= 0 && f->h[PARENT(i)].weight > weight) {
					BubbleUp(f->h, i);
				}
				else {
					BubbleDown(&f->h[i], f->index - i);
				}
			}
		}
	}

	return f;
}


void PrintFringeH(FringeH f)
{
	int i = 0;

	if (f != NULL && f->h != NULL) {
		for (; i < f->index; i++) {
			printf("Vertex: %d - Weight: %d\n", 
				   f->h[i].vertex, f->h[i].weight);
		}

		printf("\n");
	}
}


void ClearFringeH(FringeH f)
{
	if (f != NULL) {
		if (f->h != NULL) {
			free(f->h);
			f->h = NULL;
		}

		free(f);
		f = NULL;
	}
}