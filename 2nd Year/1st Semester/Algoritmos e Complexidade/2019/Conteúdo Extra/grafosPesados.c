#include<stdio.h>
#include<stdlib.h>
#include <limits.h>

#define N 6
#define PRETO 2
#define CINZENTO 1
#define BRANCO 0
#define VAZIO -100

typedef struct lista{
    int vertice;
    int custo;
    struct lista *next;
} Nodo, *Lista[N];

typedef int Fringe[N];

void newFringe(Fringe f){
    int i;
    for(i=0;i<N;i++) f[i] = -1;
}

void addCusto(Fringe f, int vertice,int custo){
    f[vertice] = custo;
}

void updateVertice(Fringe f, int vertice, int custo){
    f[vertice] = custo;
}

int nextF(Fringe f){
    int inim = -1;
    int i;
    for(i=0;i<N;i++){
        if(f[i]>=0){
            if(inim<0 || f[i]<f[inim]) inim = i;
        }
    }
    if (inim>=0) f[inim] = -1;
    return inim;
}

void imprimeFringe(Fringe f){
    int i;
    for(i=0;i<N;i++) printf("f[%d]=%d\n",i,f[i]);
}

void inicializaLista(Lista l){
    int i;
    for(i=0;i<N;i++){
        l[i] = NULL;
    }
}

void imprimeVector(int *p){
    int i;
    for(i=0;i<N;i++){
        printf("p[%d]=%d\n",i,p[i]);
    }
    printf("\n");
}

void imprimeLista(Lista l){
    int i;
    for (i=0;i<N;i++){
        printf ("Origem: %d\n",i);
        Nodo *aux = l[i];
        while(aux){
            printf("-->Destino: %d com custo = %d\n",aux->vertice,aux->custo);
            aux = aux->next;
        }
        if(l[i]==NULL) printf("É NULL\n");
    }
}

void insereDLista(Lista l, int o, int d,int custo){
    Nodo * n = (Nodo *)malloc(sizeof(Nodo));
    n->vertice = d;
    n->custo = custo;
    n->next = l[o];
    l[o] = n;
}

/**
 * Algoritmo de Prim!!
 */

int primMST(Lista l, int * p,int * w){
    int i,v,r=0,fsize,cor[N];
    Fringe f;
    newFringe(f);
    p = (int*)malloc(sizeof(int)*N);
    w = (int*)malloc(sizeof(int)*N);
    for(i=0;i<N;i++){
        p[i] = -1;
        cor[i]=BRANCO;
        
    } 
    cor[0] = CINZENTO;
    w[0] = 0;
    addCusto(f,0,0);
    fsize = 1;

    while(fsize){
        v = nextF(f);
        fsize--;
        cor[v] = PRETO;
        r += w[v];
        Nodo * aux;
        for(aux=l[v];aux;aux= aux->next){
            
            switch (cor[aux->vertice])
            {
                case BRANCO:
                    cor[aux->vertice] = CINZENTO;
                   
                    addCusto(f,aux->vertice,aux->custo);
                    fsize++;
                    w[aux->vertice] = aux->custo;
                    p[aux->vertice] = v;

                    break;
                case CINZENTO:
                    if(w[aux->vertice]>aux->custo){
                        updateVertice(f,aux->vertice,aux->custo);
                        w[aux->vertice] = aux->custo;
                        p[aux->vertice] = v;

                    }
                    break;
                default:
                    break;
            }
        }
    }
        return r;
}

/**
 * Algoritmo de Dijkstra
 */ 
int dijkstra(Lista l, int o, int *p, int *w){
    p =(int*)malloc(sizeof(int)*N);
    w = (int*)malloc(sizeof(int)*N);
    int i,fsize = 0;
    int r = 0;
    int v=0;
    int * cor = (int*)malloc(sizeof(int)*N);
    Nodo *aux;
    Fringe f;
    newFringe(f);

    for(i=0;i<N;i++){
        p[i] = -1;
        cor[i] = BRANCO;
    }
    w[o] = 0;
    addCusto(f,o,w[o]);
    fsize++;

    while(fsize>0){
        v = nextF(f);
        cor[v] = PRETO;
        fsize--;
        r+=w[v];
        for(aux=l[v];aux;aux=aux->next){
            switch(cor[aux->vertice]){
                case BRANCO:
                    cor[aux->vertice] = CINZENTO;
                    w[aux->vertice] = w[v] + aux->custo;
                    p[aux->vertice] = v;
                    addCusto(f,aux->vertice,w[aux->vertice]);
                    fsize++;
                    break;
                case CINZENTO:
                    if (w[aux->vertice]>(w[v]+aux->custo)){
                        w[aux->vertice] = w[v]+aux->custo;
                        p[aux->vertice] = v;
                        updateVertice(f,aux->vertice,w[aux->vertice]);
                    }
                    break;
                default:
                    break;
            }
        }
    }
    return r;
}

void imprimeMatriz(int c[N][N]){
    int i,j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            printf("%d  ",c[i][j]);
        }
        printf("\n");
    }
}

/**
 * Fecho transitivo -  metodo closure
 */
void dfsClosure(Lista l, int s,int d,int c[N][N]){
    Nodo *aux;
    
    for(aux=l[d];aux;aux=aux->next){
        if(c[s][aux->vertice] == 0){
            c[s][aux->vertice] = 1;
            dfsClosure(l,s,aux->vertice,c);
        }
    } 
} 

void transitivoClosure(Lista l, int c[N][N]){
    int i,j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            c[i][j] = 0;
        }
    }
    for(i=0;i<N;i++)
        dfsClosure(l,i,i,c);
}

typedef int Matriz[N][N];

void inicializaMatriz(Matriz m){
    int i,j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            m[i][j]=0;
        }
    }
}

void imprimeMatrizD(Matriz m){
    int i,j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            printf("%d  ",m[i][j]);
        }
        printf("\n");
    }
}

void insereDMatriz(Matriz m,int origem, int destino){
    m[origem][destino] = 1;
}

/**
 * Fecho transitivo
 * Algortimo de Warshall
 */ 
void transitivoWarshall(Matriz m,int c [N][N]){
    int i,j,k;

    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            c[i][j] = m[i][j];
        }
    }

    for(k=0;k<N;k++){
        for(i=0;i<N;i++){
            for(j=0;j<N;j++){
               if (c[i][k] && c[k][j])
                    c[i][j] = 1;
            }
        }
    }
}
int main(){

    return 0;
}