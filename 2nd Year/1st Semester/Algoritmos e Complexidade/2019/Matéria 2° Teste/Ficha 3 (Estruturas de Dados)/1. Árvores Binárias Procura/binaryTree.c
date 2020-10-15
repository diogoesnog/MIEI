#include <stdlib.h>
#include <stdio.h>
#include "binaryTree.h"

// Função que calcula o número de Nodos de uma BinaryTree.
int tamanho(BinaryTree arvore){
    int resultado = 0;

    if(arvore != NULL){
        resultado = 1 + 
                tamanho(arvore->esquerda) +
                tamanho(arvore->direita);
    }

    return resultado;
}

// Função que calcula a altura de uma BinaryTree.
int altura(BinaryTree arvore){
    
    int resultado = 0;

    int alturaEsquerda = 0;
    int alturaDireita = 0;

    if(arvore != NULL){
        alturaDireita = 1 + altura(arvore->direita);
        alturaEsquerda = 1 + altura(arvore->esquerda);
    }

    if(alturaDireita>alturaEsquerda) resultado = alturaDireita;
    else resultado = alturaEsquerda;

    return resultado;
}

// Função que adiciona um elemento a uma BinaryTree.
BinaryTree adicionar(BinaryTree arvore, int elemento){

    if(arvore == NULL){
        arvore = malloc(sizeof(Nodo));
        arvore->valor = elemento;
        arvore->esquerda = NULL;
        arvore->direita = NULL;
    }

    if(elemento < arvore->valor) arvore->esquerda = adicionar(arvore->esquerda,elemento);
    if(elemento > arvore->valor) arvore->direita = adicionar(arvore->direita,elemento);

    return arvore;
}

// Função que verifica se um dado valor ocorre numa BinaryTree.
int pesquisar(BinaryTree arvore, int elemento){

    int existe = 0; // Predefinição para quando não existe.

    if(arvore != NULL && existe == 0){
        if(arvore->valor == elemento) existe = 1;
        if(arvore->valor > elemento) existe = pesquisar(arvore->esquerda,elemento);
        if(arvore->valor < elemento) existe = pesquisar(arvore->direita,elemento); 
    }

    return existe;
}

// Função que calcula o maior elemento de uma BinaryTree.
// Obviamente que o maior elemento estará sempre mais à esquerda.
int maiorElemento(BinaryTree arvore){

    int maior = 0;

    if(arvore != NULL){
        if(arvore->direita != NULL) maior = maiorElemento(arvore->direita);
        else(maior = arvore->valor);
    }

    return maior;
}

// Função que testa se uma BinaryTree é balanceada.
int balanceada(BinaryTree arvore){

    int direita, esquerda, diferenca;

    if(arvore != NULL){
        direita = altura(arvore->direita);
        esquerda = altura(arvore->esquerda);
    }

    diferenca = abs(direita-esquerda);

    if(diferenca <= 1) return 1;
    if(diferenca > 1) return 0;

}

// Função Main para testes

int main(void)
{
	BinaryTree arvore = NULL;
	arvore = adicionar(arvore, 20);
	arvore = adicionar(arvore, 10);
	arvore = adicionar(arvore, 25);
	arvore = adicionar(arvore, 21);
	arvore = adicionar(arvore, 26);
	arvore = adicionar(arvore, 9);
	arvore = adicionar(arvore, 22);
    arvore = adicionar(arvore, 7);
    arvore = adicionar(arvore, 5);

	printf("Tamanho: %d\n", tamanho(arvore));
	printf("Altura: %d\n", altura(arvore));
	printf("Existe 21? (1 se Sim e 0 se Não): %d\n", pesquisar(arvore, 21));
	printf("Maior Elemento: %d\n", maiorElemento(arvore));
	printf("É balanceada? (1 se Sim e 0 se Não): %d", balanceada(arvore));
    printf("\n");

	return 0;
}
