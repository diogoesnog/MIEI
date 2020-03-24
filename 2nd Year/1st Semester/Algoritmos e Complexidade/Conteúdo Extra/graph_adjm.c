#include "graph_adjm.h"
#include <stdlib.h>
#include <stdio.h>

Graph_MA create_GraphMA(int V) {
	Graph_MA g;
	g.V = V;
	g.adj_tab=(int*)malloc(MAX_VERTEX*MAX_VERTEX*sizeof(int));
	for(int i = 0; i < V; i++) {
		for(int j = 0; j < V; j++) {
			g.adj_tab[i*g.V+j] = 0;
		}
	}
	return g;
}

void addEdge_GraphMA(Graph_MA g, int s, int d, int w) {
	g.adj_tab[s*g.V+d]=w;
}

Graph_MA convert_GraphLA_GraphMA(Graph_LA g) {
	Graph_MA gnew = create_GraphMA(g.V);
	for(int i = 0; i < g.V; i++) {
		Edge *edge = g.adj_ls[i];
		while (edge) {
			addEdge_GraphMA(gnew, i, edge->dest, edge->weight);
			edge = edge -> next;
		}
	}
	return gnew;
}

Graph_MA convert_GraphVA_GraphMA(Graph_VA g) {
	Graph_MA gnew = create_GraphMA(g.V);
	for(int i=0; i<g.V; i++) {
		for(int j=g.adj_idx[i]; j<g.adj_idx[i+1]; j++) {
			addEdge_GraphMA(gnew,i,g.adj_vec[j],g.wei_vec[j]);
		}
	}
	return gnew;
}

void print_GraphMA(Graph_MA g) {
	printf("|V| = %d\n",g.V);
	for(int i = 0; i < g.V; i++) {
		printf ("(%d) -> ",i);
		for(int j = 0; j < g.V; j++) {
			if (g.adj_tab[i*g.V+j] > 0)
				printf("(%d,%d) ", j, g.adj_tab[i*g.V+j]);
		}
		printf ("\n");
	}
}

