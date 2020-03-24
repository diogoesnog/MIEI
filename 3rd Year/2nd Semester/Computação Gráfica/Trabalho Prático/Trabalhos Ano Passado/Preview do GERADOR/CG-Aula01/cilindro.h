//
//  cilindro.h
//  CG-FORMAS-PRIMARIAS
//
//  Created by Hélder José Alves Gonçalves on 27/02/14.
//  Copyright (c) 2014 Hélder José Alves Gonçalves. All rights reserved.
//

#ifndef CG_FORMAS_PRIMARIAS_cilindro_h
#define CG_FORMAS_PRIMARIAS_cilindro_h

#include "circulo.h"

void cilindro(float raio,int lados,float alt,int sep_cir,int sep_h);

class Cilindro{
public:
    Cilindro(float raio,int fatias,float altura,int aneis,int camadas);
    void desenha();
    
protected:
    GLuint buffers[3];
    int n_indices;
    unsigned short *indices;
};

#endif
