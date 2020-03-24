#include <stdio.h>
#define DEFAULT_SIZE 64

struct buffer {
	char * buff;
	int capacity;
	int stored;
}*Buff;


Buff initBuff(){
	Buff buffer = (Buff)malloc(sizeof(DEFAULT_SIZE));
	char * buff = malloc(sizeof(DEFAULT_SIZE));
	buffer->buff = buff;
	buffer->capacity = DEFAULT_SIZE;
	buffer->stored = 0;
	return buffer;
}
