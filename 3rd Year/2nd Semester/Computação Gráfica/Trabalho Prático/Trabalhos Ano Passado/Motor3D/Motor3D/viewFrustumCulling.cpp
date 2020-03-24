//
//  viewFrustumCulling.cpp
//  Motor3D
//
//  Created by Hélder José Alves Gonçalves on 28/05/14.
//  Copyright (c) 2014 Duarte Nuno Ferreira Duarte. All rights reserved.
//

#include "viewFrustumCulling.h"

float M[16],P[16],A[16];

//Função que testa um ponto no clipSpace
int testaPonto(float x, float y, float z){
    float lx, ly, lz, lw, w=1;
    
    lx= A[0]*x + A[4]*y + A[8]*z + A[12]*w;
    ly= A[1]*x + A[5]*y + A[9]*z + A[13]*w;
    lz= A[2]*x + A[6]*y + A[10]*z + A[14]*w;
    lw= A[3]*x + A[7]*y + A[11]*z + A[15]*w;
    
    if ( lx<-lw || lx>lw)
        return OUT;
    if ( ly<-lw || ly>lw)
        return OUT;
    if ( lz<-lw || lz>lw)
        return OUT;
    
    return INSIDE;
}


int testaSOLID(float maxX, float minX, float maxY, float minY, float maxZ, float minZ){
    
    //Testa os 8 pontos da caixa
    if(testaPonto(maxX, maxY, maxZ)==INSIDE)
        return INSIDE;
    
    if(testaPonto(minX, maxY, maxZ)==INSIDE)
        return INSIDE;
    
    if(testaPonto(maxX, minY, maxZ)==INSIDE)
        return INSIDE;
    
    if(testaPonto(minX, minY, maxZ)==INSIDE)
        return INSIDE;
    
    if(testaPonto(maxX, maxY, minZ)==INSIDE)
        return INSIDE;
    
    if(testaPonto(minX, maxY, minZ)==INSIDE)
        return INSIDE;
    
    if(testaPonto(maxX, minY, minZ)==INSIDE)
        return INSIDE;
    
    if(testaPonto(minX, minY, minZ)==INSIDE)
        return INSIDE;
    
    return OUT;
}


//Função adaptada para varios tipos de formatos de caixa (caixa, esfera, etc)
int testaModelo(ViewFrustum vfc){
    glGetFloatv(GL_MODELVIEW_MATRIX,M);
    glGetFloatv(GL_PROJECTION_MATRIX,P);
    
    
    //Push para guardar matriz original
    glPushMatrix();
    
    //Carregar a matriz P e multiplicar pela matriz M
    glLoadMatrixf(P);
    glMultMatrixf(M);
    
    //Obter a matriz A e POP para a matriz original
    glGetFloatv(GL_MODELVIEW_MATRIX, A);
    glPopMatrix();
    
    //Neste caso só testamos um tipo, mas podia haver mais, fazendo um 'if' no tipo de caixa
    if (testaSOLID(vfc->maxX,vfc->minX,vfc->maxY,vfc->minY,vfc->maxZ,vfc->minZ)==OUT)
        return OUT;

    
    
    return INSIDE;
}




void desenhaCaixa(ViewFrustum view){
    
    if(view){
        //Para ver caixas utilizadas no viewfruntum
        glBegin(GL_LINE_LOOP);
        glVertex3f(view->maxX, view->maxY, view->maxZ);
        glVertex3f(view->maxX, view->minY, view->maxZ);
        glVertex3f(view->minX, view->minY, view->maxZ);
        glVertex3f(view->minX, view->maxY, view->maxZ);
        glEnd();
        
        glBegin(GL_LINE_LOOP);
        glVertex3f(view->maxX, view->maxY, view->minZ);
        glVertex3f(view->maxX, view->minY, view->minZ);
        glVertex3f(view->minX, view->minY, view->minZ);
        glVertex3f(view->minX, view->maxY, view->minZ);
        glEnd();
        
        glBegin(GL_LINE_STRIP);
        glVertex3f(view->maxX, view->maxY, view->maxZ);
        glVertex3f(view->maxX, view->maxY, view->minZ);
        glEnd();
        
        glBegin(GL_LINE_STRIP);
        glVertex3f(view->minX, view->maxY, view->maxZ);
        glVertex3f(view->minX, view->maxY, view->minZ);
        glEnd();
        
        glBegin(GL_LINE_STRIP);
        glVertex3f(view->maxX, view->minY, view->maxZ);
        glVertex3f(view->maxX, view->minY, view->minZ);
        glEnd();
        
        glBegin(GL_LINE_STRIP);
        glVertex3f(view->minX, view->minY, view->maxZ);
        glVertex3f(view->minX, view->minY, view->minZ);
        glEnd();

    }
}
