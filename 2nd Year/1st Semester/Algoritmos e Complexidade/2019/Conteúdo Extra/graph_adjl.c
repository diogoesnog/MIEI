#include "graph_adjl.h"
#include <stdlib.h>
#include <stdio.h>

Graph_LA create_GraphLA(int V) {
	Graph_LA g;
	g.V = V;
	g.adj_ls=(Edge**)malloc(MAX_VERTEX*sizeof(Edge*));
	for(int i = 0; i < V; i++) {
		g.adj_ls[i] = NULL;
	}
	return g;
}

void addEdge_GraphLA(Graph_LA g, int s, int d, int w) {
	Edge *new = (Edge*)malloc(sizeof(Edge));
	new->weight=w;
	new->dest=d;
	new->next=g.adj_ls[s];
	g.adj_ls[s]=new;
}

Graph_LA convert_GraphMA_GraphLA(Graph_MA g){
	Graph_LA gnew = create_GraphLA(g.V);
	for(int i=0; i<g.V; i++) {
		for(int j=0; j<g.V; j++) {
			if (g.adj_tab[i*g.V+j] > 0) {
				addEdge_GraphLA(gnew,i,j,g.adj_tab[i*g.V+j]);
			}
		}
	}
	return gnew;
}

Graph_LA convert_GraphVA_GraphLA(Graph_VA g) {
	Graph_LA gnew = create_GraphLA(g.V);
	for(int i=0; i<g.V; i++) {
		for(int j=g.adj_idx[i]; j<g.adj_idx[i+1]; j++) {
			addEdge_GraphLA(gnew,i,g.adj_vec[j],g.wei_vec[j]);
		}
	}
	return gnew;
}

void print_GraphLA(Graph_LA g) {
	printf("|V| = %d\n",g.V);
	for(int i = 0; i < g.V; i++) {
		printf ("(%d) -> ",i);
		Edge *edge = g.adj_ls[i];
		while (edge) {
			printf("(%d,%d) ",edge->dest, edge->weight);
			edge = edge -> next;
		}
		printf ("\n");
	}
}
