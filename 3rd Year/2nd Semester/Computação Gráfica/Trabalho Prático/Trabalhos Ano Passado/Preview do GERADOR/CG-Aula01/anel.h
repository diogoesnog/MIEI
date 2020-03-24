//
//  anel.h
//  CG-TESTES
//
//  Created by Hélder José Alves Gonçalves on 07/04/14.
//  Copyright (c) 2014 Hélder José Alves Gonçalves. All rights reserved.
//

#ifndef __CG_TESTES__anel__
#define __CG_TESTES__anel__


#include <GL/glew.h>
#include <GLUT/glut.h>
#include <iostream>
#include <math.h>

void anel(float raio_fora, float raio_dentro, int fatias, int aneis, int ori);

class Anel{
public:
    Anel(float raio_fora, float raio_dentro, int fatias, int aneis, int ori);
    void desenha();
    
protected:
    GLuint buffers[3];
    short n_indices;
    unsigned int *indices;
};


#endif /* defined(__CG_TESTES__anel__) */
