//
//  catmull.h
//  Motor3D
//
//  Created by Duarte Nuno Ferreira Duarte on 23/04/14.
//  Copyright (c) 2014 Duarte Nuno Ferreira Duarte. All rights reserved.
//

#ifndef __Motor3D__catmull__
#define __Motor3D__catmull__

#include <iostream>
#include "tinyxml/tinyxml.h"
#include <math.h>
#include <GLUT/GLUT.h>

typedef struct point {
    float coords[3] = {0.0f, 0.0f,0.0f};
    struct point *next=NULL;
} Point;

typedef struct translacao{
    GLuint buffer[1];
    short n_indices;
    float res[3];
    int point_count;
    Point *points;
    float tempo;
    float a;
    float lastTime;
    float pX;
    float pY;
    float pZ;
    struct translacao *next;
}Translacao;

int lerPontos(TiXmlNode* root, Point **res);
Translacao* insereTranslacao(Point *listaPontos, Translacao *translacoes, int numeroPontos, float tempo, float x, float y, float z);
Translacao* do_translacao(Translacao* rot, long currentTime);
void getCatmullRomPointDERIVADA(float t, int *indices, float *res, Point *points);

#endif /* defined(__Motor3D__catmull__) */

