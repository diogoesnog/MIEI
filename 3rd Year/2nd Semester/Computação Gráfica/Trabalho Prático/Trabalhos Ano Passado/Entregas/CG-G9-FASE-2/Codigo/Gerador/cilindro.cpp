//
//  cilindro.cpp
//  CG-FORMAS-PRIMARIAS
//
//  Created by Hélder José Alves Gonçalves on 27/02/14.
//  Copyright (c) 2014 Hélder José Alves Gonçalves. All rights reserved.
//

#include "cilindro.h"



void cilindro(float raio,int fatias,int camadas,float alt,int aneis, FILE* f){
    float angulo=(2*M_PI)/fatias,x,y=0,l_aux,h_aux1,h_aux2=0, r_aux1,r_aux2;
    int aneis_aux=aneis-1;

    raio=raio/aneis;
    
    fprintf(f,"%d\n",(2*fatias*(aneis-1)+fatias)*9*2 + 2*fatias*camadas*9);

    for(l_aux=0;l_aux<fatias;l_aux++){
            x=y;
            y+=angulo;
            fprintf(f,"%d %f %d\n",0, alt, 0);
            fprintf(f,"%f %f %f\n",raio*sin(x), alt, raio*cos(x));
            fprintf(f,"%f %f %f\n",raio*sin(y), alt, raio*cos(y));
        }
        r_aux2=raio;
        y=0;
        for(aneis--;aneis>0;aneis--){
            r_aux1=r_aux2;
            r_aux2+=raio;
        
           for(l_aux=0;l_aux<fatias;l_aux++){
               x=y;
               y+=angulo;
                fprintf(f,"%f %f %f\n",r_aux1*sin(x), alt, r_aux1*cos(x));
                fprintf(f,"%f %f %f\n",r_aux2*sin(x), alt, r_aux2*cos(x));
                fprintf(f,"%f %f %f\n",r_aux1*sin(y), alt, r_aux1*cos(y));
               
                fprintf(f,"%f %f %f\n",r_aux1*sin(y), alt, r_aux1*cos(y));
                fprintf(f,"%f %f %f\n",r_aux2*sin(x), alt, r_aux2*cos(x));
                fprintf(f,"%f %f %f\n",r_aux2*sin(y), alt, r_aux2*cos(y));
            }
        }
    r_aux2=raio;
    y=0;
        for(l_aux=0;l_aux<fatias;l_aux++){
            x=y;
            y+=angulo;
            fprintf(f,"%d %d %d\n",0, 0, 0);
            fprintf(f,"%f %f %f\n",raio*sin(y), 0.0, raio*cos(y));
            fprintf(f,"%f %f %f\n",raio*sin(x), 0.0, raio*cos(x));
        }
        
        
        for(aneis=aneis_aux;aneis>0;aneis--){
            r_aux1=r_aux2;
            r_aux2+=raio;
            
            for(l_aux=0;l_aux<fatias;l_aux++){
                x=y;
                y+=angulo;
                fprintf(f,"%f %f %f\n",r_aux1*sin(x), 0.0, r_aux1*cos(x));
                fprintf(f,"%f %f %f\n",r_aux1*sin(y), 0.0, r_aux1*cos(y));
                fprintf(f,"%f %f %f\n",r_aux2*sin(x), 0.0, r_aux2*cos(x));
                
                fprintf(f,"%f %f %f\n",r_aux1*sin(y), 0.0, r_aux1*cos(y));
                fprintf(f,"%f %f %f\n",r_aux2*sin(y), 0.0, r_aux2*cos(y));
                fprintf(f,"%f %f %f\n",r_aux2*sin(x), 0.0, r_aux2*cos(x));
            }
        }

    raio=r_aux2;

    //Corpo
    alt=alt/camadas;
    for(;camadas>0;camadas--){
        h_aux1=h_aux2;
        h_aux2+=alt;
        y=0;
        for (l_aux=0; l_aux<fatias; l_aux++) {
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