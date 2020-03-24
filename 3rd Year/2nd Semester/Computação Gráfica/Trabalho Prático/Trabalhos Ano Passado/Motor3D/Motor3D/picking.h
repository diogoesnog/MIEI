//
//  picking.h
//  Motor3D
//
//  Created by Hélder José Alves Gonçalves on 29/05/14.
//  Copyright (c) 2014 Duarte Nuno Ferreira Duarte. All rights reserved.
//

#ifndef __Motor3D__picking__
#define __Motor3D__picking__

#include "motorXML.h"
#include "camera_explorador.h"
#include "camera_fps.h"
#include <unistd.h>


void do_Picking(int xx, int yy);
void initPickingCena(TiXmlNode *cena);
void motor_Picking(TiXmlNode *root);

#endif /* defined(__Motor3D__picking__) */
