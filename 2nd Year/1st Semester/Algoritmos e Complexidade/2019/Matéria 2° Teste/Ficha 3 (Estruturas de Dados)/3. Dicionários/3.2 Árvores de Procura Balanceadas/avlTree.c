#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "avlTree.h"

int alturaAVL(AVLTree arvore){

    int altura = 0;

    if(arvore!=NULL){
        
        if(arvore->balanceada > 0) arvore = arvore->esquerda;
        else arvore = arvore->direita;

        altura++;
    }

    return altura;
}

AVLTree rodarEsquerda(AVLTree arvore){

    AVLTree auxiliar = arvore->direita;

    arvore->direita = auxiliar->esquerda;
    auxiliar->esquerda = arvore;

    return auxiliar;

}

AVLTree rodarDireita(AVLTree arvore){

    AVLTree auxiliar = arvore->esquerda;

    arvore->esquerda = auxiliar->direita;
    auxiliar->direita = arvore;

    return auxiliar;
}