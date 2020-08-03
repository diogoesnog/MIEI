/**
@file estado.c
@brief Definição das funções estado2str e str2estado invocadas no ficheiro estado.h. 
*/

#include <stdio.h>
#include "estado.h"

/** \brief O  tamanho máximo do buffer. 
*/
#define MAX_BUFFER		10240

/**
\brief Função que converte um estado numa String.
@param e O estado.
@returns A string correspondente ao estado e.
*/
char *estado2str(ESTADO e) {
	static char buffer[MAX_BUFFER];
	unsigned char *p = (unsigned char *) &e;
    unsigned int i;

	buffer[0] = 0;

	for(i = 0; i < sizeof(ESTADO); i++)
		sprintf(buffer, "%s%02x", buffer, p[i]);
	
	return buffer;
}

/**
\brief Função que converte uma String num estado.
@param argumentos Uma String que contém os argumentos passados à CGI.
@returns O estado correspondente à String dos argumentos.
*/
ESTADO str2estado(char *argumentos) {
	ESTADO e;
	unsigned char *p = (unsigned char *) &e;
	unsigned int i;

	for(i = 0; i < sizeof(ESTADO); i++, argumentos += 2) {
		unsigned int d;
		sscanf(argumentos, "%2x", &d);
		p[i] = (unsigned char) d;
	}
	
	return e;
}
