//
//  material.h
//  Motor3D
//
//  Created by Hélder José Alves Gonçalves on 27/05/14.
//  Copyright (c) 2014 Duarte Nuno Ferreira Duarte. All rights reserved.
//

#ifndef __Motor3D__material__
#define __Motor3D__material__

#include <iostream>
#include <GLUT/glut.h>
#include "tinyxml/tinyxml.h"


typedef struct sMaterial{
    
    int tipo;
    float cor[3];
    struct sMaterial *next;
    
}*Material,NMaterial;


Material preparaMaterial(TiXmlNode *root);
void do_Materiais(Material lista);
void do_MattNeutro(Material lista);

#endif /* defined(__Motor3D__material__) */
