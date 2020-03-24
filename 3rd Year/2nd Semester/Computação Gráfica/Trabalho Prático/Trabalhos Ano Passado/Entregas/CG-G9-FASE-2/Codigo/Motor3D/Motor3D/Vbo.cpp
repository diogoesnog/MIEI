//
//  Vbo.cpp
//  Motor3D
//
//  Created by Hélder José Alves Gonçalves on 09/04/14.
//  Copyright (c) 2014 Duarte Nuno Ferreira Duarte. All rights reserved.
//

#include "Vbo.h"

Vbo addVbo(const char* nome, GLuint *buffers, unsigned short n_indices, unsigned short *indices, Vbo lista){
 
    Vbo novo=(Vbo)malloc(sizeof(NVbo));
    novo->nome=nome;
    novo->n_indices=n_indices;
    novo->indices=indices;
    novo->buffers=buffers;
    
    if (lista) {
        novo->next=lista;
        return novo;
    }
    novo->next=NULL;
    return novo;
}


Vbo search_Vbo(const char* nome, Vbo lista){
    
    while (lista) {
        if (strcmp(nome, lista->nome)==0)
            return lista;
        lista=lista->next;
    }
    return NULL;
}

