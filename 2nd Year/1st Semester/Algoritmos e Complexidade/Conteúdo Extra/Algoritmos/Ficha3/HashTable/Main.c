#include <stdio.h>
#include "HashTable.h"


int main(void)
{
	HashTable h = InitializeTable();

	int x = 2, y = 1, z = 10, a = 11, b = 20, c = 7, f = 8;

	InsertTable(h, "2", &x);
	InsertTable(h, "1", &y);
	InsertTable(h, "10", &z);
	InsertTable(h, "11", &a);
	InsertTable(h, "20", &b);
	InsertTable(h, "7", &c);
	InsertTable(h, "8", &f);

	Info info = RetrieveTable(h, "10");

	if (info != NULL) {
		printf("%d\n\n", *(int*)info);
	}

	info = RetrieveTable(h, "17");

	if (info != NULL) {
		printf("%d\n\n", *(int*)info);
	}

	DeleteTable(h, "8");

	Print(h);

	ClearTable(h);

	getchar();
	return 0;
}