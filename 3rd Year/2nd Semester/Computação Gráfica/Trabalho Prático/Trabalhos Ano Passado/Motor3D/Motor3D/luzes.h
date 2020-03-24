//
//  luzes.h
//  Motor3D
//
//  Created by Hélder José Alves Gonçalves on 26/05/14.
//  Copyright (c) 2014 Duarte Nuno Ferreira Duarte. All rights reserved.
//

#ifndef __Motor3D__luzes__
#define __Motor3D__luzes__

#include <iostream>
#include <GLUT/glut.h>
#include "tinyxml/tinyxml.h"


typedef struct sluz{
    int luz;
    int tipo;
    float propriedade[4];
    struct sluz *next;
    
}*Luz, NLuz;



void preparaLuzes(TiXmlNode* root);
void defineLuzes();

#endif /* defined(__Motor3D__luzes__) */