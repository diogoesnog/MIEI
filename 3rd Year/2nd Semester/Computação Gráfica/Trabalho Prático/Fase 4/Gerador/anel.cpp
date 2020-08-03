#define _USE_MATH_DEFINES

#include <cmath>
#include <math.h>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "anel.h"

using namespace std;

// Função que permite gerar todos os pontos de um anel.

void anel(float raioFora, float raioDentro, int fatias, int aneis, string nomeFicheiro){

    float	angulo = (2*M_PI)/fatias, 
			anguloCircular1,
			anguloCircular2 = 0,
			raio = (raioFora-raioDentro)/aneis,
			altura = 0;

	int		contadorFatias;

	// Abrir o ficheiro para escrita dos pontos.
	ofstream f;
	f.open(nomeFicheiro.c_str());

	// Coloca no início do ficheiro o número de coordendas que irão ser geradas.
	f << 2*fatias*(aneis)*9 << "\n";
  
    raioFora = raioDentro;

    for(; aneis>0; aneis--){

		raioDentro=raioFora;
        raioFora+=raio;
            
        for(contadorFatias=0; contadorFatias<fatias; contadorFatias++){

			anguloCircular1 = anguloCircular2;
			anguloCircular2 += angulo;

			f << fixed << setprecision(6) << raioDentro*sin(anguloCircular1)<<" "<<altura<<" "<<raioDentro*cos(anguloCircular1) << "\n";
			f << fixed << setprecision(6) << raioFora*sin(anguloCircular1)<<" "<<altura<<" "<<raioFora*cos(anguloCircular1) << "\n";
			f << fixed << setprecision(6) << raioDentro*sin(anguloCircular2)<<" "<<altura<<" "<<raioDentro*cos(anguloCircular2) << "\n";

			f << fixed << setprecision(6) << raioDentro*sin(anguloCircular2)<<" "<<altura<<" "<<raioDentro*cos(anguloCircular2) << "\n";
			f << fixed << setprecision(6) << raioFora*sin(anguloCircular1)<<" "<<altura<<" "<<raioFora*cos(anguloCircular1) << "\n";
			f << fixed << setprecision(6) << raioFora*sin(anguloCircular2)<<" "<<altura<<" "<<raioFora*cos(anguloCircular2) << "\n";
               
        }
    }

	// Fechar o ficheiro.
    f.close();
}