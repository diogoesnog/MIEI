//
//  cilindro.cpp
//  CG-FORMAS-PRIMARIAS
//
//  Created by Hélder José Alves Gonçalves on 27/02/14.
//  Copyright (c) 2014 Hélder José Alves Gonçalves. All rights reserved.
//

#include "cilindro.h"



void cilindro(float raio,int fatias,int camadas,float altura,int aneis, FILE* f){
    float angulo=(2*M_PI)/fatias,x,y=0,l_aux,h_aux1,h_aux2=0, r_aux1,r_aux2;
    int aneis_aux=aneis-1;

    //Imprimir maxX, minX, maxY, minY, maxZ, minZ para o ViewFrustumCulling
    fprintf(f, "%f %f %f %d %f %f\n",raio, -raio,altura,0,raio,-raio);
    fprintf(f,"%d\n",(2*fatias*(aneis-1)+fatias)*9*2 + 2*fatias*camadas*9);

    raio=raio/aneis;

    for(l_aux=0;l_aux<fatias;l_aux++){
            x=y;
            y+=angulo;
            fprintf(f,"%d %f %d\n",0, altura, 0);
            fprintf(f,"%f %f %f\n",raio*sin(x), altura, raio*cos(x));
            fprintf(f,"%f %f %f\n",raio*sin(y), altura, raio*cos(y));
        }
        r_aux2=raio;
        y=0;
        for(aneis--;aneis>0;aneis--){
            r_aux1=r_aux2;
            r_aux2+=raio;
        
           for(l_aux=0;l_aux<fatias;l_aux++){
               x=y;
               y+=angulo;
                fprintf(f,"%f %f %f\n",r_aux1*sin(x), altura, r_aux1*cos(x));
                fprintf(f,"%f %f %f\n",r_aux2*sin(x), altura, r_aux2*cos(x));
                fprintf(f,"%f %f %f\n",r_aux1*sin(y), altura, r_aux1*cos(y));
               
                fprintf(f,"%f %f %f\n",r_aux1*sin(y), altura, r_aux1*cos(y));
                fprintf(f,"%f %f %f\n",r_aux2*sin(x), altura, r_aux2*cos(x));
                fprintf(f,"%f %f %f\n",r_aux2*sin(y), altura, r_aux2*cos(y));
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
    altura=altura/camadas;
    for(;camadas>0;camadas--){
        h_aux1=h_aux2;
        h_aux2+=altura;
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

void cilindroVBO(float raio,int fatias,int camadas,float altura,int aneis, FILE* f){
    float angulo=(2*M_PI)/fatias,y=0,l_aux, r_aux,alt_aux=altura;
    int i=0,v=0,j,n=0,t=0,avanco=0;
    float texFactor_fatias=1.0f/fatias;
    float texFactor_camadas=1.0f/camadas;
    float texFactor_aneis=1.0f/aneis;
    

    int n_pontos=((fatias+1)*(camadas+1)*3) + ((fatias+1)+(fatias+1)*aneis)*6;
    int n_indices= (fatias*camadas*3*2) + (fatias*(aneis-1)*2+fatias)*6;
    int tex_pontos=(n_pontos*2)/3;
    
    //Alocações de memória
    float *vertexB=(float*)malloc(n_pontos*sizeof(float)),
    *normalB=(float*)malloc(n_pontos*sizeof(float)),
    *texB=(float*)malloc(tex_pontos*sizeof(float));
    int *indices=(int*)malloc(n_indices*sizeof(int));


    //------------- Circulo da base ----------------//
    r_aux=raio/aneis;
    
    //Primeiro ponto central
    for (l_aux=0; l_aux<=fatias; l_aux++) {
        vertexB[v++]=0;vertexB[v++]=0;vertexB[v++]=0;
        normalB[n++]=0;normalB[n++]=-1;normalB[n++]=0;
        texB[t++]=l_aux*texFactor_fatias;texB[t++]=1;
    }
    avanco+=fatias+1;
    
    //Primeiro circulo
    for(l_aux=0;l_aux<=fatias;l_aux++){
        
        vertexB[v++]=r_aux*sin(y);vertexB[v++]=0;vertexB[v++]=r_aux*cos(y);
        normalB[n++]=0;normalB[n++]=-1;normalB[n++]=0;
        texB[t++]=l_aux*texFactor_fatias; texB[t++]=1.0f-texFactor_aneis;
        if(l_aux!=fatias){
            indices[i++]=avanco-(fatias+1)+l_aux;
            indices[i++]=avanco+l_aux+1;
            indices[i++]=avanco+l_aux;
        }
        y+=angulo;
    }
    avanco+=fatias+1;
    
    //Aneis da base
    for(j=1;j<aneis;j++){
        r_aux+=raio/aneis;
        y=0;
        for(l_aux=0;l_aux<=fatias;l_aux++){
            
            vertexB[v++]=r_aux*sin(y); vertexB[v++]=0; vertexB[v++]=r_aux*cos(y);
            normalB[n++]=0;normalB[n++]=-1;normalB[n++]=0;
            texB[t++]=l_aux*texFactor_fatias;texB[t++]=1.0f-((j+1)*texFactor_aneis);
            
            if(l_aux!=fatias){
                indices[i++]=avanco-(fatias+1)+l_aux;
                indices[i++]=avanco-(fatias+1)+l_aux+1;
                indices[i++]=avanco+l_aux+1;
                
                indices[i++]=avanco+l_aux;
                indices[i++]=avanco-(fatias+1)+l_aux;
                indices[i++]=avanco+l_aux+1;
            }
            y+=angulo;
        }
        avanco+=fatias+1;
    }

    
    //------------ Corpo ------------//
    r_aux=raio;
    for(j=0;j<=camadas;j++){
        y=0;
        
        for(l_aux=0;l_aux<=fatias;l_aux++){
            
            vertexB[v++]=r_aux*sin(y); vertexB[v++]=alt_aux; vertexB[v++]=r_aux*cos(y);
            normalB[n++]=sin(y);normalB[n++]=0;normalB[n++]=cos(y);
            texB[t++]=l_aux*texFactor_fatias;texB[t++]=j*texFactor_camadas;
            
            if(l_aux!=fatias){
                if(j!=camadas){
                    indices[i++]=avanco+l_aux;
                    indices[i++]=avanco+(fatias+1)+l_aux;
                    indices[i++]=avanco+l_aux+1;
                    
                    indices[i++]=avanco+(fatias+1)+l_aux;
                    indices[i++]=avanco+(fatias+1)+l_aux+1;
                    indices[i++]=avanco+l_aux+1;
                }
            }
            y+=angulo;
        }
        
        avanco+=fatias+1;
        alt_aux-=altura/camadas;
    }

    
    //------------- Circulo do topo -------------//
    r_aux=raio/aneis;
    
    //Primeiro ponto central
    for (l_aux=0; l_aux<=fatias; l_aux++) {
        vertexB[v++]=0;vertexB[v++]=altura;vertexB[v++]=0;
        normalB[n++]=0;normalB[n++]=1;normalB[n++]=0;
        texB[t++]=l_aux*texFactor_fatias;texB[t++]=1;
    }
    avanco+=fatias+1;
    
    //Primeiro circulo
    for(l_aux=0;l_aux<=fatias;l_aux++){
        
        vertexB[v++]=r_aux*sin(y);vertexB[v++]=altura;vertexB[v++]=r_aux*cos(y);
        normalB[n++]=0;normalB[n++]=1;normalB[n++]=0;
        texB[t++]=l_aux*texFactor_fatias; texB[t++]=1.0f-texFactor_aneis;
        if(l_aux!=fatias){
            indices[i++]=avanco-(fatias+1)+l_aux;
            indices[i++]=avanco+l_aux;
            indices[i++]=avanco+l_aux+1;
        }
        y+=angulo;
    }
    avanco+=fatias+1;
    
    //Aneis do topo
    for(j=1;j<aneis;j++){
        r_aux+=raio/aneis;
        y=0;
        for(l_aux=0;l_aux<=fatias;l_aux++){
            
            vertexB[v++]=r_aux*sin(y); vertexB[v++]=altura; vertexB[v++]=r_aux*cos(y);
            normalB[n++]=0;normalB[n++]=1;normalB[n++]=0;
            texB[t++]=l_aux*texFactor_fatias;texB[t++]=1.0f-((j+1)*texFactor_aneis);
            
            if(l_aux!=fatias){
                indices[i++]=avanco-(fatias+1)+l_aux;
                indices[i++]=avanco+l_aux+1;
                indices[i++]=avanco-(fatias+1)+l_aux+1;
                
                indices[i++]=avanco+l_aux;
                indices[i++]=avanco+l_aux+1;
                indices[i++]=avanco-(fatias+1)+l_aux;
            }
            
            y+=angulo;
        }
        avanco+=fatias+1;
    }
    
    //Imprimir maxX, minX, maxY, minY, maxZ, minZ para o ViewFrustumCulling
    fprintf(f, "%f %f %f %d %f %f\n",raio, -raio,altura,0,raio,-raio);
 
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



