//
//  modelo.cpp
//  Motor3D
//
//  Created by Hélder José Alves Gonçalves on 09/04/14.
//  Copyright (c) 2014 Duarte Nuno Ferreira Duarte. All rights reserved.
//

#include "modelo.h"


Modelo addModelo(const char* nome, float *vertices, int n_pontos, Modelo lista){
    
    Modelo novo =(Modelo)malloc(sizeof(NModelo));
    novo->nome=nome;
    novo->vertices=vertices;
    novo->n_pontos=n_pontos;
    
    if (lista) {
        novo->next=lista;
        return novo;
    }
    novo->next=NULL;
    return novo;
}


Modelo search_Modelo(const char* nome, Modelo lista){
    
    while (lista) {
        if (strcmp(nome, lista->nome)==0)
            return lista;
        lista=lista->next;
    }
    return NULL;
}