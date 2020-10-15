#include <stdio.h>
#include <stdlib.h>

#include "AVL.h"

// Função que é acionada quando o elemento fica inserido à direita.
// Necessário então corrigir à direita.
AVLTree corrigirDireita(AVLTree *arvore) {

    AVLTree (*auxiliar) = arvore->direita;

    if(auxiliar->fatorBalanceamento == DIREITA) {
        arvore->fatorBalanceamento = IGUAIS;
        arvore = rodarEsquerda(arvore);
    }
    else {
        arvore->fatorBalanceamento = IGUAIS;
        arvore->direita = rodarDireita(arvore->direita);
        arvore = rodarEsquerda(arvore);
    }

    return (*arvore);
}

// Função que é acionada quando o elemento fica inserido à esquerda.
// Necessário então corrigir à esquerda.
AVLTree corrigirEsquerda(AVLTree *arvore) {

    AVLTree (*auxiliar) = arvore->esquerda;

    if(auxiliar->fatorBalanceamento == ESQUERDA) {
        arvore->fatorBalanceamento = IGUAIS;
        arvore = rodarDireita(arvore);
    }
    else {
        arvore->fatorBalanceamento == IGUAIS;
        arvore->esquerda = rodarEsquerda(arvore->esquerda);
        arvore = rodarDireita(arvore);
    }

    return (*arvore);
}

// Temos de ter em atenção o balanceamento da árvore.
// Contrariamente a uma BST normal, uma AVL segue uma estrutura rígida da árvore.
// O valor de "cresceu" serve para indicar se a altura da árvore aumentou.
AVLTree inserirÁrvore(AVLTree *arvore, int elemento, int *cresceu) {

    // Caso não haja mais nodos a percorrer.
    if (arvore = NULL){ 
        arvore = malloc(sizeof(struct AVLTree));
        arvore->fatorBalanceamento = IGUAIS;
        arvore->valorNodo = elemento;

        arvore->direita = NULL;
        arvore->esquerda = NULL;

        cresceu = 1;
    }

    // Caso o elemento seja maior, temos de andar para a direita.
    else if (elemento > arvore->valorNodo) {
        *(arvore->direita) = inserirÁrvore(arvore->direita, elemento, cresceu);

        // Ponto em que já se inseriu o elemento e portanto a árvore já cresceu.
        // Logo, cresceu = 1.
        if(cresceu == 1) {

            if(arvore->fatorBalanceamento == IGUAIS) arvore->fatorBalanceamento = DIREITA;
            else if(arvore->fatorBalanceamento == ESQUERDA) {
                arvore->fatorBalanceamento = IGUAIS;
                cresceu = 0;
            }
            else {
                (*arvore) = corrigirDireita(arvore);
                cresceu = 0;
            }
        }
    }
    // Caso o elemento seja menor, temos de andar para a esquerda.
    else if (elemento < arvore->valorNodo) {
        *(arvore->esquerda) = inserirÁrvore(arvore->esquerda, elemento, cresceu);

        // Ponto em que já se inseriu o elemento e portanto a árvore já cresceu.
        // Logo, cresceu = 1.
        if(cresceu == 1) {

            if(arvore->fatorBalanceamento == IGUAIS) arvore->fatorBalanceamento = ESQUERDA;
            else if(arvore->fatorBalanceamento == DIREITA) {
                arvore->fatorBalanceamento = IGUAIS;
                cresceu = 0;
            }
            else {
                *arvore = corrigirEsquerda(arvore);
                cresceu = 0;
            }
        }
    }

    return (*arvore);
}
