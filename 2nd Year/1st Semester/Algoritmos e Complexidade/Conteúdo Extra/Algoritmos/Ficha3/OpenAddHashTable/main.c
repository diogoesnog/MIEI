#include <stdio.h>
#include "hashtable.h"


int main(void)
{
	HashTable h = InitializeTable();

	int x = 1, y = 4, z = 15, w = 2;
	int a = 5;

	InsertTableLP(h, "1", &x);
	InsertTableLP(h, "4", &y);
	InsertTableLP(h, "15", &z);
	InsertTableLP(h, "2", &w);
	InsertTableLP(h, "5", &a);

	DeleteTableLP(h, "1");
	DeleteTableLP(h, "15");
	Info i = RetrieveTableLP(h, "5");

	if (i != NULL) {
		printf("%d\n\n\n", *(int*)i);
	}

	Print(h);
	ClearTable(h);

	getchar();
	return 0;
}