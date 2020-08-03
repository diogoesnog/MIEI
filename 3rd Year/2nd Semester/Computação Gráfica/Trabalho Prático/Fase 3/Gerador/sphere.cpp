#define _USE_MATH_DEFINES

#include <cmath>
#include <math.h>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "sphere.h"

using namespace std;

// Função que permite gerar todos os pontos de uma esfera - Modo Tempo Real.

void sphere(float raio, int fatias, int camadas, string nomeFicheiro){

	float   anguloCircular = (2 * M_PI) / fatias,
			anguloAltura = (M_PI) / camadas,
			angCircular1, 
			angCircular2, 
			angAltura1,
			angAltura2 = M_PI_2;

	int		contadorFatias, contadorCamadas;

	angAltura1 = angAltura2;
	angAltura2 += anguloCircular;
	angCircular2 = 0;

	// Abrir o ficheiro para escrita dos pontos.
	ofstream f;
	f.open(nomeFicheiro.c_str());

	// Coloca no início do ficheiro o número de coordendas que irão ser geradas.
	f << (2*fatias*(camadas-1)*9) << "\n";

	for (contadorFatias=0; contadorFatias<fatias; contadorFatias++){

		angCircular1 = angCircular2;
		angCircular2 += anguloCircular;

		f << fixed << setprecision(6) << raio*sin(angCircular1)*cos(angAltura2) << " " << raio*sin(angAltura2) << " " << raio*cos(angCircular1)*cos(angAltura2) << "\n";
		f << fixed << setprecision(6) << raio*sin(angCircular2)*cos(angAltura2) << " " << raio*sin(angAltura2) << " " << raio*cos(angCircular2)*cos(angAltura2) << "\n";
		f << fixed << setprecision(6) << raio*sin(angCircular2)*cos(angAltura1) << " " << raio*sin(angAltura1) << " " << raio*cos(angCircular2)*cos(angAltura1) << "\n";
	}

	for (contadorCamadas=1; contadorCamadas<camadas-1; contadorCamadas++){

		angAltura1 = angAltura2;
		angAltura2 += anguloAltura; // Momento em que é aplicada a altura.
		angCircular2 = 0;

		for (contadorFatias=0; contadorFatias < fatias; contadorFatias++){

			angCircular1 = angCircular2;
			angCircular2 += anguloCircular;

			// Primeiro Triângulo
			f << fixed << setprecision(6) << raio*sin(angCircular1)*cos(angAltura1) << " " << raio*sin(angAltura1) << " " << raio*cos(angCircular1)*cos(angAltura1) << "\n";
			f << fixed << setprecision(6) << raio*sin(angCircular1)*cos(angAltura2) << " " << raio*sin(angAltura2) << " " << raio*cos(angCircular1)*cos(angAltura2) << "\n";
			f << fixed << setprecision(6) << raio*sin(angCircular2)*cos(angAltura1) << " " << raio*sin(angAltura1) << " " << raio*cos(angCircular2)*cos(angAltura1) << "\n";

			// Segundo Triângulo
			f << fixed << setprecision(6) << raio*sin(angCircular1)*cos(angAltura2) << " " << raio*sin(angAltura2) << " " << raio*cos(angCircular1)*cos(angAltura2) << "\n";
			f << fixed << setprecision(6) << raio*sin(angCircular2)*cos(angAltura2) << " " << raio*sin(angAltura2) << " " << raio*cos(angCircular2)*cos(angAltura2) << "\n";
			f << fixed << setprecision(6) << raio*sin(angCircular2)*cos(angAltura1) << " " << raio*sin(angAltura1) << " " << raio*cos(angCircular2)*cos(angAltura1) << "\n";
		}
	}

	angAltura1 = angAltura2;
	angAltura2 += anguloAltura; // Momento em que é aplicada a altura.
	angCircular2 = 0;

	for (contadorFatias=0; contadorFatias<fatias; contadorFatias++){

		angCircular1 = angCircular2;
		angCircular2 += anguloCircular;

		f << fixed << setprecision(6) << raio*sin(angCircular1)*cos(angAltura1) << " " << raio*sin(angAltura1) << " " << raio*cos(angCircular1)*cos(angAltura1) << "\n";
		f << fixed << setprecision(6) << raio*sin(angCircular1)*cos(angAltura2) << " " << raio*sin(angAltura2) << " " << raio*cos(angCircular1)*cos(angAltura2) << "\n";
		f << fixed << setprecision(6) << raio*sin(angCircular2)*cos(angAltura1) << " " << raio*sin(angAltura1) << " " << raio*cos(angCircular2)*cos(angAltura1) << "\n";
	}

	// Fechar o ficheiro.
	f.close();
}

// Função que permite gerar todos os pontos de uma esfera - Modo VBOs.

void sphereVBO(float raio, int fatias, int camadas, string nomeFicheiro) {
	
	float   anguloCircular = (2 * M_PI) / fatias,
			anguloAltura = (M_PI) / camadas,
			angCircular2 = 0, angAltura2 = M_PI_2;
	
	int		contadorFatias, contadorCamadas;
			
	int		indice = 0, 
			vertice = 0, 
			avanco;

	int numPontos = (2 * fatias*(camadas - 1) * 9);
	int numIndices = (fatias*(camadas-1)*2)*3;

	// Arrays de índices e vértices.
	// Seguido o mesmo que nas aulas práticas
	float *vertexB = (float*) malloc(numPontos*sizeof(float));
	int *indices = (int*) malloc(numIndices*sizeof(int));

	angAltura2 += anguloAltura;

	vertexB[vertice++] = 0; vertexB[vertice++] = raio; vertexB[vertice++] = 0;

	for (contadorFatias=0; contadorFatias<fatias; contadorFatias++){

		vertexB[vertice++] = raio*sin(angCircular2)*cos(angAltura2); vertexB[vertice++] = raio*sin(angAltura2); vertexB[vertice++] = raio*cos(angCircular2)*cos(angAltura2);

		angCircular2 += anguloCircular;
	}


	for (contadorCamadas=1; contadorCamadas<camadas-1; contadorCamadas++){

		angAltura2 += anguloAltura;
		angCircular2 = 0;

		for (contadorFatias = 0; contadorFatias<fatias; contadorFatias++){

			avanco = contadorCamadas*fatias+1;

			vertexB[vertice++] = raio*sin(angCircular2)*cos(angAltura2); vertexB[vertice++] = raio*sin(angAltura2); vertexB[vertice++] = raio*cos(angCircular2)*cos(angAltura2);


			angCircular2 += anguloCircular;
		}
	}

	vertexB[vertice++] = 0; vertexB[vertice++] = -raio; vertexB[vertice++] = 0;


	// Abrir o ficheiro para escrita dos pontos.
	// Impressão dos vértices e índices.
	ofstream f;
	f.open(nomeFicheiro.c_str());

	// Coloca no ficheiro o número de pontos que irão ser gerados.
	f << numPontos << "\n";
	f << numIndices << "\n";
	
	// Imprimir os pontos.
	for (indice = 0; indice < numPontos; indice += 3)
		f << fixed << setprecision(6) << vertexB[indice] << " " << vertexB[indice + 1] << " " << vertexB[indice + 2] << "\n";
}