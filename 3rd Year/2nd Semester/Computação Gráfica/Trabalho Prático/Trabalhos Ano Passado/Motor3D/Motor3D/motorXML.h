//
//  motor.h
//  Motor3D
//
//  Created by Hélder José Alves Gonçalves on 12/03/14.
//  Copyright (c) 2014 Duarte Nuno Ferreira Duarte. All rights reserved.
//

#ifndef Motor3D_motorXML_h
#define Motor3D_motorXML_h


#include <glew.h>
#include <il.h>

#include <iostream>
#include <string>
#include <regex>
#include "tinyxml/tinyxml.h"
#include "modelo.h"
#include "catmull.h"
#include "rotacoes.h"
#include "escala.h"


extern Picking *pickings;
extern Rotacao *rotacoes, *rot_actual;
extern Translacao *translacoes, *tra_actual;
extern Escala escalas, esc_actual;
extern PropModel l_PropModel, prop_actual;
extern long currentTime;
extern int tipo_camera;
extern int n_desenhos, total_desenhos,enableViewFrustum,caixasDesenho;
extern char* print_ecra;
void motor_XML(TiXmlNode *doc);
void prepara_MotorXML(TiXmlNode* root);

#endif
