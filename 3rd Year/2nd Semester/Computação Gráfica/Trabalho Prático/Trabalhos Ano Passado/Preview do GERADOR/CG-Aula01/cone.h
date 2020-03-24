//
//  cone.h
//  CG-FORMAS-PRIMARIAS
//
//  Created by Hélder José Alves Gonçalves on 10/03/14.
//  Copyright (c) 2014 Hélder José Alves Gonçalves. All rights reserved.
//

#ifndef CG_FORMAS_PRIMARIAS_cone_h
#define CG_FORMAS_PRIMARIAS_cone_h

#include "circulo.h"

void cone(float raio_base, float altura, int lados, int sep_circulo, int sep_h);


class Cone{
public:
    Cone(float raio_base, float altura, int fatias, int aneis, int camadas);
    void desenha();
    
protected:
    GLuint buffers[3];
    short n_indices;
    unsigned short *indices;
};
#endif
