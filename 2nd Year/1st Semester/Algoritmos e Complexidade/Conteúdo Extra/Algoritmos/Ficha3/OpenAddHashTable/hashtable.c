#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include <stdio.h>


typedef struct entry {
	KeyType key;
	Info info;
} *Entry;


struct hashTable {
	int capacity;
	int numEntries;
	Entry entries;
};


// Private

double GetLoadFactor(HashTable h)
{
	double f = ((double)h->numEntries) / ((double)h->capacity);

	return f;
}


Entry InitEntries(int capacity)
{
	int i = 0;
	Entry entries = malloc(sizeof(struct entry) * capacity);

	for (; i < capacity; i++) {
		strcpy_s(entries[i].key, KEYSIZE, EMPTY);
	}

	return entries;
}


// Linear Probing

int HashLP(int capacity, KeyType key)
{
	char *aux = key;
	int sum = 0;

	while (*aux != '\0') {
		sum += (int)*aux++;
	}

	return (sum % capacity);
}


void InsertEntryLP(Entry e, KeyType key, Info info, int capacity)
{
	int aux = 0;
	int index = HashLP(capacity, key);
	int i = index;

	while (i != index || aux == 0) {
		aux = 1;

		if (strcmp(e[i].key, EMPTY) == 0 || strcmp(e[i].key, DELETED) == 0) {
			strcpy_s(e[i].key, KEYSIZE, key);
			e[i].info = info;
			break;
		}

		i = (i + 1 == capacity) ? 0 : i + 1;
	}
}


int DeleteEntryLP(Entry e, KeyType key, int capacity)
{
	int index = HashLP(capacity, key);
	int i = index;
	int aux = 0;
	int r = 0;

	while (i != index || aux == 0) {
		aux = 1;

		if (strcmp(e[i].key, EMPTY) == 0) {
			break;
		}

		if (strcmp(e[i].key, key) == 0) {
			strcpy_s(e[i].key, KEYSIZE, DELETED);
			r++;
			break;
		}

		i = (i + 1 == capacity) ? 0 : i + 1;
	}

	return r;
}


Entry RehashLP(Entry e, int capacity, int oldCapacity)
{
	int i = 0;
	Entry newEntries = InitEntries(capacity);

	for (; i < oldCapacity; i++) {
		if (strcmp(e[i].key, DELETED) != 0 || strcmp(e[i].key, EMPTY) != 0) {
			InsertEntryLP(newEntries, e[i].key, e[i].info, capacity);
		}
	}

	free(e);
	e = NULL;

	return newEntries;
}


// Quadratic Probing

int HashQP(int capacity, KeyType key, int n)
{
	char *aux = key;
	int sum = 0;

	while (*aux != '\0') {
		sum += (int)*aux++;
	}

	return ((sum + (n * n)) % capacity);
}


void InsertEntryQP(Entry e, KeyType key, Info info, int capacity)
{
	int n = 0;
	int i = 0;

	for (; n < capacity; n++) {
		i = HashQP(capacity, key, n);

		if (strcmp(e[i].key, EMPTY) == 0 || strcmp(e[i].key, DELETED) == 0) {
			strcpy_s(e[i].key, KEYSIZE, key);
			e[i].info = info;
			break;
		}
	}
}


int DeleteEntryQP(Entry e, KeyType key, int capacity)
{
	int n = 0;
	int i = 0;
	int r = 0;

	for (; n < capacity; n++) {
		i = HashQP(capacity, key, n);

		if (strcmp(e[i].key, EMPTY) == 0) {
			break;
		}

		if (strcmp(e[i].key, key) == 0) {
			strcpy_s(e[i].key, KEYSIZE, DELETED);
			r++;
			break;
		}
	}

	return r;
}


Entry RehashQP(Entry e, int capacity, int oldCapacity)
{
	int i = 0;
	Entry newEntries = InitEntries(capacity);

	for (; i < oldCapacity; i++) {
		if (strcmp(e[i].key, DELETED) != 0 || strcmp(e[i].key, EMPTY) != 0) {
			InsertEntryQP(newEntries, e[i].key, e[i].info, capacity);
		}
	}

	free(e);
	e = NULL;

	return newEntries;
}


// Public

HashTable InitializeTable(void)
{
	HashTable h = malloc(sizeof(struct hashTable));

	if (h != NULL) {
		h->capacity = HASHSIZE;
		h->numEntries = 0;
		h->entries = InitEntries(h->capacity);
	}

	return h;
}


void ClearTable(HashTable h)
{
	if (h != NULL) {
		if (h->entries != NULL) {
			free(h->entries);
			h->entries = NULL;
		}

		free(h);
		h = NULL;
	}
}


void Print(HashTable h)
{
	int i = 0;

	if (h != NULL) {
		for (; i < h->capacity; i++) {
			if (strcmp(h->entries[i].key, EMPTY) == 0) {
				printf("EMPTY\n");
			}
			else if (strcmp(h->entries[i].key, DELETED) == 0) {
				printf("DELETED\n");
			}
			else {
				printf("%d\n", (*(int*)h->entries[i].info));
			}
		}
	}
}


// Linear Probing

void InsertTableLP(HashTable h, KeyType key, Info info)
{
	if (h != NULL) {
		InsertEntryLP(h->entries, key, info, h->capacity);
		h->numEntries++;

		if (GetLoadFactor(h) >= 0.75) {
			h->entries = RehashLP(h->entries, h->capacity * 2 + 1, h->capacity);
			h->capacity = h->capacity * 2 + 1;
		}
	}
}


void DeleteTableLP(HashTable h, KeyType key)
{
	if (h != NULL) {
		if (DeleteEntryLP(h->entries, key, h->capacity) == 1) {
			h->numEntries--;
		}

		if (GetLoadFactor(h) <= 0.25) {
			h->entries = RehashLP(h->entries, 
				                 (int)(h->capacity / 2), h->capacity);
			h->capacity = (int)(h->capacity / 2);
		}

	}
}


Info RetrieveTableLP(HashTable h, KeyType key) 
{
	int index = HashLP(h->capacity, key);
	int i = index;
	int aux = 0;
	Info info = NULL;

	if (h != NULL) {
		while (i != index || aux == 0) {
			aux = 1;

			if (strcmp(h->entries[i].key, EMPTY) == 0) {
				break;
			}

			if (strcmp(h->entries[i].key, key) == 0) {
				info = h->entries[i].info;
				break;
			}

			i = (i + 1 == h->capacity) ? 0 : i + 1;
		}
	}

	return info;
}


// Quadratic Probing

void InsertTableQP(HashTable h, KeyType key, Info info)
{
	if (h != NULL) {
		InsertEntryQP(h->entries, key, info, h->capacity);
		h->numEntries++;

		if (GetLoadFactor(h) >= 0.5) {
			h->entries = RehashQP(h->entries, h->capacity * 2 + 1, h->capacity);
			h->capacity = h->capacity * 2 + 1;
		}
	}
}


void DeleteTableQP(HashTable h, KeyType key)
{
	if (h != NULL) {
		if (DeleteEntryQP(h->entries, key, h->capacity) == 1) {
			h->numEntries--;
		}

		if (GetLoadFactor(h) < 0.25) {
			h->entries = RehashQP(h->entries, (int)(h->capacity / 2), 
				                  h->capacity);
			h->capacity = (int)(h->capacity / 2);
		}
	}
}


Info RetrieveTableQP(HashTable h, KeyType key)
{
	int n = 0;
	int i = 0;
	Info info = NULL;

	if (h != NULL) {
		for (; n < h->capacity; n++) {
			i = HashQP(h->capacity, key, n);

			if (strcmp(h->entries[i].key, EMPTY) == 0) {
				break;
			}

			if (strcmp(h->entries[i].key, key) == 0) {
				info = h->entries[i].info;
				break;
			}
		}
	}
	
	return info;
}
