//
//  escala.h
//  Motor3D
//
//  Created by Hélder José Alves Gonçalves on 08/05/14.
//  Copyright (c) 2014 Duarte Nuno Ferreira Duarte. All rights reserved.
//

#ifndef __Motor3D__escala__
#define __Motor3D__escala__

#include <iostream>
#include <GLUT/glut.h>

typedef struct sEscala{
    float x;
    float y;
    float z;
    struct sEscala *next;
}*Escala, NEscala;

Escala insereEscala(float x, float y, float z, Escala escalas);
Escala do_escala(Escala escala);

#endif /* defined(__Motor3D__escala__) */
