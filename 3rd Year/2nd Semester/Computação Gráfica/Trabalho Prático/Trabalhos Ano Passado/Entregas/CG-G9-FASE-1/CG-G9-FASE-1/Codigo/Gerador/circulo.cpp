//
//  circulo.cpp
//  CG-FORMAS-PRIMARIAS
//
//  Created by Hélder José Alves Gonçalves on 27/02/14.
//  Copyright (c) 2014 Hélder José Alves Gonçalves. All rights reserved.
//

#include "circulo.h"

//ORI --- 1 -> BASE && 0 -> TOPO

void circulo(float raio, int fatias,int aneis, float alt,int ori, FILE* f){
    float angulo=(2*M_PI)/fatias,x,y=0,l_aux, r_aux1,r_aux2;
    raio=raio/aneis;
    if(ori){
        for(l_aux=0;l_aux<=fatias;l_aux++){
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
        
           for(l_aux=0;l_aux<=fatias;l_aux++){
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
    }else{
        for(l_aux=0;l_aux<=fatias;l_aux++){
        	x=y;
            y+=angulo;
            fprintf(f,"%d %f %d\n",0, alt, 0);
            fprintf(f,"%f %f %f\n",raio*sin(y), alt, raio*cos(y));
            fprintf(f,"%f %f %f\n",raio*sin(x), alt, raio*cos(x));
        }
        r_aux2=raio;
        y=0;
        for(aneis--;aneis>0;aneis--){
            r_aux1=r_aux2;
            r_aux2+=raio;
            
            for(l_aux=0;l_aux<=fatias;l_aux++){
                x=y;
                y+=angulo;
                fprintf(f,"%f %f %f\n",r_aux1*sin(x), alt, r_aux1*cos(x));
                fprintf(f,"%f %f %f\n",r_aux1*sin(y), alt, r_aux1*cos(y));
                fprintf(f,"%f %f %f\n",r_aux2*sin(x), alt, r_aux2*cos(x));
                
                fprintf(f,"%f %f %f\n",r_aux1*sin(y), alt, r_aux1*cos(y));
                fprintf(f,"%f %f %f\n",r_aux2*sin(y), alt, r_aux2*cos(y));
                fprintf(f,"%f %f %f\n",r_aux2*sin(x), alt, r_aux2*cos(x));
            }
        }
    }
}