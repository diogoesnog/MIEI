#include <stdlib.h>
#include "AVLTree.h"


AVLTree rotateLeft(AVLTree a)
{
	AVLTree pivot = a->right;

	a->right = pivot->left;
	pivot->left = a;

	return pivot;
}


AVLTree rotateRight(AVLTree a)
{
	AVLTree pivot = a->left;

	a->left = pivot->right;
	pivot->right = a;

	return pivot;
}


int Height(AVLTree a)
{
	int h = 0;

	if (a != NULL) {
		h = (a->bal >= 0) ? (1 + Height(a->right)) : (1 + Height(a->left));
	}

	return h;
}