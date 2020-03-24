//
//  cilindro.cpp
//  CG-FORMAS-PRIMARIAS
//
//  Created by Hélder José Alves Gonçalves on 27/02/14.
//  Copyright (c) 2014 Hélder José Alves Gonçalves. All rights reserved.
//

#include "cilindro.h"



void cilindro(float raio,int fatias,int camadas,float alt,int aneis, FILE* f){
    float angulo=(2*M_PI)/fatias,x,y=0,l_aux,h_aux1,h_aux2=0;
    
    circulo(raio, fatias, aneis, 0, 0,f);
    circulo(raio, fatias, aneis, alt, 1,f);
    
    alt=alt/camadas;
    for(;camadas>0;camadas--){
        h_aux1=h_aux2;
        h_aux2+=alt;
        y=0;
        for (l_aux=0; l_aux<=fatias; l_aux++) {
            x=y;
            y+=angulo;
            
            fprintf(f,"%f %f %f\n",raio*sin(x), h_aux2, raio*cos(x));
            fprintf(f,"%f %f %f\n",raio*sin(x), h_aux1, raio*cos(x));
            fprintf(f,"%f %f %f\n",raio*sin(y), h_aux2, raio*cos(y));
            
            fprintf(f,"%f %f %f\n",raio*sin(x), h_aux1, raio*cos(x));
            fprintf(f,"%f %f %f\n",raio*sin(y), h_aux1, raio*cos(y));
            fprintf(f,"%f %f %f\n",raio*sin(y), h_aux2, raio*cos(y));
        }
    }
}