/** 
 * @author (Diogo Nogueira)
 * @version (01.04.2019)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct listaligada {
    int valor;
    struct lligada *proxima;
} *ListaLigada;

// Questão 1

int tamanaho(ListaLigada lista){

    int tamanho=0;
    
    while(lista){
        tamanho++;
        lista=lista->proxima;
    }
    
    return tamanho;
}

// Questão 2

void freeL(ListaLigada lista){

    ListaLigada auxiliar;

    while(lista){
        auxiliar=lista->proxima;
        free(lista);
        lista=auxiliar;
    }
}

// Questão 3

void imprimeL (ListaLigada lista){

    int elemento;

    while(l){
        elemento=lista->valor;
        printf("Elemento = %s\n", elemento);
        lista=lista->proxima;
    }

    printf("Fim da Lista Ligada.\n")
}

// Questão 4

LInt reverseL (LInt l){
    
    LInt lista1 = NULL;
    LInt auxiliar = NULL;
    
    while(l){
        auxiliar = l->prox;
        l->prox = lista1;
        lista1 = l;
        l = auxiliar;
    }
    
    return lista1;
}

// Questão 5

void insertOrd (LInt *l, int x){

    while(*l && (*l)->valor<x) l = &((*l)->prox);
    
    LInt novaLista = malloc(sizeof(struct lligada));
    novaLista->valor = x;
    novaLista->prox = (*l);
    
    (*l) = novaLista;
}

// Questão 6

int removeOneOrd (LInt *l, int x){

    int resultado = 1; // Elemento não existe.
    
    while(*l && (*l)->valor!=x) l = &((*l)->prox);
    
    if(*l != NULL){
        LInt novaLista = malloc(sizeof(struct lligada));
        novaLista = (*l)->prox;
        free(*l);
        (*l) = novaLista;
        
        resultado = 0;
    }

    return resultado;
}

// Questão 7

// Questão 8

// Questão 9

// Questão 10

int removeAll (LInt *l, int x){

    int celulasRemovidas = 0;

    while(*l){
        
        // Basta colocar a apontar para o próximo. 
        // Não há necessidade de colocar numa auxiliar o próximo, e fazer free da atual.
        if((*l)->valor == x){
            (*l) = (*l)->prox;
            celulasRemovidas++;
        }
        else l = &((*l)->prox);
    }
    
    return celulasRemovidas;
}

// Questão 11

int existeValor(int valores[], int x){
   
    int i;
    int resultado = 0;
    
    for(i=0; valores[i]!=0; i++){
        if(valores[i]==x) resultado=1;
    }
    
    return resultado;
}

int removeDups (LInt *l){
    
    LInt temporario = (*l);
    int numListas;

    for(numListas=0; temporario!=NULL; temporario = temporario->prox)
        numListas++;
        
    int valores[numListas];
    numListas = 0;
    int i = 0;
    
    while(*l){
        
        if(existeValor(valores, (*l)->valor)){
            (*l) = (*l)->prox;
            numListas++;
        }
        else{
            valores[i] = (*l)->valor;
            i++;
            l = &((*l)->prox);
        }
    }
    
    return numListas;
}

// Questão 12

int removeMaiorL (LInt *l){

    int maiorElemento = 0;
    LInt temporaria = (*l);
    
    // Retiramos o maior elemento da Lista Ligada.
    while(temporaria){
        if(temporaria->valor > maiorElemento) maiorElemento = temporaria->valor;
        temporaria = temporaria->prox;
    }
    
    while(*l){
        
        if((*l)->valor == maiorElemento){
            // Assim já estamos a apontar para o próximo.
            (*l)= (*l)->prox;
            return maiorElemento;
        }
        else l = &((*l)->prox);
    }
}

// Questão 13

void init (LInt *l){
    
    // Vamos até à penúltima lista.
    // Não contamos coma última que em si é NULL.
	while((*l)->prox !=NULL) l = &((*l)->prox);
	
	free(*l);
	*l = NULL;
}

// Questão 14

void appendL (LInt *l, int x){

    while(*l) l = &((*l)->prox);
    
    // Como em si a última lista é NULL, ou seja, não está inicializada, precisamos de alocar espaço.
    (*l) = malloc(sizeof(struct lligada));
    
    (*l)->valor = x;
    (*l)->prox = NULL;
}

// Questão 15

void concatL (LInt *a, LInt b){

    while(*a) a = &((*a)->prox);
    
    (*a) = malloc(sizeof(struct lligada));

    (*a) = b;
}

// Questão 16

LInt cloneL (LInt l){

    LInt clone;
    LInt *auxiliar = &clone;

        while(l){

            *auxiliar = malloc(sizeof(struct lligada));
            (*auxiliar->valor) = l->valor;
            auxiliar = &((*auxiliar)->prox);

            l=l->prox;
        } 

        *auxiliar = NULL;

        return clone;
}

// Questão 17

LInt cloneRev (LInt l){

	LInt clone = NULL;
    LInt temporaria;

	for (clone = NULL; l; l = l->prox){

		temporaria = clone;

		clone = malloc(sizeof(struct lligada));
		clone->valor = l->valor;
		clone->prox = temporaria;
	}

	return clone;
}

// Questão 18

int maximo (LInt l){
    
    int maiorValor = 0;
    
    while(l){
        
        if(l->valor > maiorValor) maiorValor = l->valor;
        
        l=l->prox;
    }
    
    return maiorValor;
}

// Questão 19

int take (int n, LInt *l){

    int tamanhoLista = 0;
    
    while(*l && n>0){

        l = &((*l)->prox);
        n--;
        tamanhoLista++;
    }
    
    while(*l){
        
        LInt novaLista = malloc(sizeof(struct lligada));
        novaLista = (*l)->prox;
        free(*l);
        (*l) = novaLista;
    }
    
    return tamanhoLista;
}

// Questão 20

int drop(int n, LInt *l){

    int elementosRemovidos = 0;

    while(*l && n>0){

        LInt novaLista = malloc(sizeof(struct lligada));
        novaLista = (*l)->prox;
        free(*l);
        (*l) = novaLista;
        
        n--;
        elementosRemovidos++;
    }

    return elementosRemovidos;
}

// Questão 21

LInt Nforward (LInt l, int N){

	while (N){
		l = l->prox;
		N--;
	}

	return l;
}

// Questão 22

int listToArray (LInt l, int v[], int N){
   
   int elementosPreenchidos = 0;
   
   while(l && N>0){
       v[elementosPreenchidos] = l->valor;
       l = l->prox;
       
       elementosPreenchidos++;
       N--;
   }
   
   v[elementosPreenchidos] = '\0';
   
   return elementosPreenchidos;
}

// Questão 23

LInt arrayToList (int v[], int N){
    
    LInt lista;
    LInt *auxiliar = &lista;

    int i = 0;
    
    while(N>0){
        
        (*auxiliar) = malloc(sizeof(struct lligada));
        (*auxiliar)->valor = v[i];
        auxiliar = &((*auxiliar)->prox);
        
        i++;
        N--;
    }
    
    *auxiliar = NULL;
    
    return lista;
}

// Questão 24

LInt somasAcL (LInt l) {

    LInt listaAcumulados;
    LInt *auxiliar = &listaAcumulados;
    
    int valor = 0;
    
    while(l){
        
        valor = valor + l->valor;
        
        (*auxiliar) = malloc(sizeof(struct lligada));
        (*auxiliar)->valor = valor;
        
        auxiliar = &((*auxiliar)->prox);
        l = l->prox;
    }
    
    *auxiliar = NULL;
    
    return listaAcumulados;
}

// Questão 25

void remreps (LInt l){

    LInt auxiliar;
    
    while(l){
        
        auxiliar = l->prox;
        
        while(auxiliar && l->valor == auxiliar->valor){
            LInt temporaria = malloc(sizeof(struct lligada));
            temporaria = auxiliar->prox;
            free(auxiliar);
            auxiliar = temporaria;
        }
        
        l->prox = auxiliar;
        l = l->prox;
    }
 
}

// Questão 26

// Questão 27

LInt parte (LInt l){
    
    LInt listaPares;
    LInt *auxiliarPares = &listaPares;
    
    LInt *auxiliarImpares = &l;
    
    while(*auxiliarImpares){
        
        if((*auxiliarImpares)->valor % 2 != 0){
            auxiliarImpares = &((*auxiliarImpares)->prox);
        }
        else{
            (*auxiliarPares) = (*auxiliarImpares);
            auxiliarPares = &((*auxiliarPares)->prox);
            
            (*auxiliarImpares) = (*auxiliarImpares)->prox;
        }
    }
    
    (*auxiliarPares) = NULL;
    
    return listaPares;
}