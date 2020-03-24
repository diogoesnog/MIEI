//
//  main.cpp
//  Motor3D
//
//  Created by Duarte Nuno Ferreira Duarte on 10/03/14.
//  Copyright (c) 2014 Duarte Nuno Ferreira Duarte. All rights reserved.
//


#include "motorXML.h"
#include "camera_explorador.h"
#include "camera_fps.h"
#include "luzes.h"

//#include <freeglut.h>

//Inicializaçoes Principais
TiXmlNode *cena=NULL;
int tipo_camera=0;
//char* print_ecra="";

Rotacao *rotacoes=NULL, *rot_actual=NULL;
Translacao *translacoes=NULL, *tra_actual=NULL;
Escala escalas=NULL, esc_actual=NULL;
PropModel l_PropModel=NULL, prop_actual=NULL;
long currentTime=0,test;

//Numero de modelos desenhados
int n_desenhos=0, total_desenhos=0, enableViewFrustum=0, caixasDesenho=0;
char print[20]="";

void changeSize(int w, int h){
    
	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if (h == 0)
		h = 1;
    
	// compute window's aspect ratio
	float ratio = w * 1.0 / h;
    
	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
    
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
    
	// Set perspective
	gluPerspective(45.0f, ratio, 1.0f, 1000.0f);
    
	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void renderScene(void) {
    
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	// set the camera
	glLoadIdentity();
	
    //Vê o glutAt a usar
    if (tipo_camera==1)
        modo_explorador();
    else
        if (tipo_camera==2)
            modo_fps();
        else{
            gluLookAt(0,3,5,
                      0.0, 0.0, 0.0,
                      0.0f, 1.0f, 0.0f);
        }
    
	// pÙr instruÁıes de desenho aqui

    //LUZES
    defineLuzes();
    
    //Actualiza apontadores
	rot_actual=rotacoes;
    tra_actual=translacoes;
    esc_actual=escalas;
    prop_actual=l_PropModel;
    
    n_desenhos=0;
    
    //Actualiza do tempo
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    motor_XML(cena);
    
    //Alterar titulo da janela a cada frame
    sprintf(print, "Galaxy 3D ® => %d/%d desenhados\n",n_desenhos, total_desenhos);
    glutSetWindowTitle(print);
    
    // End of frame
	glutSwapBuffers();
}


void front_menu(int op){
    switch (op) {
        case 1:
            glPolygonMode(GL_FRONT,GL_POINT);
            break;
        case 2:
            glPolygonMode(GL_FRONT,GL_LINE);
            break;
        case 3:
            glPolygonMode(GL_FRONT,GL_FILL);
            break;
        case 4:
            glutKeyboardFunc(teclado_normal_explorador);
            glutSpecialFunc(teclado_especial_explorador);
            glutMouseFunc(rato_explorador);
            glutMotionFunc(mov_rato_explorador);
            tipo_camera=1;
            break;
        case 5:
            glutKeyboardFunc(teclado_normal_fps);
            glutSpecialFunc(teclado_especial_fps);
            glutMouseFunc(rato_fps);
            glutMotionFunc(mov_rato_fps);
            tipo_camera=2;
            break;
        case 6:
             glEnable(GL_LIGHTING);
            break;
        case 7:
            glDisable(GL_LIGHTING);
            break;
        case 8:
            glEnable(GL_TEXTURE_2D);
            break;
        case 9:
            glDisable(GL_TEXTURE_2D);
            break;
        case 10:
            enableViewFrustum=0;
            break;
        case 11:
            enableViewFrustum=1;
            break;
        case 12:
            caixasDesenho=1;
            break;
        case 13:
            caixasDesenho=0;
            break;

        default:
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char* argv[]){
    
    TiXmlDocument doc;
    TiXmlElement *root=NULL;
    TiXmlNode *node=NULL;
    TiXmlAttribute *attr=NULL;
    const char *tag=NULL;
    int M_Visual, M_Camera, M_Luzes, M_Texturas, M_ViewFrustum;
    
    
   
    if(argc!=2){
        printf("ERRO!! Número de argumentos errado, falta XML de input!\n");
        return 1;
    }
    
	if(doc.LoadFile(argv[1])){
    //if(doc.LoadFile("sistema_solar.xml")){
        
        root=doc.RootElement();
        cena=root->FirstChild("cena");
        
        if (cena) {
            
            // inicializaÁ„o
            glutInit(&argc, argv);
            glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
            glutInitWindowPosition(100, 100);
            glutInitWindowSize(1100, 800);
            glutCreateWindow("Galaxy 3D ®");
            
            
            // pÙr registo de funÁıes aqui
            glutDisplayFunc(renderScene);
            glutReshapeFunc(changeSize);
            glutIdleFunc(renderScene);
            
            // funções do teclado e rato
            if((node=root->FirstChild("cameras"))){
                for (node=node->FirstChild(); node; node=node->NextSibling()) {
                    tag=node->Value();
                    if(strcmp("camera", tag)==0 && (attr=node->ToElement()->FirstAttribute())){
                        if (strcmp(attr->Name(), "tipo")==0) {
                            if(strcmp(attr->Value(), "fps")==0){
                                preDefinicoes_FPS(node);
                                glutKeyboardFunc(teclado_normal_fps);
                                glutSpecialFunc(teclado_especial_fps);
                                glutMouseFunc(rato_fps);
                                glutMotionFunc(mov_rato_fps);
                                tipo_camera=2;
                            }else
                                if (strcmp(attr->Value(), "explorador")==0){
                                    preDefinicoes_Explorador(node);
                                    glutKeyboardFunc(teclado_normal_explorador);
                                    glutSpecialFunc(teclado_especial_explorador);
                                    glutMouseFunc(rato_explorador);
                                    glutMotionFunc(mov_rato_explorador);
                                    tipo_camera=1;
                                }
                        }
                    }

                }
            }else{
                //Caso não esteja definida nenhuma camera, o modo explorador fica activo por defeito
                glutKeyboardFunc(teclado_normal_explorador);
                glutSpecialFunc(teclado_especial_explorador);
                glutMouseFunc(rato_explorador);
                glutMotionFunc(mov_rato_explorador);
                tipo_camera=1;
            }
            
            //Luzes
            if((node=root->FirstChild("luzes"))){
                glEnable(GL_LIGHTING);
                preparaLuzes(node);
            }
            
            
            //MENU
            M_Visual=glutCreateMenu(front_menu);
            glutAddMenuEntry("GL POINT",1);
            glutAddMenuEntry("GL LINE",2);
            glutAddMenuEntry("GL FILL",3);
            
            M_Camera=glutCreateMenu(front_menu);
            glutAddMenuEntry("Modo Explorador",4);
            glutAddMenuEntry("Modo FPS",5);
            
            M_Luzes=glutCreateMenu(front_menu);
            glutAddMenuEntry("Ligar",6);
            glutAddMenuEntry("Desligar",7);
            
            M_Texturas=glutCreateMenu(front_menu);
            glutAddMenuEntry("Ligar",8);
            glutAddMenuEntry("Desligar",9);
            
            M_ViewFrustum=glutCreateMenu(front_menu);
            glutAddMenuEntry("Ligar",10);
            glutAddMenuEntry("Desligar",11);
            glutAddMenuEntry("Desenhar Limites",12);
            glutAddMenuEntry("Não Desenhar Limites",13);
            
            glutCreateMenu(front_menu);
            glutAddSubMenu("Visualização",M_Visual);
            glutAddSubMenu("Camera",M_Camera);
            glutAddSubMenu("Luz",M_Luzes);
            glutAddSubMenu("Texturas",M_Texturas);
            glutAddSubMenu("ViewFrustumCulling",M_ViewFrustum);
            
            //Activar pop-up Menus  <<<<---------<<<<------<<<<---------<<<<------
            glutAttachMenu(GLUT_RIGHT_BUTTON);
            
            //Callback do GLEW - Tem de estar depois de todos os callbacks do GLUT
            glewInit();
            ilInit();
            
            //Activar Buffers
            glEnableClientState(GL_VERTEX_ARRAY);
            glEnableClientState(GL_NORMAL_ARRAY);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            
            // alguns settings para OpenGL
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);
            glEnable(GL_TEXTURE_2D);
            glClearColor(0.0f,0.0f,0.0f,0.0f);
            
            
            //Carregar todas as estruturas para correr o Motor3D e prepara o Picking
            prepara_MotorXML(cena);
            initPickingCena(cena);

            // entrar no ciclo do GLUT
            glutMainLoop();
            
        }
        else
            printf("Falhou!! Sem tag 'cena' no XML!\n");
    }
    else
        printf("Falhou!! Não fez load do ficheiro!\n");
    
	return 0;
}



