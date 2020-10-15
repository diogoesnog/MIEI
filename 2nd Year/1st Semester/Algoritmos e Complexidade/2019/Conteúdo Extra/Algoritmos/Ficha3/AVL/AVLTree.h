#ifndef AVLTree_h
#define AVLTree_h

typedef struct avlTree {
	int value;
	int bal;
	struct avlTree *left, *right;
} AVLNode, *AVLTree;


int Height(AVLTree);


#endif
