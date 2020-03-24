//
//  picking.cpp
//  Motor3D
//
//  Created by Hélder José Alves Gonçalves on 29/05/14.
//  Copyright (c) 2014 Duarte Nuno Ferreira Duarte. All rights reserved.
//

#include "picking.h"

Rotacao *rotPicking=NULL;
Translacao *transPicking=NULL;
Escala escPicking=NULL;
PropModel modelPicking=NULL;
TiXmlNode *cenaPick=NULL;

Picking procuraPicking(int cor){
    
    PropModel lista=l_PropModel;
    
    while (lista) {
        if (lista->picking && lista->picking->cor==cor)
            return lista->picking;
        lista=lista->next;
    }
    
    return NULL;
}


void motor_Picking(TiXmlNode *root){
    
    
    TiXmlNode *child;
    Modelo modelo;
    const char* tag;
    float color;
    
    for (child = root->FirstChild(); child; child=child->NextSibling()) {
        tag=child->Value();
        
        if (strcmp(tag, "modelo")==0) {
            modelo=modelPicking->modelo;
            if (modelPicking->picking && modelo && testaModelo(modelo->pontos)==INSIDE) {
                
                //Atribuir determinada cor ao objecto
                color=modelPicking->picking->cor/256.0f;
                glColor3f(color,color,color);
                
                if(modelo->tipo==1)
                    desenha_RTime(modelo->u.rTime);
                else
                    desenha_vbo(modelo->u.vbo, modelPicking->texID);
                
                //Tudo o resto é pintado de preto porque não interessa
                glColor3f(0, 0, 0);
            }
            //Actualiza para propModel actual
            modelPicking=modelPicking->next;
            
        }else
            if (strcmp(tag, "grupo")==0) {
                glPushMatrix();
                motor_Picking((child));
                glPopMatrix();
            }else
                if (strcmp(tag, "translacao")==0) {
                    transPicking=do_translacao(transPicking, currentTime);
                }else
                    if (strcmp(tag, "rotacao")==0) {
                        rotPicking=do_rotacao(rotPicking,currentTime);
                        
                    }else
                        if (strcmp(tag, "escala")==0)
                            escPicking=do_escala(escPicking);
        
    }
}

void do_Picking(int x, int y){

    
    Picking pick_aux;
    int luz=1, textura=1;
    
    if(!glIsEnabled(GL_LIGHTING))
        luz=0;
    
    if(!glIsEnabled(GL_TEXTURE_2D))
        textura=0;
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    if (tipo_camera==1)
        modo_explorador();
    else
        if (tipo_camera==2)
            modo_fps();
    
    
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    
    //Actualiza apontadores
    rotPicking=rotacoes;
    transPicking=translacoes;
    escPicking=escalas;
    modelPicking=l_PropModel;
    
    //Desenhar cena
    motor_Picking(cenaPick);
    
    
    //Ler posição do rato da imagem gerada
    GLint viewport[4];
    unsigned char res[4];
    glGetIntegerv(GL_VIEWPORT,viewport);
    glReadPixels(x,viewport[3]-y,1,1,
                 GL_RGBA,GL_UNSIGNED_BYTE, &res);
    
    
    if (res[0]){
        if((pick_aux=procuraPicking((int)res[0]))){
            printf("Titulo: %s\nDescrição: %s\n\n",  pick_aux->titulo, pick_aux->descricao );
            
            //Flag para poder desenhar descrição && tempo do click para a flag ser desligada passada 'X' tempo
            pick_aux->desenha=1;
            pick_aux->pressTime=currentTime;
        }
    }else
        printf("Nothing selected\n");
    
    if(luz)
        glEnable(GL_LIGHTING);
    
    if(textura)
        glEnable(GL_TEXTURE_2D);
    
    glColor3f(1, 1, 1);
    
    
}

void initPickingCena(TiXmlNode *cena){
    cenaPick=cena;
}


