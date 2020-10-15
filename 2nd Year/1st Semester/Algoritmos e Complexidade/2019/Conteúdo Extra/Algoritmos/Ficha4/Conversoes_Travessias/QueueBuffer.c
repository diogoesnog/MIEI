#include <stdlib.h>
#include <stdio.h>
#include "QueueBuffer.h"


typedef struct lList {
	int elem;
	struct lList *next;
} *LList;


struct lListBuffer {
	int size;
	LList list;
};


LList AddElem(LList l, int elem)
{
	LList newNode = malloc(sizeof(struct lList));
	LList current = l;

	newNode->elem = elem;
	newNode->next = NULL;

	if (l == NULL) {
		l = newNode;
	}
	else {
		while (current->next != NULL) {
			current = current->next;
		}

		current->next = newNode;
	}

	return l;
}


LListBuffer InitLL(void)
{
	LListBuffer b = malloc(sizeof(struct lListBuffer));

	b->size = 0;
	b->list = NULL;

	return b;
}


int EmptyLL(LListBuffer b)
{
	int r = 0;

	if (b != NULL) {
		r = (b->size > 0) ? 0 : 1;
	}

	return r;
}


int AddLL(LListBuffer b, int elem)
{
	int r = 0;

	if (b != NULL) {
		b->list = AddElem(b->list, elem);
		b->size++;
		r++;
	}

	return r;
}


int NextLL(LListBuffer b, int *elem)
{
	int r = 0;

	if (b != NULL && b->list != NULL) {
		*elem = b->list->elem;
		r++;
	}

	return r;
}


int RemoveLL(LListBuffer b, int *elem)
{
	LList aux = NULL;
	int r = 0;

	if (b != NULL && b->list != NULL) {
		*elem = b->list->elem;
		aux = b->list;
		b->list = b->list->next;
		free(aux);
		aux = NULL;
		b->size--;
		r++;
	}

	return r;
}


void ClearLL(LListBuffer b)
{
	LList aux = NULL;

	if (b != NULL) {
		while (b->list != NULL) {
			aux = b->list;
			b->list = b->list->next;
			free(aux);
			aux = NULL;
		}

		free(b);
		b = NULL;
	}
}


// Array Buffer

struct arrayBuffer {
	int head;
	int tail;
	int size;
	int capacity;
	int *arr;
};


ArrayBuffer InitArray(int capacity)
{
	ArrayBuffer b = malloc(sizeof(struct arrayBuffer));

	b->head = 0;
	b->tail = 0;
	b->size = 0;
	b->capacity = capacity;
	b->arr = malloc(sizeof(int) * capacity);

	return b;
}


int EmptyArray(ArrayBuffer b)
{
	int r = 0;

	if (b != NULL) {
		r = (b->size > 0) ? 1 : 0;
	}

	return r;
}


int AddArray(ArrayBuffer b, int elem)
{
	int r = 0;

	if (b != NULL && b->arr != NULL && b->size < b->capacity) {
		if (b->tail == b->capacity) {
			b->tail = 0;
		}

		b->arr[b->tail++] = elem;
		b->size++;
		r++;
	}

	return r;
}


int NextArray(ArrayBuffer b, int *elem)
{
	int r = 0;

	if (b != NULL && b->arr != NULL && b->size > 0) {
		*elem = b->arr[b->head];
		r++;
	}

	return r;
}


int RemoveArray(ArrayBuffer b, int *elem)
{
	LList aux = NULL;
	int r = 0;

	if (b != NULL && b->arr != NULL && b->size > 0) {
		*elem = b->arr[b->head++];
		b->size--;
		r++;

		if (b->head == b->capacity) {
			b->head = 0;
		}
	}

	return r;
}


void ClearArray(ArrayBuffer b)
{
	if (b != NULL) {
		if (b->arr != NULL) {
			free(b->arr);
			b->arr = NULL;
		}

		free(b);
		b = NULL;
	}
}


void PrintArray(ArrayBuffer b)
{
	int i = 0;

	if (b != NULL && b->arr != NULL) {
		for (; i < b->capacity; i++) {
			printf("%d - %d\n", i, b->arr[i]);
		}
	}
}