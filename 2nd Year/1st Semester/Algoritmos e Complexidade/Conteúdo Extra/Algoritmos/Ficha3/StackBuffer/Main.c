#include <stdio.h>
#include "StackBuffer.h"


int main(void)
{
	/* 
	BufferLList b = InitLL();
	int x = 0;

	AddLL(b, 1);
	AddLL(b, 5);
	AddLL(b, 1);
	AddLL(b, 6);
	AddLL(b, 8);
	AddLL(b, 10);

	printf("Vazia: %d\n", EmptyLL(b));

	NextLL(b, &x);

	printf("Next: %d\n", x);

	RemoveLL(b, &x);

	NextLL(b, &x);

	printf("Next: %d\n", x);

	ClearLL(b);
	*/

	BufferArray b = InitArray(10);
	int x = 0;

	AddArray(b, 1);
	AddArray(b, 5);
	AddArray(b, 1);
	AddArray(b, 6);
	AddArray(b, 8);
	AddArray(b, 10);

	printf("Vazia: %d\n", EmptyArray(b));

	NextArray(b, &x);

	printf("Next: %d\n", x);

	RemoveArray(b, &x);

	NextArray(b, &x);

	printf("Next: %d\n", x);

	ClearArray(b);

	getchar();

	return 0;
}