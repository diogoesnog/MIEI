#define _USE_MATH_DEFINES

#include <cmath>
#include <math.h>
#include <fstream>

#include "cone.h"

using namespace std;

// Função que permite gerar todos os pontos de um cone - Modo Tempo Real.

void cone(float raio, float altura, int fatias, int camadas, string ficheiro){

	// Abrir o ficheiro para escrita dos pontos.
	ofstream f;
	f.open(ficheiro.c_str());

	// Criação dos triângulos que constituem a base do Cone.
	for (int i=0; i<fatias; i++){

		float anguloFatia = (2 * M_PI)/fatias;
		float cumulativoAngulo = i*(2*M_PI)/fatias;

		f << 0 << " " << 0 << " " << 0 << " ";
		f << raio * sin(anguloFatia+cumulativoAngulo) << " " << 0 << " " << raio*cos(anguloFatia+cumulativoAngulo) << " ";
		f << raio * sin(cumulativoAngulo) << " " << 0 << " " << raio*cos(cumulativoAngulo) << "\n";
	}

	// Altura inicial à qual se vai somar o tamanho de cada camada (corresponde ao tamanhoNivel).
	float alturaInicial = 0;
	float multiplicador = raio/camadas;
	float tamanhoNivel = altura/camadas;

	for (int i=0; i<camadas; i++){

		float parteCima = multiplicador * (i + 1);
		float parteBaixo = multiplicador * i;

		for (int j=0; j<camadas; j++) {

			float anguloSuperior = j*((2*M_PI)/fatias);
			float anguloInferior = (j+1)*((2*M_PI)/fatias);

			f << (raio - parteCima)*sin(anguloSuperior) << " " << alturaInicial+tamanhoNivel << " " << (raio-parteCima)*cos(anguloSuperior) << " ";
			f << (raio - parteBaixo)*sin(anguloSuperior) << " " << alturaInicial << " " << (raio-parteBaixo)*cos(anguloSuperior) << " ";
			f << (raio - parteBaixo)*sin(anguloInferior) << " " << alturaInicial << " " << (raio-parteBaixo)*cos(anguloInferior) << " ";

			f << (raio - parteCima)*sin(anguloInferior) << " " << alturaInicial+tamanhoNivel << " " << (raio-parteCima)*cos(anguloInferior) << " ";
			f << (raio - parteCima)*sin(anguloSuperior) << " " << alturaInicial+tamanhoNivel << " " << (raio-parteCima)*cos(anguloSuperior) << " ";
			f << (raio - parteBaixo)*sin(anguloInferior) << " " << alturaInicial << " " << (raio-parteBaixo)*cos(anguloInferior) << " ";
		}
		alturaInicial += tamanhoNivel;
	}

	// Fechar o ficheiro.
	f.close();
}
