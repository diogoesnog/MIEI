#include "hash_open.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	int valores[] = {1,2,3,4,5,6,7,8,9};

	HashTable t = (HashTable)malloc(HASHSIZE*sizeof(Entry));

	ClearTable(t);
    InsertTable_QP( t, "UM", valores);
    InsertTable_QP( t, "DOIS", valores+1);
    InsertTable_QP( t, "TRES", valores+2);
    InsertTable_QP( t, "QUATRO", valores+3);
    InsertTable_QP( t, "CINCO", valores+4);
    InsertTable_QP( t, "SEIS", valores+5);

    int pos = RetrieveTable_QP(t, "DOIS");
	if (pos == -1) {
		printf("TA MAL!!!\n");
	}
	else {
		printf("ENCONTROU %d\n",*(int*)t[pos].info);
	}

	DeleteTable_QP(t,"DOIS");

    pos = RetrieveTable_QP(t, "DOIS");
	if (pos == -1) {
		printf("TA BEM!!!\n");
	}
	else {
		printf("TA MAL!!!\n");
	}

    InsertTable_QP( t, "SETE", valores+7);
    InsertTable_QP( t, "OITO", valores+8);

    pos = RetrieveTable_QP(t, "SETE");
	if (pos == -1) {
		printf("TA MAL!!!\n");
	}
	else {
		printf("ENCONTROU %d\n",*(int*)t[pos].info);
	}


	free(t);
}