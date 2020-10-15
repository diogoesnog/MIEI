#include "graph_adjv.h"
#include <stdlib.h>
#include <stdio.h>

Graph_VA create_GraphVA(int V) {
	Graph_VA g;
	g.V = V;
	g.adj_vec=(int*)malloc(MAX_VERTEX*MAX_VERTEX*sizeof(int));
	g.wei_vec=(int*)malloc(MAX_VERTEX*MAX_VERTEX*sizeof(int));
	g.adj_idx=(int*)malloc((MAX_VERTEX+1)*sizeof(int));
	for(int i = 0; i <= V; i++) {
		g.adj_idx[i] = 0;
	}
	return g;
}

void addEdge_GraphVA(Graph_VA g, int s, int d, int w) {
	int edge_idx = g.adj_idx[s+1];
	int last_edge = g.adj_idx[g.V]-1;
    for(int i = last_edge; i >= edge_idx; i--) {
    	g.adj_vec[i+1] = g.adj_vec[i];
    	g.wei_vec[i+1] = g.wei_vec[i];
    }
    g.adj_vec[edge_idx] = d;
    g.wei_vec[edge_idx] = w;
    for(int i = s+1; i<=g.V; i++)
    	g.adj_idx[i]++;
}

Graph_VA convert_GraphLA_GraphVA(Graph_LA g) {
	Graph_VA gnew = create_GraphVA(g.V);
	int edge_count=0;
	for(int i = 0; i < g.V; i++) {
		gnew.adj_idx[i] = edge_count;
		Edge *edge = g.adj_ls[i];
		while (edge) {
	    	gnew.adj_vec[edge_count] = edge->dest;
   			gnew.wei_vec[edge_count] = edge->weight;
   			edge_count++;
			edge = edge -> next;
		}
	}
	gnew.adj_idx[g.V] = edge_count;
	return gnew;
}

Graph_VA convert_GraphMA_GraphVA(Graph_MA g) {
	Graph_VA gnew = create_GraphVA(g.V);
	int edge_count=0;
	for(int i=0; i<g.V; i++) {
		gnew.adj_idx[i] = edge_count;
		for(int j=0; j<g.V; j++) {
			if (g.adj_tab[i*g.V+j] > 0) {
		    	gnew.adj_vec[edge_count] = j;
    			gnew.wei_vec[edge_count] = g.adj_tab[i*g.V+j];
    			edge_count++;
			}
		}
	}
	gnew.adj_idx[g.V] = edge_count;
	return gnew;
}

void print_GraphVA(Graph_VA g) {
	printf("|V| = %d\n",g.V);
	for(int i = 0; i < g.V; i++) {
		printf ("(%d) -> ",i);
		for(int j=g.adj_idx[i]; j<g.adj_idx[i+1]; j++) {
			printf("(%d,%d) ",g.adj_vec[j],g.wei_vec[j]);
		}
		printf ("\n");
	}
}
