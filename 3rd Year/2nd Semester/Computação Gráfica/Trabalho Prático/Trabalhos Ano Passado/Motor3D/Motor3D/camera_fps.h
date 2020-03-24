//
//  camera_fps.h
//  Motor3D
//
//  Created by Hélder José Alves Gonçalves on 14/03/14.
//  Copyright (c) 2014 Duarte Nuno Ferreira Duarte. All rights reserved.
//

#ifndef Motor3D_camera_fps_h
#define Motor3D_camera_fps_h


#include "picking.h"


//Modo FPS
void modo_fps();
void preDefinicoes_FPS(TiXmlNode *node);
void teclado_especial_fps(int tecla,int x, int y);
void teclado_normal_fps(unsigned char tecla,int x, int y);
void mov_rato_fps(int x, int y);
void rato_fps(int botao, int estado, int x, int y);

#endif
