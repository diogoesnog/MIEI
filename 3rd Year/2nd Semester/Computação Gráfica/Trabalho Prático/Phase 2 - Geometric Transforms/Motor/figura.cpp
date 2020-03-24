#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include "figura.h"

Figura adicionaFigura(const char *nome, float *vertices, int npontos, Figura l) {

	Figura nova = (Figura)malloc(sizeof(Lista));

	nova->nome = nome;
	nova->vertices = vertices;
	nova->npontos = npontos;

	if (l) {
		nova->next = l;
		return nova;
	}
	nova->next = NULL;
	return nova;
}

Figura pesquisaFigura(const char *nome, Figura l) {
	while (l) {
		if (strcmp(nome, l->nome) == 0) return l;
		l = l->next;
	}
	return NULL;
}
