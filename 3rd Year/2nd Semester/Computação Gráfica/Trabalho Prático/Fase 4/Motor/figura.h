#include <iostream>
#include <GL/glut.h>

using namespace std;

typedef struct modeloVBO {
	const char *nome;
	GLuint *buffers;
	GLuint *indices;
	int numIndices;
}*ModeloVBO, ListaV;

typedef struct modeloTR {
	const char *nome;
	float* vertices;
	int numPontos;
}*ModeloTR, ListaTR;

typedef struct figura {
	short tipoFigura;

	union {
		ModeloVBO modeloVBO;
		ModeloTR modeloTR;
	}option;

	struct figura *next;
}*Figura, ListaF;

Figura adicionaModeloVBO(const char *nome, GLuint *buffers, int numIndices, unsigned short *indices, Figura l);
Figura parsingModeloVBO(const char* filename, Figura lista);
void desenhaModeloVBO(ModeloVBO modelo);

Figura adicionaModeloTR(const char *nome, float *vertices, int numPontos, Figura l);
Figura parsingModeloTR(const char* filename, Figura lista);
void desenhaModeloTR(ModeloTR modelo);

Figura pesquisaFigura(const char* nomeFigura, Figura lista);




