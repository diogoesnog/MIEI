#ifndef binaryTree_h
#define binaryTree_h

// Estrutura definida

typedef 
struct binaryTree{
    int valor;
    struct binaryTree *esquerda, *direita;
} Nodo, *BinaryTree;

// Métodos a implementar

int tamanho(BinaryTree);
int altura(BinaryTree);
BinaryTree adicionar(BinaryTree, int);
int pesquisar(BinaryTree, int);
int maiorElemento(BinaryTree);
int balanceada(BinaryTree);
// void Destroy(binaryTree);

#endif
