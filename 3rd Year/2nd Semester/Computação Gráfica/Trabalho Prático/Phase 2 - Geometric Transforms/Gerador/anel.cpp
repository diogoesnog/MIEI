#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include "anel.h"
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

//fazer um anel 
void anel(float raio_fora, float raio_dentro,int fatias, int aneis, string nomeFicheiro){
    float angulo=(2*M_PI)/fatias,anguloCircular1,contadorFatias,raio=(raio_fora-raio_dentro)/aneis,altura=0;
    float anguloCircular2=0;
    ofstream f;
	f.open(nomeFicheiro.c_str());
      f<<2*fatias*(aneis)*9<<"\n";
  
    raio_fora=raio_dentro;
    for(;aneis>0;aneis--){
		raio_dentro=raio_fora;
        raio_fora+=raio;
            
        for(contadorFatias=0;contadorFatias<fatias;contadorFatias++){
         anguloCircular1=anguloCircular2;
         anguloCircular2+=angulo;
         f << fixed << setprecision(6) << raio_dentro*sin(anguloCircular1)<<" "<<altura<<" "<<raio_dentro*cos(anguloCircular1) << "\n";
         f << fixed << setprecision(6) << raio_fora*sin(anguloCircular1)<<" "<<altura<<" "<<raio_fora*cos(anguloCircular1) << "\n";
         f << fixed << setprecision(6) << raio_dentro*sin(anguloCircular2)<<" "<<altura<<" "<<raio_dentro*cos(anguloCircular2) << "\n";

         f << fixed << setprecision(6) << raio_dentro*sin(anguloCircular2)<<" "<<altura<<" "<<raio_dentro*cos(anguloCircular2) << "\n";
         f << fixed << setprecision(6) << raio_fora*sin(anguloCircular1)<<" "<<altura<<" "<<raio_fora*cos(anguloCircular1) << "\n";
         f << fixed << setprecision(6) << raio_fora*sin(anguloCircular2)<<" "<<altura<<" "<<raio_fora*cos(anguloCircular2) << "\n";
               
        }
    }

    f.close();
}