#include <stdlib.h>
#include "StackBuffer.h"




BufferLList InitLL(void)
{
	BufferLList b = malloc(sizeof(struct bufferLList));

	b->list = NULL;
	b->size = 0;

	return b;
}


int EmptyLL(BufferLList b)
{
	return (b->size == 0) ? 1 : 0;
}


void AddLL(BufferLList b, int elem)
{
	List newElem = NULL;
	
	if (b != NULL) {
		newElem = malloc(sizeof(struct llist));

		newElem->elem = elem;
		newElem->next = b->list;
		b->list = newElem;
		b->size++;
	}
}


int NextLL(BufferLList b, int *elem)
{
	int r = 0;

	if (b != NULL && b->list != NULL) {
		*elem = b->list->elem;
		r++;
	}

	return r;
}


int RemoveLL(BufferLList b, int *elem)
{
	int r = 0;
	List aux = NULL;

	if (b != NULL && b->list != NULL) {
		aux = b->list;
		*elem = aux->elem;
		b->list = b->list->next;
		free(aux);
		aux = NULL;
		b->size--;
		r++;
	}

	return r;
}


void ClearLL(BufferLList b)
{
	List aux = NULL;

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


// Buffer Array


struct bufferArray {
	int *arr;
	int size;
	int capacity;
};op


BufferArray InitArray(int capacity)
{
	BufferArray b = malloc(sizeof(struct bufferArray));

	b->arr = malloc(sizeof(int) * capacity);
	b->size = 0;
	b->capacity = capacity;

	return b;
}


int EmptyArray(BufferArray b)
{
	return (b->size == 0) ? 1 : 0;
}


void AddArray(BufferArray b, int elem)
{
	if (b != NULL && b->arr != NULL && b->size < b->stackpointer) {
		b->arr[b->size++] = elem;
	}
}


int NextArray(BufferArray b, int *elem)
{
	int r = 0;

	if (b != NULL && b->arr != NULL && b->size > 0) {
		*elem = b->arr[b->size - 1];
		r++;
	}

	return r;
}


int RemoveArray(BufferArray b, int *elem)
{
	int r = 0;

	if (b != NULL && b->arr != NULL && b->size > 0) {
		*elem = b->arr[--(b->size)];
		r++;
	}

	return r;
}


void ClearArray(BufferArray b)
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