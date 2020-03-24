//
//  cone.cpp
//  CG-FORMAS-PRIMARIAS
//
//  Created by Hélder José Alves Gonçalves on 10/03/14.
//  Copyright (c) 2014 Hélder José Alves Gonçalves. All rights reserved.
//

#include "cone.h"

void cone(float raio_base, float altura, int fatias, int aneis, int camadas, FILE* f){
    float angulo=(2*M_PI)/fatias,x,y=0,l_aux,  alt_aux1,alt_aux2=0,r_aux1,r_aux2=raio_base;
    altura/=camadas;
    
    float i=1,factor_h=(i/camadas);
    
    circulo(raio_base, fatias, aneis, 0, 0,f);
    for(;camadas>1;camadas--){
        alt_aux1=alt_aux2;
        alt_aux2+=altura;
        y=0;
        i-=factor_h;
        r_aux1=r_aux2;
        r_aux2=raio_base *i;
        
        for (l_aux=0; l_aux<fatias; l_aux++) {
            x=y;
            y+=angulo;
            fprintf(f,"%f %f %f\n",r_aux2*sin(x), alt_aux2, r_aux2*cos(x));
            fprintf(f,"%f %f %f\n",r_aux1*sin(x), alt_aux1, r_aux1*cos(x));
            fprintf(f,"%f %f %f\n",r_aux2*sin(y), alt_aux2, r_aux2*cos(y));

            fprintf(f,"%f %f %f\n",r_aux1*sin(x), alt_aux1, r_aux1*cos(x));
            fprintf(f,"%f %f %f\n",r_aux1*sin(y), alt_aux1, r_aux1*cos(y));
            fprintf(f,"%f %f %f\n",r_aux2*sin(y), alt_aux2, r_aux2*cos(y));
        }
    }
    
    alt_aux1=alt_aux2;
    alt_aux2+=altura;
    y=0;
    i-=factor_h;
    r_aux1=r_aux2;
    r_aux2=raio_base *i;
    
    for (l_aux=0; l_aux<fatias; l_aux++) {
        x=y;
        y+=angulo;  
        fprintf(f,"%f %f %f\n",r_aux1*sin(x), alt_aux1, r_aux1*cos(x));
        fprintf(f,"%f %f %f\n",r_aux1*sin(y), alt_aux1, r_aux1*cos(y));
        fprintf(f,"%f %f %f\n",r_aux2*sin(y), alt_aux2, r_aux2*cos(y));
    }
}

