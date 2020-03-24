#include <stdlib.h>
#include <stdio.h>
#include "Graphs.h"
#include "QueueBuffer.h"
#include "FringeMinHeap.h"


typedef WEIGHT GraphM[MAX_SIZE][MAX_SIZE];

struct graphL {
	int dest;
	WEIGHT weight;
	struct graphL *next;
};

typedef struct graphL *GraphL[MAX_SIZE];


// Conversions 

void GraphMtoL(GraphM gm, GraphL gl, int size)
{
	int i = 0;
	int j = 0;
	struct graphL *head = NULL, *newNode = NULL;

	for (int i = 0; i < NV; i++) {
		for (j = NV - 1; j >= 0; j--) {
			if (gm[i][j] != NE) {
				newNode = malloc(sizeof(struct graphL));
				newNode->dest = j;
				newNode->weight = gm[i][j];
				newNode->next = head;
				head = newNode;
			}
		}

		gl[i] = head;
		head = NULL;
	}
}


void GraphLtoM(GraphL gl, GraphM gm, int size)
{
	int i = 0;
	int j = 0;
	struct graphL *aux = NULL;

	for (; i < size; i++) {
		for (j = 0, aux = gl[i]; j < size; j++) {
			if (aux != NULL && aux->dest == j) {
				gm[i][j] = aux->weight;
				aux = aux->next;
			}
			else {
				gm[i][j] = NE;
			}
		}
	}
}


int InDegreeL(GraphL gl, int v, int size)
{
	int i = 0;
	int d = 0;
	struct graphL *aux = NULL;

	for (; i < size; i++) {
		for (aux = gl[i]; aux != NULL && aux->dest <= v; aux = aux->next) {
			if (aux->dest == v) {
				d++;
			}
		}
	}

	return d;
}


int InDegreeM(GraphM gm, int v, int size)
{
	int i = 0;
	int d = 0;

	for (; i < size; i++) {
		if (gm[i][v] != NE) {
			d++;
		}
	}

	return d;
}


int OutDegreeL(GraphL gl, int v)
{
	int d = 0;
	struct graphL *aux = NULL;

	for (aux = gl[v]; aux != NULL; aux = aux->next) {
		d++;
	}

	return d;
}


int OutDegreeM(GraphM gm, int v, int size)
{
	int d = 0;
	int j = 0;

	if (v < size) {
		for (; j < size; j++) {
			if (gm[v][j] != NE) {
				d++;
			}
		}
	}

	return d;
}


WEIGHT CapacityL(GraphL gl, int v, int size)
{
	int i = 0;
	int capacity = 0;
	struct graphL *aux = NULL;

	for (; i < size; i++) {
		if (i == v) {
			for (aux = gl[i]; aux != NULL; aux = aux->next) {
				capacity -= aux->weight;
			}
		}
		else {
			for (aux = gl[i]; aux != NULL && aux->dest <= v; aux = aux->next) {
				if (aux->dest == v) {
					capacity += aux->weight;
				}
			}
		}
	}

	return capacity;
}


WEIGHT CapacityM(GraphM gm, int v, int size)
{
	int i = 0;
	int j = 0;
	int capacity = 0;

	for (; i < size; i++) {
		if (i == v) {
			for (j = 0; j < size; j++) {
				if (gm[v][j] != NE) {
					capacity -= gm[v][j];
				}
			}
		}
		else {
			if (gm[i][v] != NE) {
				capacity += gm[i][v];
			}
		}
	}

	return capacity;
}


int MaxCapL(GraphL gl, int size)
{
	int *cap = malloc(sizeof(int) * size);
	int i = 0;
	int k = 0;
	struct graphL *aux = NULL;

	for (; i < size; i++) {
		cap[i] = 0;
	}

	for (i = 0; i < size; i++) {
		for (aux = gl[i]; aux != NULL; aux = aux->next) {
			cap[i] -= aux->weight;
			cap[aux->dest] += aux->weight;
		}
	}

	for (i = 1; i < size; i++) {
		if (cap[i] > cap[k]) {
			k = i;
		}
	}

	free(cap);
	cap = NULL;

	return k;
}


int MaxCapM(GraphM gm, int size)
{
	int *cap = malloc(sizeof(int) * size);
	int i = 0;
	int j = 0;
	int k = 0;

	for (; i < size; i++) {
		cap[i] = 0;
	}

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			if (gm[i][j] != NE) {
				cap[i] -= gm[i][j];
				cap[j] += gm[i][j];
			}
		}
	}

	for (i = 1; i < size; i++) {
		if (cap[i] > cap[k]) {
			k = i;
		}
	}

	free(cap);
	cap = NULL;

	return k;
}


int ColorOKL(GraphL gl, int color[], int size)
{
	int i = 0;
	int r = 1;
	struct graphL *aux = NULL;

	for (; i < size && r == 1; i++) {
		aux = gl[i];

		while (aux != NULL && r == 1) {
			if (color[i] == color[aux->dest]) {
				r = 0;
			}

			aux = aux->next;
		}
	}

	return r;
}


int ColorOKM(GraphM gm, int color[], int size)
{
	int i = 0;
	int j = 0;
	int r = 1;

	for (; i < size && r == 1; i++) {
		for (j = 0; j < size && r == 1; j++) {
			if (gm[i][j] != NE) {
				if (color[i] == color[j]) {
					r = 0;
				}
			}
		}
	}

	return r;
}


void InverseL(GraphL gl, GraphL inverse, int size)
{
	int i = 0;
	struct graphL *aux = NULL;
	struct graphL *p = NULL;
	struct graphL *newNode = NULL;
	struct graphL *previous = NULL;

	for (; i < size; i++) {
		inverse[i] = NULL;
	}

	for (i = 0; i < size; i++) {
		for (aux = gl[i]; aux != NULL; aux = aux->next) {
			newNode = malloc(sizeof(struct graphL));
			newNode->dest = i;
			newNode->weight = aux->weight;

			for (p = inverse[aux->dest]; p != NULL; p = p->next) {
				if (p->dest > newNode->dest) {
					break;
				}

				previous = p;
			}

			if (previous == NULL) {
				newNode->next = NULL;
				inverse[aux->dest] = newNode;
			}
			else {
				newNode->next = p;
				previous->next = newNode;
			}

			previous = NULL;
		}
	}
}


void InverseM(GraphM gm, GraphM inverse, int size)
{
	int i = 0;
	int j = 0;

	for (; i < size; i++) {
		for (j = 0; j < size; j++) {
			inverse[j][i] = gm[i][j];
		}
	}
}


void ClearGraphL(GraphL gl, int size)
{
	int i = 0;
	struct graphL *aux = NULL;

	for (; i < size; i++) {
		while (gl[i] != NULL) {
			aux = gl[i];
			gl[i] = gl[i]->next;
			free(aux);
			aux = NULL;
		}
	}
}


void PrintGraphM(GraphM gm, int size)
{
	int i = 0;
	int j = 0;

	for (; i < size; i++) {
		for (j = 0; j < size; j++) {
			if (gm[i][j] == NE) {
				printf("NE ");
			}
			else {
				printf("%d ", gm[i][j]);
			}
		}

		printf("\n");
	}

	printf("\n\n");
}


void PrintGraphL(GraphL gl, int size)
{
	int i = 0;
	struct graphL *aux = NULL;

	for (; i < size; i++) {
		printf("%d (Dest, Weight) -> ", i);

		aux = gl[i];

		while (aux != NULL) {
			printf("(%d, %d) ", aux->dest, aux->weight);
			aux = aux->next;
		}

		printf("\n");
	}

	printf("\n\n");
}



// Graph traversals

int colors[MAX_SIZE];
int tarjanIndex;

int predecessors[MAX_SIZE];
int visited[MAX_SIZE];
int kahnIndex;


int DFSTarjanL(GraphL g, int v, int tsort[])
{
	int cycle = 0;
	struct graphL *aux = NULL;

	colors[v] = GREY;

	for (aux = g[v]; aux != NULL && cycle == 0; aux = aux->next) {
		if (colors[aux->dest] == GREY) {
			cycle = 1;
		}

		if (colors[aux->dest] == WHITE) {
			cycle = DFSTarjanL(g, aux->dest, tsort);
		}
	}

	colors[v] = BLACK;

	tsort[tarjanIndex--] = v;

	return cycle;
}


int TarjanTopL(GraphL g, int size, int tsort[])
{
	int cycle = 0;
	int i = 0;

	tarjanIndex = size - 1;

	for (; i < size; i++) {
		colors[i] = WHITE;
	}

	for (i = 0; i < size && cycle == 0; i++) {
		if (colors[i] == WHITE) {
			cycle = DFSTarjanL(g, i, tsort);
		}
	}

	return cycle;
}


int DFSKahnL(GraphL g, int v, int tsort[])
{
	int cycle = 0;
	struct graphL *aux = NULL;

	visited[v] = 1;

	for (aux = g[v]; aux != NULL && cycle == 0; aux = aux->next) {
		if (visited[aux->dest] == 1 && predecessors[aux->dest] != 0) {
			cycle = 1;
		}

		if (predecessors[aux->dest] > 0) {
			predecessors[aux->dest]--;
			cycle = DFSKahnL(g, aux->dest, tsort);
		}
	}

	predecessors[v] = 0;

	tsort[kahnIndex--] = v;

	return cycle;
}


int KahnTopL(GraphL g, int size, int tsort[])
{
	int cycle = 0;
	int i = 0;

	kahnIndex = size - 1;

	for (; i < size; i++) {
		predecessors[i] = InDegreeL(g, i, size);
		visited[i] = 0;
	}

	for (i = 0; i < size && cycle == 0; i++) {
		if (predecessors[i] < 0 || visited[i] == 0) {
			cycle = DFSKahnL(g, i, tsort);
		}
	}

	return cycle;
}


int SuccN(GraphL g, int v, int size, int N)
{
	int x = 0;
	int i = 0;
	int vAux = 0;
	struct graphL *aux = NULL;
	LListBuffer l = InitLL();

	for (; i < size; i++) {
		colors[i] = WHITE;
	}

	colors[v] = GREY;
	AddLL(l, v);

	while (EmptyLL(l) == 0 && N > 0) {
		N--;
		RemoveLL(l, &vAux);

		for (aux = g[vAux]; aux != NULL; aux = aux->next) {
			if (colors[aux->dest] == WHITE) {
				x++;
				AddLL(l, aux->dest);
			}
		}
=
		colors[vAux] = BLACK;
	}

	ClearLL(l);

	return x;
}


int DFSConnection(GraphL g, int v, int vDest, WEIGHT section, int *c)
{
	int cycle = 0;
	struct graphL *aux = NULL;

	colors[v] = GREY;

	for (aux = g[v]; aux != NULL && cycle == 0 && *c == 0; aux = aux->next) {
		if (colors[aux->dest] == GREY) {
			cycle = 1;
		}

		if (aux->dest == vDest && aux->weight > section) {
			*c = 1;
		}
		else if (colors[aux->dest] == WHITE && aux->weight > section) {
			cycle = DFSConnection(g, aux->dest, vDest, section, c);
		}
	}

	colors[v] = BLACK;

	return cycle;
}


int Connection(GraphL g, int v1, int v2, int size, WEIGHT section)
{
	int i = 0;
	int c = 0;

	for (; i < size; i++) {
		colors[i] = WHITE;
	}

	DFSConnection(g, v1, v2, section, &c);

	return c;
}


int DFSUnreachable(GraphL g, int v)
{
	int cycle = 0;
	struct graphL *aux;

	colors[v] = GREY;

	for (aux = g[v]; aux != NULL && cycle == 0; aux = aux->next) {
		if (colors[aux->dest] == GREY) {
			cycle = 1;
		}

		if (colors[aux->dest == WHITE]) {
			cycle = DFSUnreachable(g, aux->dest);
		}
	}

	colors[v] = BLACK;

	return cycle;
}


int Unreachable(GraphL g, int o, int size)
{
	int i = 0;
	int r = -1;

	for (; i < size; i++) {
		colors[i] = WHITE;
	}

	DFSUnreachable(g, o);

	for (i = 0; i < size && r == -1; i++) {
		if (colors[i] == WHITE) {
			r = i;
		}
	}

	return r;
}
	