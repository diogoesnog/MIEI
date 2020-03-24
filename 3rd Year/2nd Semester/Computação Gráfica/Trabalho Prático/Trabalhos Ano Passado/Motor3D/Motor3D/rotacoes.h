//
//  rotacoes.h
//  Motor3D
//
//  Created by Duarte Nuno Ferreira Duarte on 26/04/14.
//  Copyright (c) 2014 Duarte Nuno Ferreira Duarte. All rights reserved.
//

#ifndef __Motor3D__rotacoes__
#define __Motor3D__rotacoes__

#include <iostream>
#include <GLUT/glut.h>

typedef struct sRotacao{
    int  periodo;
    float angulo;
    float x;
    float y;
    float z;
    struct sRotacao *next;
}Rotacao;

Rotacao *insereRotacao(float periodo, float angulo, float x, float y, float z, Rotacao *rotacoes);
Rotacao* do_rotacao(Rotacao* rot,long currentTime);

#endif /* defined(__Motor3D__rotacoes__) */
