//
//  rotacoes.cpp
//  Motor3D
//
//  Created by Duarte Nuno Ferreira Duarte on 26/04/14.
//  Copyright (c) 2014 Duarte Nuno Ferreira Duarte. All rights reserved.
//

#include "rotacoes.h"

Rotacao *insereRotacao(float periodo, float angulo, float x, float y, float z, Rotacao *rotacoes){
    Rotacao *aux=NULL, *aux2=rotacoes;
    
    aux=(Rotacao*)malloc(sizeof(Rotacao));
    aux->x = x;
    aux->y = y;
    aux->z = z;
    if(periodo==0){
        aux->angulo=angulo;
        aux->periodo=0;
    }
    else{
        aux->periodo = periodo*1000;
        aux->angulo=0;
    }
    aux->next=NULL;
    
    if(!rotacoes)
        return aux;
    
    while(rotacoes->next)
        rotacoes=rotacoes->next;
    rotacoes->next = aux;
    return aux2;
}

Rotacao* do_rotacao(Rotacao* rot,long currentTime){
    if(rot->periodo!=0)
        glRotatef(360*(currentTime%rot->periodo)/rot->periodo, rot->x, rot->y, rot->z);
    else
        glRotatef(rot->angulo, rot->x, rot->y, rot->z);
    
    return rot->next;
}
