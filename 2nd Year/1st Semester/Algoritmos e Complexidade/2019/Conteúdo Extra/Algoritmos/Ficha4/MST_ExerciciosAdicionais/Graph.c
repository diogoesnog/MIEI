#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "Graph.h"


struct edge {
	Vertex dest;
	Weight weight;
	struct edge *next;
};


void NewGraph(Graph g)
{
	int i = 0;

	for (; i < MAX_V; i++) {
		g[i] = NULL;
	}
}


void AddEdge(Graph g, int vertex, Vertex dest, Weight weight)
{
	struct edge *p = NULL;
	struct edge *previous = NULL;
	struct edge *newE = NULL;

	if (vertex >= 0 && vertex < MAX_V) {
		p = g[vertex];

		for (; p != NULL && p->dest < dest; previous = p, p = p->next);

		newE = malloc(sizeof(struct edge));
		newE->dest = dest;
		newE->weight = weight;

		if (previous == NULL) {
			g[vertex] = newE;
		}
		else {
			previous->next = newE;
		}

		newE->next = p;
	}
}



void PrintGraph(Graph g)
{
	int i = 0;
	struct edge *p = NULL;

	for (; i < MAX_V; i++) {
		p = g[i];

		printf("%d - (Dest, Weight) - ", i);

		for (; p != NULL; p = p->next) {
			printf("(%d, %d) ", p->dest, p->weight);
		}

		printf("\n");
	}

	printf("\n");
}


void ClearGraph(Graph g)
{
	int i = 0;
	struct edge *p = NULL;

	for (; i < MAX_V; i++) {
		while (g[i] != NULL) {
			p = g[i];
			g[i] = g[i]->next;
			free(p);
			p = NULL;
		}
	}
}


int PrimMST(Graph g, int p[], int w[]) {
	int i = 0;
	int v = 0;
	int r = 0;
	int fsize = 0;
	int col[MAX_V];
	struct edge *x = NULL;
	FringeH f = NewFringeH(MAX_V);

	for (i = 1; i < MAX_V; i++) {
		p[i] = -1;
		w[i] = INT_MAX;
		col[i] = WHITE;
	}

	col[0] = GREY;
	w[0] = 0;
	f = AddFringeH(f, 0, 0);
	fsize = 1;

	while (fsize > 0) {
		fsize--;
		f = NextFringeH(f, &v);
		col[v] = BLACK;
		r += w[v];

		for (x = g[v]; x != NULL; x = x->next) {
			switch (col[x->dest]) {
			case WHITE: 
				col[x->dest] = GREY;
				fsize++;
				f = AddFringeH(f, x->dest, x->weight);
				w[x->dest] = x->weight; 
				p[x->dest] = v;
				break;
			case GREY:
				if (w[x->dest] > x->weight) {
					f = UpdateFringeH(f, x->dest, x->weight);
					w[x->dest] = x->weight; 
					p[x->dest] = v;	
				}

				break;
			default:
				break;
			}
		}
	}

	return r;
}


int DijkstraSP(Graph g, int o, int p[], int w[])
{
	int i = 0;
	int fsize = 0;
	int v = 0;
	int col[MAX_V];
	int r = 0;
	FringeH f = NewFringeH(MAX_V);
	struct edge *x = NULL;

	for (; i < MAX_V; i++) {
		p[i] = -1;
		col[i] = WHITE;

		if (i != o) {
			w[i] = INT_MAX;
		}

		fsize++;
	}

	w[o] = 0;
	f = AddFringeH(f, o, w[o]);

	while (fsize > 0) {
		fsize--;
		f = NextFringeH(f, &v);
		col[v] = BLACK;
		r += w[v];

		for (x = g[v]; x != NULL; x = x->next) {
			switch (col[x->dest]) {
			case WHITE:
				col[x->dest] = GREY;
				fsize++;
				f = AddFringeH(f, x->dest, w[v] + x->weight);
				w[x->dest] = w[v] + x->weight;
				p[x->dest] = v;
				break;
			case GREY:
				if (w[x->dest] > w[v] + x->weight) {
					f = UpdateFringeH(f, x->dest, w[v] + x->weight);
					w[x->dest] = w[v] + x->weight;
					p[x->dest] = v;
				}

				break;
			default:
				break;
			}
		}
	}

	return r;
}


void DFSClosure(Graph g, int s, int d, int c[MAX_V][MAX_V])
{
	struct edge *aux = NULL;

	c[s][d] = 1;

	for (aux = g[d]; aux != NULL; aux = aux->next) {
		if (c[s][aux->dest] == 0) {
			DFSClosure(g, s, aux->dest, c);
		}
	}
}


void TransitiveClosure(Graph g, int c[MAX_V][MAX_V])
{
	int i = 0;
	int j = 0;

	for (; i < MAX_V; i++) {
		for (j = 0; j < MAX_V; j++) {
			c[i][j] = 0;
		}
	}

	for (i = 0; i < MAX_V; i++) {
		DFSClosure(g, i, i, c);
	}
}


void TransitiveClosureW(GraphM g, int c[MAX_V][MAX_V])
{
	int i = 0;
	int j = 0;
	int k = 0;

	for (; i < MAX_V; i++) {
		for (j = 0; j < MAX_V; j++) {
			c[i][j] = g[i][j];
		}
	}

	for (k = 0; k < MAX_V; k++) {
		for (i = 0; i < MAX_V; i++) {
			for (j = 0; j < MAX_V; j++) {
				if (c[i][k] && c[k][j]) {
					c[i][j] = 1;
				}
			}
		}
	}
}


int Excentricity(Graph g, int v)
{
	int color[MAX_V];
	int dist[MAX_V];
	int i = 0;
	int u = 0;
	int r = 0;
	ArrayBuffer arr = InitArray(MAX_V);
	struct edge *x = NULL;

	for (; i < MAX_V; i++) {
		color[i] = WHITE;
		dist[i] = 0;
	}

	color[v] = GREY;
	AddArray(arr, v);

	while (EmptyArray(arr) == 0) {
		RemoveArray(arr, &u);

		for (x = g[u]; x != NULL; x = x->next) {
			if (color[x->dest] == WHITE) {
				color[x->dest] = GREY;
				dist[x->dest] = dist[u] + 1;
				AddArray(arr, x->dest);
			}
		}

		color[u] = BLACK;
	}

	for (i = 0; i < MAX_V; i++) {
		if (r < dist[i]) {
			r = dist[i];
		}
	}

	return r;
}


int DFSHowMany(Graph g, int v, Weight w, int color[MAX_V])
{
	struct edge *x = NULL;
	int r = 0;

	if (w >= 0) {
		color[v] = GREY;
		r++;

		for (x = g[v]; x != NULL; x = x->next) {
			if (color[x->dest] == WHITE) {
				r += DFSHowMany(g, x->dest, w - x->weight, color);
			}
		}

		color[v] = BLACK;
	}

	return r;
}


int HowManyD(Graph g, int v, Weight w)
{
	int color[MAX_V];
	int i = 0;

	for (; i < MAX_V; i++) {
		color[i] = WHITE;
	}

	i = DFSHowMany(g, v, w, color);

	return i;
}


int DFTraversal(Graph g, int o, int f[], int vis[])
{
	int r = 0;
	struct edge *x = NULL;

	vis[o] = 1;

	for (x = g[o]; x != NULL; x = x->next) {
		if (vis[x->dest] == 0) {
			r++;
			f[x->dest] = o;
			r += DFTraversal(g, x->dest, f, vis);
		}
	}

	return r;
}


int TraversalDF(Graph g, int o, int f[])
{
	int vis[MAX_V];
	int i = 0;

	for (; i < MAX_V; i++) {
		vis[i] = 0;
		f[i] = -1;
	}

	i = DFTraversal(g, o, f, vis);

	return i;
}


int Root(int f[MAX_V], int v)
{
	int i = (f[v] == -1) ? v : Root(f, f[v]);

	return i;
}


int InTree(int f[MAX_V], int a, int b) 
{
	int in = (Root(f, a) == Root(f, b)) ? 1 : 0;

	return in;
}


void JoinTree(int f[MAX_V], int a, int b)
{
	f[Root(f, a)] = Root(f, b);
}


int Cost(Graph g, int f[MAX_V])
{
	int c = 0;
	int i = 0;
	int valid = 1;
	struct edge *aux = NULL;

	for (; i < MAX_V && valid == 1; i++) {
		if (f[i] >= 0 && f[i] < MAX_V) {
			for (aux = g[f[i]]; aux != NULL && aux->dest < i; aux = aux->next);

			if (aux == NULL || aux->dest != i) {
				valid = 0;
			}
			else {
				c += aux->weight;
			}
		}
		else if (f[i] >= MAX_V) {
			valid = 0;
		}
	}

	if (valid == 0) {
		c = 0;
	}

	return c;
}


int HeightOf(int f[MAX_V], int v)
{
	int h = (f[v] == -1) ? 0 : 1 + HeightOf(f, f[v]);

	return h;
}


int Height(int f[MAX_V])
{
	int i = 0;
	int h = 0;
	int aux = 0;

	for (; i < MAX_V; i++) {
		aux = HeightOf(f, i);
		h = (aux > h) ? aux : h;
	}

	return h;
}