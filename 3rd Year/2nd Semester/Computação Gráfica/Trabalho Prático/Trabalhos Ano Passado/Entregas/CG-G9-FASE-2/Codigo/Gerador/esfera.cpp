//
//  esfera.cpp
//  CG-FORMAS-PRIMARIAS
//
//  Created by Hélder José Alves Gonçalves on 27/02/14.
//  Copyright (c) 2014 Hélder José Alves Gonçalves. All rights reserved.
//

#include "esfera.h"

void esfera(float raio, int camadas, int fatias, FILE* f){
    float   angulo_cir=(2*M_PI)/fatias,
            angulo_h=(M_PI)/camadas,
            x,y,l_aux,lh_aux,h_aux1,h_aux2=M_PI_2;
    
    h_aux1=h_aux2;
    h_aux2+=angulo_h;
    y=0;
    
    fprintf(f,"%d\n",2*fatias*(camadas-1)*9);

    for (l_aux=0; l_aux<fatias; l_aux++) {
        x=y;
        y+=angulo_cir;
        fprintf(f,"%f %f %f\n",raio*sin(x)*cos(h_aux2), raio*sin(h_aux2), raio*cos(x)*cos(h_aux2));
        fprintf(f,"%f %f %f\n",raio*sin(y)*cos(h_aux2), raio*sin(h_aux2), raio*cos(y)*cos(h_aux2));
        fprintf(f,"%f %f %f\n",raio*sin(y)*cos(h_aux1), raio*sin(h_aux1), raio*cos(y)*cos(h_aux1));
    }
    
    for(lh_aux=1;lh_aux<camadas-1;lh_aux++){
        h_aux1=h_aux2;
        h_aux2+=angulo_h;
        y=0;
        
        for (l_aux=0; l_aux<fatias; l_aux++) {
            x=y;
            y+=angulo_cir;
            fprintf(f,"%f %f %f\n",raio*sin(x)*cos(h_aux1), raio*sin(h_aux1), raio*cos(x)*cos(h_aux1));
            fprintf(f,"%f %f %f\n",raio*sin(x)*cos(h_aux2), raio*sin(h_aux2), raio*cos(x)*cos(h_aux2));
            fprintf(f,"%f %f %f\n",raio*sin(y)*cos(h_aux1), raio*sin(h_aux1), raio*cos(y)*cos(h_aux1));

            fprintf(f,"%f %f %f\n",raio*sin(x)*cos(h_aux2), raio*sin(h_aux2), raio*cos(x)*cos(h_aux2));
            fprintf(f,"%f %f %f\n",raio*sin(y)*cos(h_aux2), raio*sin(h_aux2), raio*cos(y)*cos(h_aux2));
            fprintf(f,"%f %f %f\n",raio*sin(y)*cos(h_aux1), raio*sin(h_aux1), raio*cos(y)*cos(h_aux1));
        }
    }
    h_aux1=h_aux2;
    h_aux2+=angulo_h;
    y=0;
    
    for (l_aux=0; l_aux<fatias; l_aux++) {
        x=y;
        y+=angulo_cir;
        fprintf(f,"%f %f %f\n",raio*sin(x)*cos(h_aux1), raio*sin(h_aux1), raio*cos(x)*cos(h_aux1));
        fprintf(f,"%f %f %f\n",raio*sin(x)*cos(h_aux2), raio*sin(h_aux2), raio*cos(x)*cos(h_aux2));
        fprintf(f,"%f %f %f\n",raio*sin(y)*cos(h_aux1), raio*sin(h_aux1), raio*cos(y)*cos(h_aux1));
    }
   
}
