/** 
 * @author (Diogo Nogueira)
 * @version (28.05.2019)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Questão 28

int altura (ABin a){

    int resultado = 0;
    int alturaDireita;
    int alturaEsquerda;
    
    if(a){
        alturaDireita = altura(a->dir);
        alturaEsquerda = altura(a->esq);
        
        if(alturaDireita>alturaEsquerda) resultado = 1+alturaDireita;
        else resultado = 1+alturaEsquerda;
    }
    
    return resultado;
}

// Questão 29

ABin cloneAB (ABin a) {

    ABin novaArvore;
    
    if(a == NULL) novaArvore = NULL;
    else{
        novaArvore = malloc(sizeof(struct nodo));
        novaArvore->valor = a->valor;
        novaArvore->dir = cloneAB(a->dir);
        novaArvore->esq = cloneAB(a->esq);
    }

    return novaArvore;
}

// Questão 30

void mirror (ABin *a) {
    
	if (*a){
	    
		ABin temporariaEsquerda;
		temporariaEsquerda = (*a)->esq;
	
		(*a)->esq = (*a)->dir;
		(*a)->dir = temporariaEsquerda;
		
		mirror (&((*a)->esq));
		mirror (&((*a)->dir));
	}
}

// Questão 31

// Questão 32

// Questão 33

// Questão 34

int minimo(int a, int b) {
    if(a>b) return b;
    else return a;
}

int depth (ABin a, int x) {

    int direita;
    int esquerda;
    
    int resultado = -1;
    
    if(a){
        
        if(a->valor == x) resultado = 1;
        
        else{
            direita = 1 + depth(a->dir, x);
            esquerda = 1 + depth(a->esq, x);
            
            if(direita>0 && esquerda>0) resultado = minimo(direita,esquerda);
            else if(direita>0) resultado = direita;
            else if(esquerda>0) resultado = esquerda;
        }
    }
    
    return resultado;
}

// Questão 35

int freeAB (ABin a) {

	int numNodosLibertados = 0;

	if (a){
		numNodosLibertados = 1 + freeAB(a->esq) + freeAB(a->dir);
		free(a);
	}

	return numNodosLibertados;
}

// Questão 36

int pruneAB (ABin *a, int l) {

    int numNodosRemovidos = 0;

    if(*a){
        
        numNodosRemovidos = numNodosRemovidos + pruneAB(&((*a)->dir),l-1);
                            + pruneAB(&((*a)->esq),l-1);

        if(l <= 0){

            free(*a);
            (*a) = NULL;
            numNodosRemovidos++;
        }
    }

    return numNodosRemovidos;
}

// Questão 37

int iguaisAB (ABin a, ABin b) {

    int iguais = 0;

	if (a == NULL && b != NULL) iguais = 0;
	if (a != NULL && b == NULL) iguais = 0;

    if (a == NULL && b == NULL) iguais = 1;
	if (a != NULL && b != NULL){

	    if (a->valor == b->valor)
	        iguais = iguaisAB (a->esq, b->esq) && iguaisAB(a->dir, b->dir);
	}

    return iguais;
}

// Questão 38

void concatL (LInt *a, LInt b){
	while (*a)
		a = &((*a)->prox);
	*a = b;
}

LInt nivelL (ABin a, int n) {

    LInt listaValores = NULL;
    
    if(a){
        
        if(n == 1){
            LInt novaLista = malloc(sizeof(struct lligada));
            novaLista->valor = a->valor;
            novaLista->prox = listaValores;
            listaValores = novaLista;
        }
        else{
            listaValores = nivelL(a->esq, n-1);
            concatL(&listaValores, nivelL(a->dir, n-1));
        }
    }
    
    return listaValores;
}

// Questão 39

int nivelV (ABin a, int n, int v[]) {

    int posicoesPreenchidas = 0;
    
    if(a){
        
       if(n == 1){
           v[posicoesPreenchidas] = a->valor;
           posicoesPreenchidas++;
       }
       else{
           // IMPORTANTE - PRIMEIRO A ESQUERDA E DEPOIS A DIREITA
            posicoesPreenchidas += nivelV(a->esq, n-1, v+posicoesPreenchidas);
            posicoesPreenchidas += nivelV(a->dir, n-1, v+posicoesPreenchidas);
       }
    }
    
    return posicoesPreenchidas;
}

// Questão 40

// Questão 41

// Questão 42

int contaFolhas (ABin a) {

    int quantFolhas = 0;
    
    if(a){
        
        if(a->esq == 0 && a->dir == 0) quantFolhas++;
        else{
            quantFolhas = quantFolhas + contaFolhas(a->dir);
            quantFolhas = quantFolhas + contaFolhas(a->esq);
        }
    }
    
    return quantFolhas;
}

// Questã0 43

ABin cloneMirror (ABin a) {

   ABin avoreClonada =NULL;

   if(a){

       avoreClonada = malloc(sizeof(struct nodo));
       avoreClonada->valor = a->valor;
       avoreClonada->esq = cloneMirror(a->dir);
       avoreClonada->dir = cloneMirror(a->esq);
   }

    return avoreClonada;
}

// Questão 44

int addOrd (ABin *a, int x) {

    int jaExiste = 0;

    while(*a && jaExiste == 0){

        if((*a)->valor > x) a= &((*a)->esq);
        if((*a)->valor < x) a = &((*a)->dir);
        if((*a)->valor == x) jaExiste = 1;
    }

    if(jaExiste == 0){
        (*a) = malloc(sizeof(struct nodo));
        (*a)->valor = x;
        (*a)->dir = NULL;
        (*a)->esq = NULL;
    }

    return jaExiste;
}