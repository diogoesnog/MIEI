#include <stdlib.h>
#include <stdio.h>

#define MAXV 10
#define MAXE 50

// Matrizes de Adjacência
typedef struct {
  int nvert;
  int peso[MAXV][MAXV];
} MAdj;

// Listas de Adjacência
typedef struct nodo {
  int dest, peso;
  struct nodo *prox;
} Nodo;

typedef struct {
  int nvert;
  Nodo *adj[MAXV];
} LAdj;

// Vectores de Adjacência
typedef struct {
  int nvert;
  int adj[MAXV+1];
  int dest[MAXE];
  int peso[MAXE];
} VAdj;

// CONVERSÕES

// MAdj => LAdj
void madj2ladj(MAdj *g1, LAdj *g2) {
  int i,j;
  Nodo *aux;
  g2->nvert = g1->nvert;
  for (i=0; i<g1->nvert; i++) {
    g2->adj[i] = NULL;
    for (j=0; j<g1->nvert; j++) {
      if (g1->peso[i][j] != 0) {
	aux = (Nodo*) malloc(sizeof(Nodo));
	aux->dest = j;
	aux->peso = g1->peso[i][j];
	aux->prox = g2->adj[i];
	g2->adj[i] = aux;
      }
    }
  }
}

// LAdj => VAdj
void ladj2vadj(LAdj *g1, VAdj *g2) {
  int i, j=0;
  Nodo *aux;
  g2->nvert = g1->nvert;
  for (i=0; i<g1->nvert; i++) {
    g2->adj[i] = j;
    for (aux=g1->adj[i]; aux!=NULL; aux=aux->prox) {
      g2->dest[j] = aux->dest;
      g2->peso[j] = aux->peso;
      j++;
    }
  }
  g2->adj[i] = j;
}

// VAdj => MAdj
void vadj2madj(VAdj *g1, MAdj *g2) {
  int i, j;

  for (i=0; i<g1->nvert; i++) {
    // limpa linha da matriz
    for (j=0; j<g1->nvert; j++) g2->peso[i][j] = 0;
    // insere sucessores
    for (j=g1->adj[i]; j<g1->adj[i+1]; j++) {
      g2->peso[i][g1->dest[j]] = g1->peso[j];
    }
  }
}

// Capacidade de um vértice (LAdj)
int cap(LAdj *g, int v) {
  int i, cap=0;
  Nodo *aux;
  for (i=0; i<g->nvert; i++) {
    for (aux=g->adj[i]; aux!=NULL; aux=aux->prox) {
      if (v==i) cap -= aux->peso;
      if (v==aux->dest) cap += aux->peso;
    }
  }
  return cap;
}

// Vertice com maior Capacidade (LAdj)
int maxcap(LAdj *g) {
  int i, cap[g->nvert], imax;
  Nodo *aux;
  // inicialização de capacidades
  for (i=0; i<g->nvert; i++) cap[i] = 0;
  // calculo das capacidades
  for (i=0; i<g->nvert; i++) {
    for (aux=g->adj[i]; aux!=NULL; aux=aux->prox) {
      cap[i] -= aux->peso;
      cap[aux->dest] += aux->peso;
    }
  }
  // calcula vértice com máxima capacidade
  imax = 0;
  for (i=1; i<g->nvert; i++)
    if (cap[i] > cap[imax]) imax = i;
  
  return imax;
}










