#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cBuffer {
	char * buff;			// data
	char * buff_end;		// end of data buffer
	size_t cap;				// capacidade do buffer
	size_t count;			// nº items no buffer
	char * head;			// pointer para a cabeça do buffer
	char * tail;			// pointer para a tail do buffer
}Cbuff;


/* Função que inicializa o buffer */
void initBuff(Cbuff * cbuff, size_t cap){

	cbuff->buff = malloc (cap * sizeof(char));
	if(cbuff->buff == NULL){
		perror(cbuff->buff);
		return;
	}
	cbuff->buff_end = (char *)cbuff->buff + (cap*sizeof(char));
	cbuff->cap = cap;
	cbuff->count = 0;
	cbuff->tail = cbuff->buff;
	cbuff->head = cbuff->buff;
}

/* Função que dá free à estrutura */
void freeBuff(Cbuff * cbuff){
	free(cbuff->buff);
	free(cbuff);
}

/* Função que insere determinada informação no buff */

int main(){
	Cbuff * cbuff = (Cbuff *) malloc(sizeof(Cbuff));
	initBuff(cbuff,20);
	freeBuff(cbuff);
	//printf("%ld\n",cbuff->count);
	return 0;
}
