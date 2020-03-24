//
//  modelo.h
//  Motor3D
//
//  Created by Hélder José Alves Gonçalves on 09/04/14.
//  Copyright (c) 2014 Duarte Nuno Ferreira Duarte. All rights reserved.
//

#ifndef __Motor3D__modelo__
#define __Motor3D__modelo__

#include <iostream>



typedef struct smodelo{
    
    const char* nome;
    float* vertices;
    int n_pontos;
    struct smodelo *next;
    
}*Modelo, NModelo;


Modelo addModelo(const char* nome, float *vertices, int n_pontos, Modelo lista);
Modelo search_Modelo(const char* nome, Modelo lista);


#endif /* defined(__Motor3D__modelo__) */
