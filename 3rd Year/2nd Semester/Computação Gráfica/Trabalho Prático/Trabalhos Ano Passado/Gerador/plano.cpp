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
    
    switch (ori) {
        case 1:
            if (flag==1){ 
                //Imprimir maxX, minX, maxY, minY, maxZ, minZ para o ViewFrustumCulling
                fprintf(f, "%f %f %f %f %f %f\n",lado/2.0f,-lado/2.0f,altura/2.0f, -altura/2.0f,z_index, z_index);
                fprintf(f,"%d\n",2*camadas*fatias*9);
            }
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
            if (flag==1){ 
                //Imprimir maxX, minX, maxY, minY, maxZ, minZ para o ViewFrustumCulling
                fprintf(f, "%f %f %f %f %f %f\n",lado/2.0f,-lado/2.0f,altura/2.0f, -altura/2.0f,z_index, z_index);
                fprintf(f,"%d\n",2*camadas*fatias*9);
            }
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
            if (flag==1){ 
                //Imprimir maxX, minX, maxY, minY, maxZ, minZ para o ViewFrustumCulling
                fprintf(f, "%f %f %f %f %f %f\n",z_index, z_index,altura/2.0f, -altura/2.0f,lado/2.0f,-lado/2.0f);
                fprintf(f,"%d\n",2*camadas*fatias*9);
            }
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
            if (flag==1){ 
                //Imprimir maxX, minX, maxY, minY, maxZ, minZ para o ViewFrustumCulling
                fprintf(f, "%f %f %f %f %f %f\n",z_index, z_index,altura/2.0f, -altura/2.0f,lado/2.0f,-lado/2.0f);
                fprintf(f,"%d\n",2*camadas*fatias*9);
            }
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
            if (flag==1){ 
                //Imprimir maxX, minX, maxY, minY, maxZ, minZ para o ViewFrustumCulling
                fprintf(f, "%f %f %f %f %f %f\n",altura/2.0f, -altura/2.0f,z_index, z_index,lado/2.0f,-lado/2.0f);
                fprintf(f,"%d\n",2*camadas*fatias*9);
            }
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
            if (flag==1){ 
                //Imprimir maxX, minX, maxY, minY, maxZ, minZ para o ViewFrustumCulling
                fprintf(f, "%f %f %f %f %f %f\n",altura/2.0f, -altura/2.0f,z_index, z_index,lado/2.0f,-lado/2.0f);
                fprintf(f,"%d\n",2*camadas*fatias*9);
            }
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


void planoVBO(float altura, float lado, int camadas, int fatias, float z_index, int ori, FILE *f){
    int k=0,j=0,v=0, i=0, avanco,n=0,t=0;
    float l_const=lado/fatias, alt_const=altura/camadas,alt_ori=-altura/2,lado_ori=-lado/2;
    float texFactor_fatias=1.0f/fatias;
    float texFactor_camadas=1.0f/camadas;
   
    
    int n_pontos=(fatias+1)*(camadas+1)*3;
    int n_indices=(2*fatias*camadas)*3;
    int tex_pontos=(n_pontos*2)/3;
    
    //Alocações de memória
    float *vertexB=(float*)malloc(n_pontos*sizeof(float)),
    *normalB=(float*)malloc(n_pontos*sizeof(float)),
    *texB=(float*)malloc(tex_pontos*sizeof(float));

    int *indices=(int*)malloc(n_indices*sizeof(int));
    
    switch (ori) {
        case 1:
            //Imprimir maxX, minX, maxY, minY, maxZ, minZ para o ViewFrustumCulling
            fprintf(f, "%f %f %f %f %f %f\n",lado/2.0f,-lado/2.0f,altura/2.0f, -altura/2.0f,z_index, z_index);
            for(altura=alt_ori;j<=camadas;j++){
                k=0;
                avanco=j*(fatias+1);
                for(lado=lado_ori;k<=fatias;k++){
                    //Inserir Ponto
                    vertexB[v++]=lado;vertexB[v++]=altura;vertexB[v++]=z_index;
                    normalB[n++]=0;normalB[n++]=0;normalB[n++]=1;
                    
                    texB[t++]=k*texFactor_fatias;texB[t++]=j*texFactor_camadas;
                  
                    if(k!=fatias && j!=camadas){
                        indices[i++]=avanco+k;
                        indices[i++]=avanco+k+1;
                        indices[i++]=avanco+fatias+1+k;
                        
                        indices[i++]=avanco+k+1;
                        indices[i++]=avanco+fatias+1+k+1;
                        indices[i++]=avanco+fatias+1+k;
                        

                    }
                    lado+=l_const;
                }
                altura+=alt_const;
            }
            break;
        case 2:
            //Imprimir maxX, minX, maxY, minY, maxZ, minZ para o ViewFrustumCulling
            fprintf(f, "%f %f %f %f %f %f\n",lado/2.0f,-lado/2.0f,altura/2.0f, -altura/2.0f,z_index, z_index);
            for(altura=alt_ori;j<=camadas;j++){
                k=0;
                avanco=j*(fatias+1);
                for(lado=lado_ori;k<=fatias;k++){
                    //Inserir Ponto
                    vertexB[v++]=lado;vertexB[v++]=altura;vertexB[v++]=z_index;
                    normalB[n++]=0;normalB[n++]=0;normalB[n++]=-1;
                    texB[t++]=k*texFactor_fatias;texB[t++]=j*texFactor_camadas;
                    if(k!=fatias && j!=camadas){
                        indices[i++]=avanco+k;
                        indices[i++]=avanco+fatias+1+k;
                        indices[i++]=avanco+k+1;
                        
                        indices[i++]=avanco+k+1;
                        indices[i++]=avanco+fatias+1+k;
                        indices[i++]=avanco+fatias+1+k+1;
                    }
                    lado+=l_const;
                }
                altura+=alt_const;
            }
            break;
        
        case 3:
            //Imprimir maxX, minX, maxY, minY, maxZ, minZ para o ViewFrustumCulling
            fprintf(f, "%f %f %f %f %f %f\n",z_index, z_index,altura/2.0f, -altura/2.0f,lado/2.0f,-lado/2.0f);
            for(altura=alt_ori;j<=camadas;j++){
                k=0;
                avanco=j*(fatias+1);
                for(lado=lado_ori;k<=fatias;k++){
                    //Inserir Ponto
                    vertexB[v++]=z_index;vertexB[v++]=altura;vertexB[v++]=lado;
                    normalB[n++]=1;normalB[n++]=0;normalB[n++]=0;
                    texB[t++]=k*texFactor_fatias;texB[t++]=j*texFactor_camadas;
                    if(k!=fatias && j!=camadas){
                        indices[i++]=avanco+k;
                        indices[i++]=avanco+fatias+1+k;
                        indices[i++]=avanco+k+1;
                        
                        indices[i++]=avanco+k+1;
                        indices[i++]=avanco+fatias+1+k;
                        indices[i++]=avanco+fatias+1+k+1;
                    }
                    lado+=l_const;
                }
                altura+=alt_const;
            }
            break;
        case 4:
            //Imprimir maxX, minX, maxY, minY, maxZ, minZ para o ViewFrustumCulling
            fprintf(f, "%f %f %f %f %f %f\n",z_index, z_index,altura/2.0f, -altura/2.0f,lado/2.0f,-lado/2.0f);
            for(altura=alt_ori;j<=camadas;j++){
                k=0;
                avanco=j*(fatias+1);
                for(lado=lado_ori;k<=fatias;k++){
                    //Inserir Ponto
                    vertexB[v++]=z_index;vertexB[v++]=altura;vertexB[v++]=lado;
                    normalB[n++]=-1;normalB[n++]=0;normalB[n++]=0;
                    texB[t++]=k*texFactor_fatias;texB[t++]=j*texFactor_camadas;
                    if(k!=fatias && j!=camadas){
                        indices[i++]=avanco+k;
                        indices[i++]=avanco+k+1;
                        indices[i++]=avanco+fatias+1+k;
                        
                        indices[i++]=avanco+k+1;
                        indices[i++]=avanco+fatias+1+k+1;
                        indices[i++]=avanco+fatias+1+k;
                    }
                    lado+=l_const;
                }
                altura+=alt_const;
            }
            break;
        case 5:
            //Imprimir maxX, minX, maxY, minY, maxZ, minZ para o ViewFrustumCulling
            fprintf(f, "%f %f %f %f %f %f\n",altura/2.0f, -altura/2.0f,z_index, z_index,lado/2.0f,-lado/2.0f);
            for(altura=alt_ori;j<=camadas;j++){
                k=0;
                avanco=j*(fatias+1);
                for(lado=lado_ori;k<=fatias;k++){
                    //Inserir Ponto
                    vertexB[v++]=altura;vertexB[v++]=z_index;vertexB[v++]=lado;
                    normalB[n++]=0;normalB[n++]=1;normalB[n++]=0;
                    texB[t++]=k*texFactor_fatias;texB[t++]=j*texFactor_camadas;
                    if(k!=fatias && j!=camadas){
                        indices[i++]=avanco+k;
                        indices[i++]=avanco+k+1;
                        indices[i++]=avanco+fatias+1+k;
                        
                        indices[i++]=avanco+k+1;
                        indices[i++]=avanco+fatias+1+k+1;
                        indices[i++]=avanco+fatias+1+k;
                    }
                    lado+=l_const;
                }
                altura+=alt_const;
            }
            break;
        case 6:
            //Imprimir maxX, minX, maxY, minY, maxZ, minZ para o ViewFrustumCulling
            fprintf(f, "%f %f %f %f %f %f\n",altura/2.0f, -altura/2.0f,z_index, z_index,lado/2.0f,-lado/2.0f);
            for(altura=alt_ori;j<=camadas;j++){
                k=0;
                avanco=j*(fatias+1);
                for(lado=lado_ori;k<=fatias;k++){
                    //Inserir Ponto
                    vertexB[v++]=altura;vertexB[v++]=z_index;vertexB[v++]=lado;
                    normalB[n++]=0;normalB[n++]=-1;normalB[n++]=0;
                    texB[t++]=k*texFactor_fatias;texB[t++]=j*texFactor_camadas;
                    if(k!=fatias && j!=camadas){
                        indices[i++]=avanco+k;
                        indices[i++]=avanco+fatias+1+k;
                        indices[i++]=avanco+k+1;
                        
                        indices[i++]=avanco+k+1;
                        indices[i++]=avanco+fatias+1+k;
                        indices[i++]=avanco+fatias+1+k+1;
                    }
                    lado+=l_const;
                }
                altura+=alt_const;
            }
            break;

        
    }
    
 
    //Imprimir os vertices, indices, normais e coordenadas de textura
    fprintf(f, "%d\n",n_pontos);
    for(i=0;i<n_pontos;i+=3)
        fprintf(f, "%f %f %f\n",vertexB[i],vertexB[i+1],vertexB[i+2]);

    fprintf(f, "%d\n",n_indices);
    for(i=0;i<n_indices;i+=3)
        fprintf(f, "%d %d %d\n",indices[i],indices[i+1],indices[i+2]);   

    for(i=0;i<n_pontos;i+=3)
        fprintf(f, "%f %f %f\n",normalB[i],normalB[i+1],normalB[i+2]);

    for(i=0;i<tex_pontos ;i+=2)
        fprintf(f, "%f %f\n",texB[i],texB[i+1]);

    free(vertexB);
    free(normalB);
    free(texB);

}


