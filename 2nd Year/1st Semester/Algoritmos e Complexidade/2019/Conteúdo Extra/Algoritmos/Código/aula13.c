#include <stdio.h>

#define MAXV 10

#define WHITE 0
#define GREY 1
#define BLACK 2

// Listas de Adjacência
typedef struct nodo {
  int dest, peso;
  struct nodo *prox;
} Nodo;
typedef struct {
  int nvert;
  Nodo *adj[MAXV];
} LAdj;

/* Funcionalidade original da Orla
typedef .... Fringe;
Fringe addV(Fringe, int, int);
Fringe nextF(Fringe, int*);
Fringe updateV(Fringe, int, int);
 */

// OBS: Vamos implementar a funcionalidade da orla "inlined" na própria função


int primMST(LAdj *g, int p[], int w[]) {
  int i, imin, v, r=0, cor[g->nvert];
  Nodo *aux;
  int fsize=0, fringe[g->nvert]; // ORLA (stack de vértices)

  // Inicializações...
  for (i=0; i<g->nvert; i++) {
    p[i] = -1;
    cor[i] = WHITE;
  }
  cor[0] = GREY;
  w[0] = 0;
  fringe[fsize++] = 0; //f = addV(f, 0, 0);
  
  //ciclo principal...
  while (fsize>0) {
    // Retirar melhor elemento da orla ("f = nextF(f, &v);"):
    // (1) encontrar mínimo
    imin = 0;
    for (i=1; i<fsize; i++)
      if (w[fringe[i]] < w[fringe[imin]]) imin = i;
    // (2) remover elemento
    v = fringe[imin];
    fringe[imin] = fringe[--fsize];
    // FIM DE "retirar"
    cor[v] = BLACK;
    r += w[v];
    for (aux=g->adj[v]; aux; aux=aux->prox)
      switch (cor[aux->dest])
	{
	case WHITE:
	  cor[aux->dest] = GREY;
	  fringe[fsize++] = aux->dest; //f = addV(f, aux->dest, aux->peso);
	  w[aux->dest] = aux->peso;
	  p[aux->dest] = v;
	  break;
	case GREY:
	  if (aux->peso < w[aux->dest]) {
	    //f = updateV(f, aux->dest, aux->peso);
	    p[aux->dest] = v;
	    w[aux->dest] = aux->peso;
	  }
	  break;
	default:
	  break;
	}
  }
  return r;
}


// Adaptação do algoritmo anterior para cálculo dos caminhos mais curtos
void cmc(LAdj *g, int p[], int w[]) {
  int i, imin, v, cor[g->nvert];
  Nodo *aux;
  int fsize=0, fringe[g->nvert]; // ORLA (stack de vértices)

  // Inicializações
  for (i=0; i<g->nvert; i++) {
    p[i] = -1;
    cor[i] = WHITE;
  }
  cor[0] = GREY;
  w[0] = 0;
  fringe[fsize++] = 0; //f = addV(f, 0, 0);
  
  //ciclo principal...
  while (fsize>0) {
    // Retirar melhor elemento da orla ("f = nextF(f, &v);"):
    // (1) encontrar mínimo
    imin = 0;
    for (i=1; i<fsize; i++)
      if (w[fringe[i]] < w[fringe[imin]]) imin = i;
    // (2) remover elemento
    v = fringe[imin];
    fringe[imin] = fringe[--fsize];
    // FIM DE "retirar"
    cor[v] = BLACK;
    for (aux=g->adj[v]; aux; aux=aux->prox)
      switch (cor[aux->dest])
	{
	case WHITE:
	  cor[aux->dest] = GREY;
	  fringe[fsize++] = aux->dest; //f = addV(f, aux->dest, aux->peso);
	  w[aux->dest] = w[v] + aux->peso;
	  p[aux->dest] = v;
	  break;
	case GREY:
	  if ((w[v]+aux->peso) < w[aux->dest]) {
	    //f = updateV(f, aux->dest, aux->peso);
	    p[aux->dest] = v;
	    w[aux->dest] = w[v]+aux->peso;
	  }
	  break;
	default:
	  break;
	}
  }
}
