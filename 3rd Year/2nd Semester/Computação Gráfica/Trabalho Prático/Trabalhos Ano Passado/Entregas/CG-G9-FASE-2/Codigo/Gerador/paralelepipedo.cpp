//
//  paralelepipedo.cpp
//  CG-FORMAS-PRIMARIAS
//
//  Created by Hélder José Alves Gonçalves on 10/03/14.
//  Copyright (c) 2014 Hélder José Alves Gonçalves. All rights reserved.
//

#include "paralelepipedo.h"


void paralelepipedo(float altura, float lado_x, float lado_z, int camadas, int fatias, FILE* f){
    
	int flag=0;

	fprintf(f,"%d\n",2*camadas*fatias*6*9);

    plano(altura, lado_x, camadas, fatias, lado_z/2, 1,f, flag);
    plano(altura, lado_x, camadas, fatias, -lado_z/2, 2,f, flag);
    
    plano(altura, lado_z, camadas, fatias, lado_x/2, 3,f, flag);
    plano(altura, lado_z, camadas, fatias, -lado_x/2, 4,f, flag);
    
    plano(lado_x, lado_z, camadas, fatias, altura/2, 5,f, flag);
    plano(lado_x, lado_z, camadas, fatias, -altura/2, 6,f, flag);
}