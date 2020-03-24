#include <stdio.h>
#include "binaryTree.h"

int main(void)
{
	BinaryTree arvore = NULL;

	printf("Size: %d\n", tamanho(arvore));
	printf("Height: %d\n", altura(arvore));

	arvore = adicionar(arvore, 20);
	arvore = adicionar(arvore, 10);
	arvore = adicionar(arvore, 25);
	arvore = adicionar(arvore, 21);
	arvore = adicionar(arvore, 26);

	printf("Size: %d\n", tamanho(arvore));
	printf("Height: %d\n", altura(arvore));
	//printf("Search 4: %d\n", Search(b, 4));
	//printf("Search 10: %d\n", Search(b, 10));
	//printf("Max: %d\n", Max(b));
	//printf("Is balanced: %d", IsBalanced(b));

	return 0;
}