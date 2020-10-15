#include <stdlib.h>
#include <stdio.h>

#define N 5
#define PRETO -1
#define CINZENTO -2
#define BRANCO -3
#define VAZIO -100

typedef struct lista{
    int vertice;
    struct lista *next;
} Nodo, *Lista[N];

typedef struct queue{
    int * values;
    int size;
    int front;
    int back;
    int tamAtual;
}*Queue;

Queue inicializaQueue(int size){
    Queue q = (Queue)malloc(sizeof(struct queue));
    q->values = (int *)malloc(sizeof(int)*size);
    int i;
    for(i=0;i<q->size;i++)q->values[i]=VAZIO;
    q->size = size;
    q->front = 0;
    q->back = 0;
    q->tamAtual = 0;
    return q;
}

void imprimeQueue(Queue q){
    int i;
    printf("Tamanho atual %d\n",q->tamAtual);
    printf("Tamanho total %d\n",q->size);
    for(i=q->front;i<q->back;i++){
        printf("q[%d]=%d\n",i,q->values[i]);
    }
}

int enqueue(Queue q, int v){
    if(q->tamAtual==q->size) return 0;
    else {
        if (q->back==q->size) q->back = 0;
        q->values[q->back++] = v;
        q->tamAtual++;
        return 1;
    }
}

int isEmpty(Queue q){
    if (q->tamAtual==0) return 1;
    else return 0;
}

int dequeue(Queue q,int *v){
    if(q->tamAtual==0) return 0;
    else{
        if (q->front==q->size) q->front = 0;
        *v = q->values[q->front++];
        q->tamAtual--;
        return 1;
    }
}

void inicializaLista(Lista l){
    int i;
    for(i=0;i<N;i++){
        l[i] = NULL;
    }
}



void imprimeLista(Lista l){
    int i;
    for (i=0;i<N;i++){
        printf ("Origem: %d\n",i);
        Nodo *aux = l[i];
        while(aux){
            printf("-->Destino: %d\n",aux->vertice);
            aux = aux->next;
        }
        if(l[i]==NULL) printf("É NULL\n");
    }
}

void insereDLista(Lista l, int o, int d){
    Nodo * n = (Nodo *)malloc(sizeof(Nodo));
    n->vertice = d;
    n->next = l[o];
    l[o] = n;
}



/**
 * Travessia em largura
 */  
void calculaCaminho(Lista l,int cores[],int distancias[],int parent[],int vertice){
    cores = (int *)malloc(sizeof(int)*N);
    distancias = (int *)malloc(sizeof(int)*N);
    Queue q = inicializaQueue(N);
    parent = (int *)malloc(sizeof(int)*N);
    int i;
    for(i=0;i<N;i++){
        cores[i] = BRANCO;
        distancias[i] = 0;
    } 

    cores[vertice] = CINZENTO;
    enqueue(q,vertice);
    while(!(isEmpty(q))){
        int *v = (int *)malloc(sizeof(int));
        dequeue(q,v);
        Nodo * aux = l[*v];
        while(aux){
            if (cores[aux->vertice]==BRANCO){
                cores[aux->vertice] = CINZENTO;
                distancias[aux->vertice] = distancias[*v] +1;
                parent[aux->vertice] = *v;
                enqueue(q,aux->vertice);
            }
            aux = aux->next;
        }
        cores[*v] = PRETO;
    }
}

/**
 * Travessia em profundidade, alinea a , aloritmo de Tarjan
 */ 
int ordenacaoTopologicaAux(Lista l,int orig, int *vis,int *ord,int *p){
    int i;
    Nodo *aux;
    vis[orig] = CINZENTO;
    for(aux=l[orig];aux;aux=aux->next){
        if (vis[aux->vertice]==CINZENTO) return 1;
        if (vis[aux->vertice]==BRANCO){
            if (ordenacaoTopologicaAux(l,aux->vertice,vis,ord,p)) return 1;
        }
    }
    vis[orig] = PRETO;
    ord[*p] = orig;
    *p= *p-1;
    return 0;
}

int ordenacaoTopologica(Lista l,int ord[]){
    int *vis = (int*)malloc(sizeof(int)*N);
    ord = (int*)malloc(sizeof(int)*N);
    int *pos = (int*)malloc(sizeof(int));
    *pos = N-1;
    int i,res;
    for(i=0;i<N;i++) vis[i] = BRANCO;
    for(i=0;i<N;i++){
        if (vis[i]==BRANCO){
            res = ordenacaoTopologicaAux(l,i,vis,ord,pos);
            if (res) return 1;
        }
    }
    return 0;
}

int grauEntradaLista(Lista l, int v){
    int i, counter = 0;
    for(i=0;i<N;i++){
        Nodo * aux = l[i];
        while(aux){
            if(aux->vertice == v) counter++;
            aux = aux->next;
        }
    }
    return counter;
}

int ordenacaoKahnAux(Lista l, int i,int *orde, int *pre,int *vis, int *pos){

    vis[i]=CINZENTO;
    Nodo *aux;
    for(aux=l[i];aux;aux=aux->next){
        if (vis[aux->vertice]==CINZENTO && pre[aux->vertice]!=0) return 1;
        if(pre[aux->vertice]>0){
            pre[aux->vertice] = pre[aux->vertice] -1;
            if (ordenacaoKahnAux(l,aux->vertice,orde,pre,vis,pos)) return 1;
        }
    }
    pre[i]=0;
    orde[*pos] = i;
    *pos = (*pos)-1;
    return 0;

}


int ordenacaoKahn(Lista l, int * ord){
    ord = (int*)malloc(sizeof(int)*N);
    int * precedentes = (int*) malloc(sizeof(int)*N);
    int * visitados = (int*)malloc(sizeof(int)*N);
    int res;
    int i;
    int * pos = (int *)malloc(sizeof(int));
    *pos =N-1;
    for(i=0;i<N;i++){
        visitados[i]=BRANCO;
        precedentes[i] = grauEntradaLista(l,i);
    }
    for(i=0;i<N;i++){
        if (precedentes[i]<0 || visitados[i]==BRANCO){
            res = ordenacaoKahnAux(l,i,ord,precedentes,visitados,pos);
            if(res) return 1;
        }
    }
return 0;   
}

int isAciclicoAux(Lista l, int i, int * vis){
    
    vis[i] = CINZENTO;
    Nodo * aux;
    for(aux=l[i];aux;aux= aux->next){
        if(vis[aux->vertice]==CINZENTO){
            return 1;
        } 
        if(vis[aux->vertice]==BRANCO){
            if (isAciclicoAux(l,aux->vertice,vis)) return 1;
        }
    }
    vis[i] = PRETO;
    return 0;
}

int isAciclico(Lista l){
    int * vis = (int*)malloc(sizeof(int)*N);
    int i,res;
    for(i=0;i<N;i++) vis[i] = BRANCO;
    for(i=0;i<N;i++){
        if (vis[i]==BRANCO){
            res = isAciclicoAux(l,i,vis);
            if (res) return 0;
        }
    }
    return 1;
}

int succN(Lista l, int v, int dist){
    Queue q = inicializaQueue(N);
    int * vis = (int *)malloc(sizeof(int)*N);
    int i;
    int * distancias = (int *)malloc(sizeof(int)*N);
    for(i=0;i<N;i++){
        vis[i]= BRANCO;
        distancias[i] = 0;
    }
    vis[v] = CINZENTO;
    enqueue(q,v);
    while(!(isEmpty(q))){
        int *ver;
        dequeue(q,ver);
        Nodo * aux = l[*ver];
        while(aux){
            if (vis[aux->vertice]==BRANCO){
                vis[aux->vertice]=CINZENTO;
                enqueue(q,aux->vertice);
                distancias[aux->vertice] = 1 + distancias[*ver];
            }
            aux = aux->next;
        }
        vis[*ver] = PRETO;
    }
    int counter = 0;
    for(i=0;i<N;i++){      
        if (distancias[i]<=dist && v!=i) counter++;
    }
    return counter;
}

int main(){
  
    return 0;
}