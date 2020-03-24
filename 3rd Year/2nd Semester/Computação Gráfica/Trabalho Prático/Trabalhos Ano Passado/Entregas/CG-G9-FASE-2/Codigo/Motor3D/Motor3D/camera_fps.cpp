//
//  camera_fps.cpp
//  Motor3D
//
//  Created by Hélder José Alves Gonçalves on 14/03/14.
//  Copyright (c) 2014 Duarte Nuno Ferreira Duarte. All rights reserved.
//

#include "camera_fps.h"

float px=0,py=2,pz=5, angCamFPS_h=M_PI, angCamFPS_v=-0.2, x_telaFPS,y_telaFPS;

void modo_fps(){
    
    //Câmera em modo explorador
	gluLookAt(px,py,pz,
	          px+sin(angCamFPS_h)*cos(angCamFPS_v), py+sin(angCamFPS_v), pz+cos(angCamFPS_h)*cos(angCamFPS_v),
              0.0f, 1.0f, 0.0f);

    
}


void mov_rato_fps(int x, int y){
    float teste;
    
    if(x_telaFPS!=x){
        angCamFPS_h+= (x_telaFPS-x)*0.002;
        x_telaFPS=x;
    }
    
    if(y_telaFPS!=y){
        teste= (y-y_telaFPS)*0.002;
        if(teste+angCamFPS_v>-M_PI_2 && teste+angCamFPS_v<M_PI_2 ){
            angCamFPS_v-=teste;
            y_telaFPS=y;
        }
    }
    glutPostRedisplay();

}

void rato_fps(int botao, int estado, int x, int y){
    if (botao==GLUT_LEFT_BUTTON)
        if (estado==GLUT_DOWN){
            x_telaFPS=x;
            y_telaFPS=y;
        }
        
}


void teclado_especial_fps(int tecla,int x, int y){
    switch (tecla) {
        case GLUT_KEY_UP:
            if(angCamFPS_v+0.05<M_PI_2)   //Para câmera não virar ao contrário
                angCamFPS_v+=0.05;
            break;
        case GLUT_KEY_DOWN:
           if(angCamFPS_v-0.05>-M_PI_2)  //Para câmera não virar ao contrário
                angCamFPS_v-=0.05;
            break;
            
        case GLUT_KEY_LEFT:
            angCamFPS_h+=0.05;
            break;
        case GLUT_KEY_RIGHT:
            angCamFPS_h-=0.05;
            break;
            
        default:
            break;
    }
    glutPostRedisplay();
}

void teclado_normal_fps(unsigned char tecla,int x, int y){
    switch (tecla) {
        case 'd':
            px+=0.7*sin(angCamFPS_h-M_PI_2);
            pz+=0.7*cos(angCamFPS_h-M_PI_2);
            break;
        case 'a':
            px+=0.7*sin(angCamFPS_h+M_PI_2);
            pz+=0.7*cos(angCamFPS_h+M_PI_2);
            break;
        case 'w':
            px+=0.7*sin(angCamFPS_h);
            pz+=0.7*cos(angCamFPS_h);
            break;
        case 's':
            px-=0.7*sin(angCamFPS_h);
            pz-=0.7*cos(angCamFPS_h);
            break;
        
            
        default:
            break;
    }
    glutPostRedisplay();

}