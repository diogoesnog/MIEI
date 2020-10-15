#ifndef btree_h
#define btree_h

typedef struct btree *BTree, Node;
typedef int Value;

int tamanho(BTree);
int altura(BTree);
int balanceada(BTree);
BTree adicionar(BTree, Value);
int pesquisar(BTree, Value);
Value maiorElemento(BTree);
void Destroy(BTree);

#endif
