//
//  escala.cpp
//  Motor3D
//
//  Created by Hélder José Alves Gonçalves on 08/05/14.
//  Copyright (c) 2014 Duarte Nuno Ferreira Duarte. All rights reserved.
//

#include "escala.h"

Escala insereEscala(float x, float y, float z, Escala escalas){
    Escala aux=NULL, aux2=escalas;
    
    aux=(Escala)malloc(sizeof(NEscala));
    aux->x=x;
    aux->y=y;
    aux->z=z;
    aux->next=NULL;
    
    if(!escalas)
        return aux;
    while (escalas->next)
        escalas=escalas->next;
    escalas->next=aux;
    
    return aux2;
}


Escala do_escala(Escala escala){
    
    glScalef(escala->x, escala->y, escala->z);
    return escala->next;
    
}