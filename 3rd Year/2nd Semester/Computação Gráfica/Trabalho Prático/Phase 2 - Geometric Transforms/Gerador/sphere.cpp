#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include "sphere.h"
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

void sphere(float raio, int fatias, int camadas, string nomeFicheiro) {

	float   anguloCircular = (2 * M_PI) / fatias;
	float   anguloAltura = (M_PI) / camadas;
	float   angCircular1, angCircular2, angAltura1;
	float   angAltura2 = M_PI_2;
	int contadorFatias, contadorCamadas;

	angAltura1 = angAltura2;
	angAltura2 += anguloCircular;
	angCircular2 = 0;

	ofstream f;
	f.open(nomeFicheiro.c_str());
	f << (2 * fatias*(camadas - 1) * 9) << "\n";

	for (contadorFatias = 0; contadorFatias < fatias; contadorFatias++) {
		angCircular1 = angCircular2;
		angCircular2 += anguloCircular;
		f << fixed << setprecision(6) << raio * sin(angCircular1)*cos(angAltura2) << " " << raio * sin(angAltura2) << " " << raio * cos(angCircular1)*cos(angAltura2) << "\n";
		f << fixed << setprecision(6) << raio * sin(angCircular2)*cos(angAltura2) << " " << raio * sin(angAltura2) << " " << raio * cos(angCircular2)*cos(angAltura2) << "\n";
		f << fixed << setprecision(6) << raio * sin(angCircular2)*cos(angAltura1) << " " << raio * sin(angAltura1) << " " << raio * cos(angCircular2)*cos(angAltura1) << "\n";
	}

	for (contadorCamadas = 1; contadorCamadas < camadas-1; contadorCamadas++) {
		angAltura1 = angAltura2;
		angAltura2 += anguloAltura; // Momento em que se aplica a altura
		angCircular2 = 0;

		for (contadorFatias = 0; contadorFatias < fatias; contadorFatias++) {
			angCircular1 = angCircular2;
			angCircular2 += anguloCircular;

			// Primeiro Triângulo
			f << fixed << setprecision(6) << raio * sin(angCircular1)*cos(angAltura1) << " " << raio * sin(angAltura1) << " " << raio * cos(angCircular1)*cos(angAltura1) << "\n";
			f << fixed << setprecision(6) << raio * sin(angCircular1)*cos(angAltura2) << " " << raio * sin(angAltura2) << " " << raio * cos(angCircular1)*cos(angAltura2) << "\n";
			f << fixed << setprecision(6) << raio * sin(angCircular2)*cos(angAltura1) << " " << raio * sin(angAltura1) << " " << raio * cos(angCircular2)*cos(angAltura1) << "\n";

			// Segundo Triângulo
			f << fixed << setprecision(6) << raio * sin(angCircular1)*cos(angAltura2) << " " << raio * sin(angAltura2) << " " << raio * cos(angCircular1)*cos(angAltura2) << "\n";
			f << fixed << setprecision(6) << raio * sin(angCircular2)*cos(angAltura2) << " " << raio * sin(angAltura2) << " " << raio * cos(angCircular2)*cos(angAltura2) << "\n";
			f << fixed << setprecision(6) << raio * sin(angCircular2)*cos(angAltura1) << " " << raio * sin(angAltura1) << " " << raio * cos(angCircular2)*cos(angAltura1) << "\n";
		}
	}

	angAltura1 = angAltura2;
	angAltura2 += anguloAltura; // Momento em que se aplica a altura
	angCircular2 = 0;

	for (contadorFatias = 0; contadorFatias < fatias; contadorFatias++) {
		angCircular1 = angCircular2;
		angCircular2 += anguloCircular;
		f << fixed << setprecision(6) << raio * sin(angCircular1)*cos(angAltura1) << " " << raio * sin(angAltura1) << " " << raio * cos(angCircular1)*cos(angAltura1) << "\n";
		f << fixed << setprecision(6) << raio * sin(angCircular1)*cos(angAltura2) << " " << raio * sin(angAltura2) << " " << raio * cos(angCircular1)*cos(angAltura2) << "\n";
		f << fixed << setprecision(6) << raio * sin(angCircular2)*cos(angAltura1) << " " << raio * sin(angAltura1) << " " << raio * cos(angCircular2)*cos(angAltura1) << "\n";
	}

	f.close();
}