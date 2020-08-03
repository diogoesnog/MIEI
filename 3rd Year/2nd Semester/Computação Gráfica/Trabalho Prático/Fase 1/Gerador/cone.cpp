#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include "cone.h"
#include <fstream>

using namespace std;

void cone(float raio, float altura, int fatias, int camadas, string ficheiro) {

	ofstream f;
	f.open(ficheiro.c_str());

	// Criação dos triângulos da base
	for (int i = 0; i < fatias; i++) {

		float anguloFatia = (2 * M_PI)/fatias;
		float cumulativoAngulo = i * (2 * M_PI)/fatias;

		f << 0 << " " << 0 << " " << 0 << " ";
		f << raio * sin(anguloFatia + cumulativoAngulo) << " " << 0 << " " << raio * cos(anguloFatia + cumulativoAngulo) << " ";
		f << raio * sin(cumulativoAngulo) << " " << 0 << " " << raio * cos(cumulativoAngulo) << "\n";
	}

	// Altura inicial a que se vai somar o tamanho de cada camada (corresponde ao tamanhoNivel)
	float alturaInicial = 0;
	float mul = raio/camadas;
	float tamanhoNivel = altura/camadas;

	for (int i=0; i<camadas; i++) {

		float parteCima = mul * (i + 1);
		float parteBaixo = mul * i;

		for (int j=0; j<fatias; j++) {

			float anguloSuperior = j * ((2 * M_PI)/fatias);
			float anguloInferior = (j + 1)*((2 * M_PI)/fatias);

			f << (raio - parteCima)*sin(anguloSuperior) << " " << alturaInicial + tamanhoNivel << " " << (raio - parteCima)*cos(anguloSuperior) << " ";
			f << (raio - parteBaixo)*sin(anguloSuperior) << " " << alturaInicial << " " << (raio - parteBaixo)*cos(anguloSuperior) << " ";
			f << (raio - parteBaixo)*sin(anguloInferior) << " " << alturaInicial << " " << (raio - parteBaixo)*cos(anguloInferior) << " ";

			f << (raio - parteCima)*sin(anguloInferior) << " " << alturaInicial + tamanhoNivel << " " << (raio - parteCima)*cos(anguloInferior) << " ";
			f << (raio - parteCima)*sin(anguloSuperior) << " " << alturaInicial + tamanhoNivel << " " << (raio - parteCima)*cos(anguloSuperior) << " ";
			f << (raio - parteBaixo)*sin(anguloInferior) << " " << alturaInicial << " " << (raio - parteBaixo)*cos(anguloInferior) << " ";
		}
		alturaInicial += tamanhoNivel;
	}
	f.close();
}
