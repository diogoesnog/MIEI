#include <stdlib.h>
#include <stdio.h>
#include "Kruskal.h"


/* Esta estrutura é diferente da dos grafos normais.
 * Usei esta estrutura para simplificar o problema. Podem usar as outras
 * estruturas normais para os grafos mas antes de aplicar o algoritmo de 
 * Kruskal convertam-nas para um array deste género.
 */

typedef struct edge {
	Vertex source;
	Vertex dest;
	Weight weight;
} *Edge;


struct graphK {
	int V;
	int E;
	int index;
	Edge edges;
};


typedef struct set {
	Vertex parent;
	int rank;
} *Set;


GraphK NewGraphK(int V, int E)
{
	GraphK g = malloc(sizeof(struct graphK));

	g->V = V;
	g->E = E;
	g->index = 0;
	g->edges = malloc(E * sizeof(struct edge));

	return g;
}


void AddEdgeK(GraphK g, Vertex source, Vertex dest, Weight weight)
{
	if (g != NULL && g->edges != NULL && g->index < g->E) {
		g->edges[g->index].source = source;
		g->edges[g->index].dest = dest;
		g->edges[g->index++].weight = weight;
	}
}


void PrintGraphK(GraphK g)
{
	int i = 0;

	if (g != NULL && g->edges != NULL) {
		for (; i < g->index; i++) {
			printf("%d -- %d : %d\n", g->edges[i].source, g->edges[i].dest,
				   g->edges[i].weight);
		}

		printf("\n");
	}
}


void ClearGraphK(GraphK g)
{
	if (g != NULL) {
		if (g->edges != NULL) {
			free(g->edges);
			g->edges = NULL;
		}

		free(g);
		g = NULL;
	}
}


int EdgeComp(const void* a, const void* b)
{
	Edge a1 = (Edge)a;
	Edge b1 = (Edge)b;
	
	return a1->weight > b1->weight;
}


Vertex Find(Set s, Vertex v)
{
	if (s[v].parent != v) {
		s[v].parent = Find(s, s[v].parent);
	}

	return s[v].parent;
}


void Union(Set s, Vertex x, Vertex y)
{
	Vertex xroot = Find(s, x);
	Vertex yroot = Find(s, y);

	if (s[xroot].rank < s[yroot].rank) {
		s[xroot].parent = yroot;
	}
	else if (s[xroot].rank > s[yroot].rank) {
		s[yroot].parent = xroot;
	}

	else{
		s[yroot].parent = xroot;
		s[xroot].rank++;
	}
}


void KruskalMST(GraphK g)
{
	int i = 0;
	int size = 0;
	Vertex x = 0;
	Vertex y = 0;
	Set s = NULL;
	Edge result = malloc(g->V * sizeof(struct edge));
	struct edge aux;

	qsort(g->edges, g->E, sizeof(struct edge), EdgeComp);

	s = malloc(g->V * sizeof(struct set));

	for (; i < g->V; i++) {
		s[i].parent = i;
		s[i].rank = 0;
	}

	for (i = 0; i < g->E; i++) {
		aux = g->edges[i];

		x = Find(s, aux.source);
		y = Find(s, aux.dest);

		if (x != y) {
			result[size++] = aux;
			Union(s, x, y);
		}
	}

	// O print não devia estar aqui, foi só para testar

	for (i = 0; i < size; i++) {
		printf("%d -- %d : %d\n", 
			   result[i].source, result[i].dest, result[i].weight);
	}

	printf("\n");

	free(result);
	result = NULL;
}