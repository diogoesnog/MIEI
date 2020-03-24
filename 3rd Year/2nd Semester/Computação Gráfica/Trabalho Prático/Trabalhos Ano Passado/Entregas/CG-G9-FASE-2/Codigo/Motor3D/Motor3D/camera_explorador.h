//
//  camera_explorador.h
//  Motor3D
//
//  Created by Hélder José Alves Gonçalves on 14/03/14.
//  Copyright (c) 2014 Duarte Nuno Ferreira Duarte. All rights reserved.
//

#ifndef Motor3D_camera_h
#define Motor3D_camera_h

#include <math.h>
#include <GLUT/glut.h>
#include "tinyxml/tinyxml.h"



void modo_explorador();
void preDefinicoes_Explorador(TiXmlNode *doc);
void rato_explorador(int botao, int estado, int x, int y);
void mov_rato_explorador(int x, int y);
void teclado_normal_explorador(unsigned char tecla,int x, int y);
void teclado_especial_explorador(int tecla,int x, int y);


#endif
