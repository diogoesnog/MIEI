//
//  camera.cpp
//  Motor3D
//
//  Created by Hélder José Alves Gonçalves on 14/03/14.
//  Copyright (c) 2014 Duarte Nuno Ferreira Duarte. All rights reserved.
//

#include "camera_explorador.h"


float raio=5,raioAux=0,angCam_h=0,angCam_v=0.5,angAux_h=0,angAux_v=0,x_tela,y_tela;
int estado_botao=0;


//Modo Explorador

void modo_explorador(){
    //Câmera em modo explorador
	gluLookAt((raio+raioAux)*sin(angCam_h+angAux_h)*cos(angCam_v+angAux_v),(raio+raioAux)*sin(angCam_v+angAux_v),(raio+raioAux)*cos(angCam_h+angAux_h)*cos(angCam_v+angAux_v),
	          0.0, 0.0, 0.0,
              0.0f, 1.0f, 0.0f);
}

//Funçoes para o Rato
void rato_explorador(int botao, int estado, int x, int y){
    if (botao==GLUT_LEFT_BUTTON){
        if (estado==GLUT_DOWN){
            estado_botao=1;
            x_tela=x;
            y_tela=y;
        }
        else{
            estado_botao=0;
            angCam_v+=angAux_v;
            angCam_h+=angAux_h;
            angAux_h=0;
            angAux_v=0;
        }
    }
}

void mov_rato_explorador(int x, int y){
    float teste;
    if(estado_botao==1){
        if(x_tela!=x)
            angAux_h= (x_tela-x)*0.007;
        
        if(y_tela!=y){
            teste= (y-y_tela)*0.007;
            if(teste+angCam_v>-M_PI_2 && teste+angCam_v<M_PI_2 )
                angAux_v=teste;
        }
        glutPostRedisplay();
    }
}

//Funçoes para o Rato
void teclado_normal_explorador(unsigned char tecla,int x, int y){
    switch (tecla) {
        case 'a':
            raio-=0.1;
            break;
        case 'd':
            raio+=0.1;
            break;
            
        default:
            break;
    }
    glutPostRedisplay();
}

void teclado_especial_explorador(int tecla,int x, int y){
    switch (tecla) {
        case GLUT_KEY_UP:
            if(angCam_v+0.05<M_PI_2)   //Para câmera não virar ao contrário
                angCam_v+=0.05;
            break;
        case GLUT_KEY_DOWN:
            if(angCam_v-0.05>-M_PI_2)  //Para câmera não virar ao contrário
                angCam_v-=0.05;
            break;
            
        case GLUT_KEY_LEFT:
            angCam_h-=0.05;
            break;
        case GLUT_KEY_RIGHT:
            angCam_h+=0.05;
            break;
            
        default:
            break;
    }
    glutPostRedisplay();
}
