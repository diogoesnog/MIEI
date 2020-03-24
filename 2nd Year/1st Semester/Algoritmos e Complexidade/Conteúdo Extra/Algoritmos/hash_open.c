#include "hash_function.h"
#include "hash_open.h"
#include <stdlib.h>
#include <string.h>

int Hash(KeyType key) {
	return hash_prime((unsigned char*)key,strnlen(key,9),HASHSIZE);
}

void InitializeTable(HashTable t) {
	for (int i = 0; i < HASHSIZE; i++)
	    strncpy(t[i].key,EMPTY,9);
}

void ClearTable(HashTable t) {
	InitializeTable(t);
}

void InsertTable_QP(HashTable t, KeyType k, Info i) {
	int pos, try;

    // Tratar actualizacao
	pos = RetrieveTable_QP(t,k);
	if (pos >= 0) {
		t[pos].info = i;
		return;
	}

	int h = Hash(k);
    pos = h;
    try = 0;
    while ((try <= HASHSIZE / 2) && 
           (strncmp(t[pos].key,EMPTY,9)!=0) &&
           (strncmp(t[pos].key,DELETED,9)!=0)) {
    	pos = (pos + (try << 1) + 1) % HASHSIZE; // h + try * try
    	try++;
    }
    if (try <= HASHSIZE / 2) {
    	strncpy(t[pos].key,k,9);
		t[pos].info = i;
    }
}

int RetrieveTable_QP(HashTable t, KeyType k) {
	int try, pos;
	int h = Hash(k);
    pos = h;
    try = 0;
    while ((try <= HASHSIZE / 2) && 
           (strncmp(t[pos].key,k,9)!=0) &&
           (strncmp(t[pos].key,EMPTY,9)!=0)) {
    	pos = (pos + (try << 1) + 1) % HASHSIZE; // h + try * try
    	try++;
    }
    if (strncmp(t[pos].key,k,9)==0) {
    	return pos;
    }
    return -1;
}

void DeleteTable_QP(HashTable t, KeyType k) {
	int pos;

	pos = RetrieveTable_QP(t,k);
	if (pos >= 0) {
		strncpy(t[pos].key,DELETED,9);
	}

}

//void InsertTable_LP(HashTable, KeyType, Info);
//void DeleteTable_LP(HashTable, KeyType);
//int RetrieveTable_LP(HashTable, KeyType);

