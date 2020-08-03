#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <cstring>
#include <fstream>
#include <GL/glew.h>
#include <GL/glut.h>

#include "figura.h"

// Funções para os modelos em modo VBO.

Figura adicionaModeloVBO(const char* nome, GLuint *buffers, int numIndices, GLuint * indices, Figura lista){

	Figura figura = (Figura) malloc(sizeof(ListaF));
	ModeloVBO novoVBO = (ModeloVBO)malloc(sizeof(ListaV));

	novoVBO->nome = nome;
	novoVBO->buffers = buffers;
	novoVBO->indices = indices;
	novoVBO->numIndices = numIndices;

	figura->next = lista;
	figura->tipoFigura = 2;
	figura->option.modeloVBO = novoVBO;

	return figura;

}

Figura parsingModeloVBO(const char* filename, Figura lista) {
	int	numPontos,
		numIndices,
		i = 0;

	unsigned short* indices, ix, iy, iz;
	float* vertices, vx, vy, vz;

	ifstream input_file(filename);

	//GLuint *buffers = NULL;
	GLuint buffers[1];
	GLuint indicesG[1];

	// Lê o número total de pontos. Aloca memória para o array de vértices.
	input_file >> numPontos;
	vertices = (float*)malloc(numPontos * sizeof(float));

	// Lê todos os pontos existentes no ficheiro consoante o número total obtido antes.
	while (i < numPontos) {
		input_file >> vx >> vy >> vz;
		vertices[i++] = vx;
		vertices[i++] = vy;
		vertices[i++] = vz;
	}

	i = 0;

	//Lê o número total de indices e aloca memória
	input_file >> numIndices;
	indices = (unsigned short*)malloc(numIndices * sizeof(unsigned short));

	//Lê todos os indices que estão no ficheiro
	while (input_file >> ix >> iy >> iz) {

		indices[i++] = ix;
		indices[i++] = iy;
		indices[i++] = iz;
	}

	input_file.close();

	// Ativação dos Buffers.
	glEnableClientState(GL_VERTEX_ARRAY);

	// Aloca memória para esses mesmos Buffers.

	// Geração dos VBOs.
	glGenBuffers(1, buffers);
	glGenBuffers(1, indicesG);

	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesG[0]);
	glBufferData(GL_ARRAY_BUFFER, numPontos * sizeof(float), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numPontos * sizeof(float), indices, GL_STATIC_DRAW);

	free(vertices);
	free(indices);

	// Adiciona a VBO à estrutura definida.
	return adicionaModeloVBO(filename, buffers, numPontos, indicesG, lista);
}

void desenhaModeloVBO(ModeloVBO modelo) {

	glBindBuffer(GL_ARRAY_BUFFER, modelo->buffers[0]);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelo->indices[0]);
	glDrawElements(GL_TRIANGLES, modelo->numIndices, GL_UNSIGNED_SHORT, NULL);
	//glDrawArrays(GL_TRIANGLES, 0, modelo->numIndices);

	// Não conseguimos colocar a funcionar.
}

// Funções para os modelos em modo normal (Tempo Real).

Figura adicionaModeloTR(const char* nome, float *vertices, int numPontos, Figura lista){

	Figura figura = (Figura) malloc(sizeof(ListaF));
	ModeloTR novoTR = (ModeloTR) malloc(sizeof(ListaTR));

	novoTR->nome = nome;
	novoTR->vertices = vertices;
	novoTR->numPontos = numPontos;

	figura->next = lista;
	figura->tipoFigura = 1;
	figura->option.modeloTR = novoTR;

	return figura;
}

Figura parsingModeloTR(const char* filename, Figura lista) {

	ifstream input_file(filename);

	float	*vertices, x, y, z;
	int		i = 0, npontos;

	// Lê o número total de pontos. Aloca memória para o array de vértices.
	input_file >> npontos;
	vertices = (float*)malloc(sizeof(float) * npontos);

	// Lê todos os pontos existentes no ficheiro consoante o número total obtido antes.
	while (input_file >> x >> y >> z) {
		vertices[i++] = x;
		vertices[i++] = y;
		vertices[i++] = z;
	}

	input_file.close();

	// Adiciona modelo à estrutura definida.
	return adicionaModeloTR(filename, vertices, npontos, lista);
}

void desenhaModeloTR(ModeloTR modelo){
	
	// Usado para as cores.
	srand(time(NULL));

	float *vertices = modelo->vertices;
	
	int i;

	glBegin(GL_TRIANGLES);

	for (i=0; i<(modelo->numPontos); i+=3){
		float vermelho = (rand() % 256);
		float verde = (rand() % 256);
		float azul = (rand() % 256);

		glColor3f(vermelho / 255, verde / 255, azul / 255);
		glVertex3f(vertices[i], vertices[i + 1], vertices[i + 2]);
	}

	glEnd();
}

// Função universal que permite pesquisar uma figura consoante o seu tipo.
// Usada tanto para os modelos em tempo real como para os modelos VBO.

Figura pesquisaFigura(const char* nomeFigura, Figura lista) {

	while (lista) {

		if (lista->tipoFigura == 1) {
			if (strcmp(nomeFigura, lista->option.modeloTR->nome) == 0)
				return lista;
		}
		else {
			if (strcmp(nomeFigura, lista->option.modeloVBO->nome) == 0)
				return lista;
		}

		lista = lista->next;
	}
	return NULL;
}