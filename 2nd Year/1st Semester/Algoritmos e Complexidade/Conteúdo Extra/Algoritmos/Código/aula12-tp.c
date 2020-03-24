#include <stdlib.h>
#include <stdio.h>

#define MAXV 10
#define MAXE 50

// Listas de Adjacência
typedef struct nodo {
  int dest, peso;
  struct nodo *prox;
} Nodo;

typedef struct {
  int nvert;
  Nodo *adj[MAXV];
} LAdj;

// Ficha 4, 2.2
int DF_aux(LAdj *g, int o, int d, int v[]) {
  int r=0;
  Nodo *aux;
  v[o] = 1;
  if (o==d) r=1;
  else for (aux=g->adj[o]; aux && !r; aux=aux->prox)
	 if (!v[aux->dest]) r = DF_aux(g, aux->dest, d, v);
  return r;
}

int DF_search(LAdj *g, int o, int d) {
  int i, vis[g->nvert];
  for (i=0; i<g->nvert; i++) vis[i]=0;
  return DF_aux(g, o, d, vis);
}


int travessiaDF_aux (LAdj *g, int o, int f[], int v[]) {
  int r=0;
  Nodo *aux;
  v[o] = 1;
  for (aux=g->adj[o]; aux && !r; aux=aux->prox)
    if (!v[aux->dest]) {
      f[aux->dest] = o;
      r++;
      r += travessiaDF_aux(g, aux->dest, f, v);
    }
  return r;
}
int travessia_DF (LAdj *g, int o, int f[]) {
  int i, vis[g->nvert];
  for (i=0; i<g->nvert; i++) {
    vis[i] = 0;
    f[i] = -1;
  }
  return travessiaDF_aux(g, o, f, vis);
}

// versão iterativa da função...
int travessia_DF2 (LAdj *g, int o, int f[]) {
  int stack[g->nvert], stackC=0;
  int i, vis[g->nvert], count=0;
  Nodo *aux;
  // inicializações...
  for (i=0; i<g->nvert; i++) {
    vis[i] = 0;
    f[i] = -1;
  }
  vis[o] = 1;
  stack[stackC++] = o; // push na stack...
  // ciclo principal
  while (stackC>0) {
    i = stack[--stackC]; // pop da stack
    for (aux=g->adj[i]; aux!=NULL; aux=aux->prox) {
      if (!vis[aux->dest]) {
	f[aux->dest] = i;
	vis[aux->dest] = 1;
	stack[stackC++] = aux->dest; // push de sucessor
	count++;
      }
    }
  }
  
  return count;
}

int travessia_BF (LAdj *g, int o, int f[]) {
  int queue[g->nvert], queueI=0, queueC=0;
  int i, vis[g->nvert], count=0;
  Nodo *aux;
  // inicializações...
  for (i=0; i<g->nvert; i++) {
    vis[i] = 0;
    f[i] = -1;
  }
  vis[o] = 1;
  queue[queueI+queueC++] = o; // enqueue...
  // ciclo principal
  while (queueC>0) {
    i = queue[queueI++]; queueC--; // dequeue
    for (aux=g->adj[i]; aux!=NULL; aux=aux->prox) {
      if (!vis[aux->dest]) {
	f[aux->dest] = i;
	vis[aux->dest] = 1;
	queue[queueI+queueC++] = aux->dest; // enqueue
	count++;
      }
    }
  }
  return count;
}

int kahn(LAdj *g, int ord[]) {
  int i, count=0;
  Nodo *aux;
  int gE[g->nvert];
  int stack[g->nvert], stackC=0;
  // calcular graus de entrada
  for (i=0; i<g->nvert; i++) gE[i]=0;
  for (i=0; i<g->nvert; i++) {
    for (aux=g->adj[i]; aux!=NULL; aux=aux->prox) {
      gE[aux->dest]++;
    }
  }
  // determinar candidatos à ordenação
  for (i=0; i<g->nvert; i++)
    if (gE[i]==0) stack[stackC++] = i;
  // ciclo principal
  while (stackC>0) {
    i = stack[--stackC];
    ord[count++] = i;
    for (aux=g->adj[i]; aux!=NULL; aux=aux->prox) {
      gE[aux->dest]--;
      if (gE[aux->dest]==0) stack[stackC++] = aux->dest;
    }
  }
  return count;
}



