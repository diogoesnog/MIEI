//
//  circulo.cpp
//  CG-FORMAS-PRIMARIAS
//
//  Created by Hélder José Alves Gonçalves on 27/02/14.
//  Copyright (c) 2014 Hélder José Alves Gonçalves. All rights reserved.
//

#include "circulo.h"

//ORI --- 1 -> BASE && 0 -> TOPO


void circulo(float raio, int fatias,int aneis, float alt,int ori){
    float angulo=(2*M_PI)/fatias,x,y=0,l_aux, r_aux1,r_aux2;
    raio=raio/aneis;
    if(ori){
        glBegin(GL_TRIANGLES);
        
        for(l_aux=0;l_aux<fatias;l_aux++){
        	x=y;
            y+=angulo;
            glVertex3f(0, alt, 0);
            glVertex3f(raio*sin(x), alt, raio*cos(x));
            glVertex3f(raio*sin(y), alt, raio*cos(y));
        }
        r_aux2=raio;
        y=0;
        for(aneis--;aneis>0;aneis--){
            r_aux1=r_aux2;
            r_aux2+=raio;
            
            for(l_aux=0;l_aux<fatias;l_aux++){
                x=y;
                y+=angulo;
                glVertex3f(r_aux1*sin(x), alt, r_aux1*cos(x));
                glVertex3f(r_aux2*sin(x), alt, r_aux2*cos(x));
                glVertex3f(r_aux1*sin(y), alt, r_aux1*cos(y));
                
                glVertex3f(r_aux1*sin(y), alt, r_aux1*cos(y));
                glVertex3f(r_aux2*sin(x), alt, r_aux2*cos(x));
                glVertex3f(r_aux2*sin(y), alt, r_aux2*cos(y));
            }
        }
        glEnd();
    }else{
        glBegin(GL_TRIANGLES);
        for(l_aux=0;l_aux<fatias;l_aux++){
        	x=y;
            y+=angulo;
            glVertex3f(0, alt, 0);
            glVertex3f(raio*sin(y), alt, raio*cos(y));
            glVertex3f(raio*sin(x), alt, raio*cos(x));
        }
        r_aux2=raio;
        y=0;
        for(aneis--;aneis>0;aneis--){
            r_aux1=r_aux2;
            r_aux2+=raio;
            
            for(l_aux=0;l_aux<=fatias;l_aux++){
                x=y;
                y+=angulo;
                glVertex3f(r_aux1*sin(x), alt, r_aux1*cos(x));
                glVertex3f(r_aux1*sin(y), alt, r_aux1*cos(y));
                glVertex3f(r_aux2*sin(x), alt, r_aux2*cos(x));
                
                glVertex3f(r_aux1*sin(y), alt, r_aux1*cos(y));
                glVertex3f(r_aux2*sin(y), alt, r_aux2*cos(y));
                glVertex3f(r_aux2*sin(x), alt, r_aux2*cos(x));
            }
        }
        glEnd();
    }
}

Circulo::Circulo(float raio, int fatias,int aneis, float alt,int ori){
    
    float angulo=(2*M_PI)/fatias,y=0,l_aux, r_aux;
    int i=0,v=0,j=0,n=0,t=0,avanco=0;
    
    raio=raio/aneis;
    r_aux=raio;
    int n_pontos=((fatias+1)+(fatias+1)*aneis)*3;
    n_indices=(fatias*(aneis-1)*2+fatias)*3;
    float texFactor_aneis=1.0f/aneis;
    float texFactor_fatias=1.0f/fatias;
    
    
    float *vertexB=(float*)malloc(n_pontos*sizeof(float)),
    *normalB=(float*)malloc(n_pontos*sizeof(float)),
    *texB=(float*)malloc((n_pontos*2)/3*sizeof(float));
    indices=(unsigned int*)malloc(n_indices*sizeof(unsigned int));
    
    //Activar Buffers
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    if(ori){
        //Primeiro ponto central
        for (l_aux=0; l_aux<=fatias; l_aux++) {
            vertexB[v++]=0;vertexB[v++]=alt;vertexB[v++]=0;
            normalB[n++]=0;normalB[n++]=1;normalB[n++]=0;
            texB[t++]=l_aux*texFactor_fatias;texB[t++]=1;
        }
        avanco+=fatias+1;
        
        //Primeiro circulo
        for(l_aux=0;l_aux<=fatias;l_aux++){
            
            vertexB[v++]=r_aux*sin(y);vertexB[v++]=alt;vertexB[v++]=r_aux*cos(y);
            normalB[n++]=0;normalB[n++]=1;normalB[n++]=0;
            texB[t++]=l_aux*texFactor_fatias;texB[t++]=1-texFactor_aneis;
            if(l_aux!=fatias){
                indices[i++]=l_aux;
                indices[i++]=avanco+l_aux;
                indices[i++]=avanco+l_aux+1;
            }
            y+=angulo;
        }
        avanco+=fatias+1;
        
        //Aneis da base
        for(j=1;j<aneis;j++){
            r_aux+=raio;
            y=0;
            for(l_aux=0;l_aux<=fatias;l_aux++){
                
                vertexB[v++]=r_aux*sin(y); vertexB[v++]=alt; vertexB[v++]=r_aux*cos(y);
                normalB[n++]=0;normalB[n++]=1;normalB[n++]=0;
                texB[t++]=l_aux*texFactor_fatias;texB[t++]=1-(j+1)*texFactor_aneis;
                
                if(l_aux!=fatias){
                    indices[i++]=avanco-(fatias+1)+l_aux;
                    indices[i++]=avanco+l_aux;
                    indices[i++]=avanco-(fatias+1)+l_aux+1;
                    
                    indices[i++]=avanco+l_aux;
                    indices[i++]=avanco+l_aux+1;
                    indices[i++]=avanco-(fatias+1)+l_aux+1;
                }
                
                y+=angulo;
            }
            avanco+=fatias+1;
        }
    }else{
        //Primeiro ponto central
        for (l_aux=0; l_aux<=fatias; l_aux++) {
            vertexB[v++]=0;vertexB[v++]=alt;vertexB[v++]=0;
            normalB[n++]=0;normalB[n++]=-1;normalB[n++]=0;
            texB[t++]=l_aux*texFactor_fatias;texB[t++]=1;
        }
        avanco+=fatias+1;
        
        //Primeiro circulo
        for(l_aux=0;l_aux<=fatias;l_aux++){
            
            vertexB[v++]=r_aux*sin(y);vertexB[v++]=alt;vertexB[v++]=r_aux*cos(y);
            normalB[n++]=0;normalB[n++]=-1;normalB[n++]=0;
            texB[t++]=l_aux*texFactor_fatias;texB[t++]=1-texFactor_aneis;
            if(l_aux!=fatias){
                indices[i++]=l_aux;
                indices[i++]=avanco+l_aux+1;
                indices[i++]=avanco+l_aux;
            }
            y+=angulo;
        }
        avanco+=fatias+1;
        
        //Aneis da base
        for(j=1;j<aneis;j++){
            r_aux+=raio;
            y=0;
            for(l_aux=0;l_aux<=fatias;l_aux++){
                
                vertexB[v++]=r_aux*sin(y); vertexB[v++]=alt; vertexB[v++]=r_aux*cos(y);
                normalB[n++]=0;normalB[n++]=-1;normalB[n++]=0;
                texB[t++]=l_aux*texFactor_fatias;texB[t++]=1-(j+1)*texFactor_aneis;
                
                if(l_aux!=fatias){
                    indices[i++]=avanco-(fatias+1)+l_aux;
                    indices[i++]=avanco-(fatias+1)+l_aux+1;
                    indices[i++]=avanco+l_aux;
                    
                    indices[i++]=avanco+l_aux;
                    indices[i++]=avanco-(fatias+1)+l_aux+1;
                    indices[i++]=avanco+l_aux+1;
                }
                
                y+=angulo;
            }
            avanco+=fatias+1;
        }
    }
    
    
    glGenBuffers(3, buffers);
    glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
    glBufferData(GL_ARRAY_BUFFER,n_pontos*sizeof(float), vertexB, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,buffers[1]);
    glBufferData(GL_ARRAY_BUFFER,n_pontos*sizeof(float), normalB, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,buffers[2]);
    glBufferData(GL_ARRAY_BUFFER,((2*n_pontos)/3)*sizeof(float), texB, GL_STATIC_DRAW);
    
        printf("%d||%d -- %d||%d -- %d\n",n_indices,i,n_pontos,v,fatias);
    
    free(vertexB);
    free(normalB);
    free(texB);
}

void Circulo::desenha(){
    
    glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
    glVertexPointer(3,GL_FLOAT,0,0);
    glBindBuffer(GL_ARRAY_BUFFER,buffers[1]);
    glNormalPointer(GL_FLOAT,0,0);
    glBindBuffer(GL_ARRAY_BUFFER,buffers[2]);
    glTexCoordPointer(2, GL_FLOAT, 0, 0);
    glDrawElements(GL_TRIANGLES, n_indices ,GL_UNSIGNED_INT, indices);

    
}







