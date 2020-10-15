#include <stdlib.h>
#include "btree.h"


struct btree {
	Value value;
	BTree left;
	BTree right;
};


int IsBalancedAux(BTree b, int *p)
{
	int l = *p;
	int r = *p;
	int balL = 1;
	int balR = 1;

	if (b != NULL) {
		l++;
		r++;

		balL = IsBalancedAux(b->left, &l);
		balR = IsBalancedAux(b->right, &r);

		*p = (l > r) ? l : r;
	}

	return ((abs(l - r) <= 1 && balL == 1 && balR == 1) ? 1 : 0);
}


int IsBalanced(BTree b)
{
	int p = 0;

	return IsBalancedAux(b, &p);
}

int Size(BTree b)
{
	int size = 0;

	if (b != NULL) {
		size += 1 + Size(b->left) + Size(b->right);
	}

	return size;
}


int Height(BTree b)
{
	int hL = 0;
	int hR = 0;

	if (b != NULL) {
		hL = 1 + Height(b->left);
		hR = 1 + Height(b->right);
	}

	return ((hL > hR) ? hL : hR);
}




BTree Add(BTree b, Value value)
{
	if (b == NULL) {
		b = malloc(sizeof(Node));
		b->value = value;
		b->left = NULL;
		b->right = NULL;
	}
	else if (value < b->value) {
		b->left = Add(b->left, value);
	}
	else if (value > b->value) {
		b->right = Add(b->right, value);
	}

	return b;
}


int Search(BTree b, Value value)
{
	int res = 0;

	if (b != NULL) {
		if (b->value == value) {
			res = 1;
		}
		else if (b->value > value) {
			res = Search(b->left, value);
		}
		else {
			res = Search(b->right, value);
		}
	}

	return res;
}


Value Max(BTree b) 
{
	int max = 0;

	if (b != NULL) {
		if (b->right != NULL) {
			max = Max(b->right);
		}
		else {
			max = b->value;
		}
	}

	return max;
}


void Destroy(BTree b) 
{
	if (b != NULL) {
		Destroy(b->left);
		Destroy(b->right);
		free(b);
		b = NULL;
	}
}










