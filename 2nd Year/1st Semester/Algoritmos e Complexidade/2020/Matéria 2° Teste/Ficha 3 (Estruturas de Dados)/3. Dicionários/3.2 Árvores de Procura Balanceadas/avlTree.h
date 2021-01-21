#ifndef avlTree_h
#define avlTree_h

// Estruturas definidas

typedef struct avlTree{
	int valor;
	int balanceada; // Diferença de alturas entre as sub-árvores (esquerda-direita).
	struct avlTree *esquerda, *direita;
} AVLNode, *AVLTree;

// Métodos a Implementar

int alturaAVL(AVLTree);
AVLTree rodarEsquerda(AVLTree);
AVLTree rodarDireita(AVLTree);

#endif

