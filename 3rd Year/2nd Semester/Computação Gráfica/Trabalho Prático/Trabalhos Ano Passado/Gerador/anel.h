//
//  anel.h
//  CG-FORMAS-PRIMARIAS
//
//  Created by Hélder José Alves Gonçalves on 24/04/14.
//  Copyright (c) 2014 Hélder José Alves Gonçalves. All rights reserved.
//

#ifndef CG_FORMAS_PRIMARIAS_anel_h
#define CG_FORMAS_PRIMARIAS_anel_h

#include <iostream>
#include <math.h>

//ORI --- 1 -> BASE && 0 -> TOPO
void anel(float raio_fora, float raio_dentro,int fatias, int aneis, int ori, FILE* f);
void anelVBO(float raio_fora, float raio_dentro, int fatias, int aneis, int ori, FILE* f);


#endif