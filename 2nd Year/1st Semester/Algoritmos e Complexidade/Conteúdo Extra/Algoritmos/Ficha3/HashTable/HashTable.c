#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "HashTable.h"


typedef struct entry {
	KeyType key;
	Info info;
	struct entry *next;
} *Entry;


struct hashTable {
	int capacity;
	int numEntries;
	Entry *entries;
};



// Private

Entry *InitEntries(int capacity)
{
	Entry *entries = malloc(sizeof(Entry) * capacity);
	int i = 0;

	for (; i < capacity; i++) {
		entries[i] = NULL;
	}

	return entries;
}


void ClearEntries(Entry *entries, int capacity)
{
	int i = 0;
	Entry aux = NULL;

	if (entries != NULL) {
		for (; i < capacity; i++) {
			if (entries[i] != NULL) {

				while (1) {
					aux = entries[i];

					if (aux == NULL) {
						break;
					}

					entries[i] = entries[i]->next;
					free(aux);
					aux = NULL;
				}
			}
		}

		free(entries);
		entries = NULL;
	}
}


int Hash(int capacity, KeyType key)
{
	int sum = 0;
	char *p = key;

	while (*p != '\0') {
		sum += (int)*p++;
	}

	return (sum % capacity);
}


double GetLoadFactor(HashTable h)
{
	double f = ((double)h->numEntries) / ((double)h->capacity);

	return f;
}


void InsertEntry(Entry *entries, KeyType key, Info info, int capacity)
{
	int index = Hash(capacity, key);
	Entry newEntry = malloc(sizeof(struct entry));

	newEntry->info = info;
	strcpy_s(newEntry->key, KEYSIZE, key);
	newEntry->next = entries[index];
	entries[index] = newEntry;
}


int DeleteEntry(Entry *entries, KeyType key, int capacity)
{
	int r = 0;
	int index = Hash(capacity, key);
	Entry aux = entries[index];
	Entry previous = NULL;

	while (aux != NULL) {
		if (strcmp(aux->key, key) == 0) {
			if (previous == NULL) {
				entries[index] = aux->next;
			}
			else {
				previous->next = aux->next;
			}

			free(aux);
			aux = NULL;
			r++;
			break;
		}

		previous = aux;
		aux = aux->next;
	}

	return r;
}


Entry *Rehash(Entry *entries, int capacity, int oldCapacity)
{
	int i = 0;
	Entry *newEntries = InitEntries(capacity);
	Entry aux = NULL;

	for (; i < oldCapacity; i++) {
		if (entries[i] != NULL) {
			aux = entries[i];

			while (aux != NULL) {
				InsertEntry(newEntries, aux->key, aux->info, capacity);
				aux = aux->next;
			}
		}
	}

	ClearEntries(entries, oldCapacity);

	return newEntries;
}


// Public

HashTable InitializeTable(void)
{
	HashTable h = malloc(sizeof(struct hashTable));

	h->capacity = HASHSIZE;
	h->numEntries = 0;
	h->entries = InitEntries(h->capacity);

	return h;
}


void InsertTable(HashTable h, KeyType key, Info info)
{
	if (h != NULL && h->entries != NULL) {
		InsertEntry(h->entries, key, info, h->capacity);
		h->numEntries++;

		if (GetLoadFactor(h) >= 0.75) {
			h->entries = Rehash(h->entries, h->capacity * 2 + 1, h->capacity);
			h->capacity = h->capacity * 2 + 1;
		}
	}
}


void DeleteTable(HashTable h, KeyType key)
{
	if (h != NULL && h->entries != NULL) {
		if (DeleteEntry(h->entries, key, h->capacity) == 1) {
			h->numEntries--;
		}

		if (GetLoadFactor(h) <= 0.25) {
			h->entries = Rehash(h->entries, h->capacity / 2, h->capacity);
			h->capacity = h->capacity / 2;
		}
	}
}


Info RetrieveTable(HashTable h, KeyType key)
{
	int index = 0;
	Info info = NULL;
	Entry aux = NULL;

	if (h != NULL && h->entries != NULL) {
		index = Hash(h->capacity, key);
		aux = h->entries[index];

		while (aux != NULL) {
			if (strcmp(aux->key, key) == 0) {
				info = aux->info;
				break;
			}

			aux = aux->next;
		}
	}

	return info;
}


void ClearTable(HashTable h) 
{
	if (h != NULL) {
		ClearEntries(h->entries, h->capacity);
		free(h);
		h = NULL;
	}
}


void Print(HashTable h)
{
	int i = 0;
	Entry aux = NULL;

	if (h != NULL && h->entries != NULL) {
		for (; i < h->capacity; i++) {
			printf("%d - ", i);

			aux = h->entries[i];

			while (aux != NULL) {
				printf("%d ", *(int*)aux->info);
				aux = aux->next;
			}

			printf("\n");
		}
	}
}