//
//  cilindro.h
//  CG-FORMAS-PRIMARIAS
//
//  Created by Hélder José Alves Gonçalves on 27/02/14.
//  Copyright (c) 2014 Hélder José Alves Gonçalves. All rights reserved.
//

#ifndef CG_FORMAS_PRIMARIAS_cilindro_h
#define CG_FORMAS_PRIMARIAS_cilindro_h

#include <iostream>
#include <math.h>


void cilindro(float raio,int fatias, int camadas,float altura, int aneis, FILE* f);
void cilindroVBO(float raio,int fatias, int camadas,float altura, int aneis, FILE* f);



#endif