//
//  plano.cpp
//  CG-FORMAS-PRIMARIAS
//
//  Created by Hélder José Alves Gonçalves on 28/02/14.
//  Copyright (c) 2014 Hélder José Alves Gonçalves. All rights reserved.
//

#include "plano.h"

/* Tipos de planos
 1 -> +XoY
 2 -> -XoY
 
 3 -> +ZoY
 4 -> -ZoY
 
 5 -> +ZoX
 6 -> -ZoX
 
*/

void plano(float altura, float lado, int camadas, int fatias, float z_index, int ori, FILE* f, int flag){
    int i;
    float l_const=lado/fatias, alt_const=altura/camadas,alt_ori=-altura/2,lado_ori=-lado/2;

    if (flag==1) fprintf(f,"%d\n",2*camadas*fatias*9);
    
    switch (ori) {
        case 1:
            for(altura=alt_ori;camadas>0;camadas--){
                i=0;
                for(lado=lado_ori;i<fatias;i++){
                    
                    fprintf(f,"%f %f %f\n",lado,altura, z_index);
                    fprintf(f,"%f %f %f\n",lado+l_const,altura, z_index);
                    fprintf(f,"%f %f %f\n",lado,altura+alt_const, z_index);
            
                    fprintf(f,"%f %f %f\n",lado+l_const,altura, z_index);
                    fprintf(f,"%f %f %f\n",lado+l_const,altura+alt_const, z_index);
                    fprintf(f,"%f %f %f\n",lado,altura+alt_const, z_index);
                    lado+=l_const;
                }
                altura+=alt_const;
            }
            break;
        case 2:
            for(altura=alt_ori;camadas>0;camadas--){
                i=0;
                for(lado=lado_ori;i<fatias;i++){
                    
                    fprintf(f,"%f %f %f\n",lado,altura, z_index);
                    fprintf(f,"%f %f %f\n",lado,altura+alt_const, z_index);
                    fprintf(f,"%f %f %f\n",lado+l_const,altura, z_index);
                    
                    fprintf(f,"%f %f %f\n",lado+l_const,altura, z_index);
                    fprintf(f,"%f %f %f\n",lado,altura+alt_const, z_index);
                    fprintf(f,"%f %f %f\n",lado+l_const,altura+alt_const, z_index);
                    lado+=l_const;
                }
                altura+=alt_const;
            }
            break;
        case 3:
            for(altura=alt_ori;camadas>0;camadas--){
                i=0;
                for(lado=lado_ori;i<fatias;i++){
                    
                    fprintf(f,"%f %f %f\n",z_index,altura, lado);
                    fprintf(f,"%f %f %f\n",z_index,altura+alt_const, lado);
                    fprintf(f,"%f %f %f\n",z_index,altura, lado+l_const);
                    
                    fprintf(f,"%f %f %f\n",z_index,altura, lado+l_const);
                    fprintf(f,"%f %f %f\n",z_index,altura+alt_const, lado);
                    fprintf(f,"%f %f %f\n",z_index,altura+alt_const, lado+l_const);
                    lado+=l_const;
                }
                altura+=alt_const;
            }
            break;
        case 4:
            for(altura=alt_ori;camadas>0;camadas--){
                i=0;
                for(lado=lado_ori;i<fatias;i++){
                    
                    fprintf(f,"%f %f %f\n",z_index,altura, lado);
                    fprintf(f,"%f %f %f\n",z_index,altura, lado+l_const);
                    fprintf(f,"%f %f %f\n",z_index,altura+alt_const, lado);
                    
                    fprintf(f,"%f %f %f\n",z_index,altura,lado+l_const);
                    fprintf(f,"%f %f %f\n",z_index,altura+alt_const, lado+l_const);
                    fprintf(f,"%f %f %f\n",z_index,altura+alt_const, lado);
                    lado+=l_const;
                }
                altura+=alt_const;
            }
            break;
        case 5:
            for(altura=alt_ori;camadas>0;camadas--){
                i=0;
                for(lado=lado_ori;i<fatias;i++){
                    
                    fprintf(f,"%f %f %f\n",altura,z_index, lado);
                    fprintf(f,"%f %f %f\n",altura,z_index, lado+l_const);
                    fprintf(f,"%f %f %f\n",altura+alt_const,z_index, lado);
                    
                    fprintf(f,"%f %f %f\n",altura,z_index,lado+l_const);
                    fprintf(f,"%f %f %f\n",altura+alt_const,z_index, lado+l_const);
                    fprintf(f,"%f %f %f\n",altura+alt_const,z_index, lado);
                    lado+=l_const;
                }
                altura+=alt_const;
            }
            break;
        case 6:
            for(altura=alt_ori;camadas>0;camadas--){
                i=0;
                for(lado=lado_ori;i<fatias;i++){
                    
                    fprintf(f,"%f %f %f\n",altura,z_index, lado);
                    fprintf(f,"%f %f %f\n",altura+alt_const,z_index, lado);
                    fprintf(f,"%f %f %f\n",altura,z_index, lado+l_const);
                    
                    fprintf(f,"%f %f %f\n",altura,z_index, lado+l_const);
                    fprintf(f,"%f %f %f\n",altura+alt_const,z_index, lado);
                    fprintf(f,"%f %f %f\n",altura+alt_const,z_index, lado+l_const);
                    lado+=l_const;
                }
                altura+=alt_const;
            }
            break;
            
        default:
            break;
    }
}