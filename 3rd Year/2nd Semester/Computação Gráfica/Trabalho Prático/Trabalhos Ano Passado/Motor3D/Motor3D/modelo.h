//
//  modelo.h
//  Motor3D
//
//  Created by Hélder José Alves Gonçalves on 09/04/14.
//  Copyright (c) 2014 Duarte Nuno Ferreira Duarte. All rights reserved.
//

#ifndef __Motor3D__modelo__
#define __Motor3D__modelo__

#include "material.h"
#include "viewFrustumCulling.h"


//Estrutura para as VBO -> '.vbo'
typedef struct sVbo{
    const char* nome;
    GLuint *buffers;
    unsigned short *indices;
    int n_indices;
    
}*Vbo, NVbo;

//Estrutura para os modelos -> '.3d'
typedef struct sr_time{
    
    const char* nome;
    float* vertices;
    int n_pontos;
    
}*RTime, NRTime;


typedef struct smodelo{
    
    ViewFrustum pontos;
    short tipo;
    union{
        Vbo vbo;
        RTime rTime;
    }u;
    struct smodelo *next;
    
}*Modelo, NModelo;

typedef struct sPicking{
    
    int cor;
    const char *descricao;
    const char *titulo;
    int desenha;
    long pressTime;
    
}*Picking, NPicking;

typedef struct sPropModel{
    Modelo modelo;
    Material materiais;
    unsigned int texID;
    Picking picking;
    
    struct sPropModel *next;
    
}*PropModel, NPropModel;



PropModel initPropModel();
PropModel addPropModel(PropModel novo, PropModel lista);
Modelo addRTime(const char* nome, float *vertices, int n_pontos, Modelo lista);
Modelo addVbo(const char* nome, GLuint *buffers, int n_indices, unsigned short *indices, Modelo lista);
Modelo ler_RTime(const char* filename, Modelo lista);
Modelo ler_VBO(const char* filename, Modelo lista);
Modelo search_Modelo(const char* nome, Modelo lista);
void desenha_vbo(Vbo vbo, unsigned int texID);
void desenha_RTime(RTime modelo);
void do_Picking(Picking pick,ViewFrustum viewFC, long time);
Picking preparaPicking(TiXmlNode *root);


#endif /* defined(__Motor3D__modelo__) */
