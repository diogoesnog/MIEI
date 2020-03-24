//
//  Vbo.h
//  Motor3D
//
//  Created by Hélder José Alves Gonçalves on 09/04/14.
//  Copyright (c) 2014 Duarte Nuno Ferreira Duarte. All rights reserved.
//

#ifndef __Motor3D__Vbo__
#define __Motor3D__Vbo__

#include <iostream>
#include <GLUT/glut.h>

//Estrutura para guardar uma VBO
typedef struct sVbo{
    const char* nome;
    GLuint *buffers;
    unsigned short *indices;
    unsigned short n_indices;
    struct sVbo *next;
    
}*Vbo, NVbo;

#endif /* defined(__Motor3D__Vbo__) */
