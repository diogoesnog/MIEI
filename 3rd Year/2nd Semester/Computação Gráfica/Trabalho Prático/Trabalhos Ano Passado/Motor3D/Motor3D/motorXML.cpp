//
//  motor.cpp
//  Motor3D
//
//  Created by Hélder José Alves Gonçalves on 12/03/14.
//  Copyright (c) 2014 Duarte Nuno Ferreira Duarte. All rights reserved.
//

#include "motorXML.h"

Modelo lista_modelos=NULL;
int first;


void motor_XML(TiXmlNode* root){
    
    TiXmlNode *child;
    Modelo modelo;
    const char* tag;
    
    for (child = root->FirstChild(); child; child=child->NextSibling()) {
        tag=child->Value();
        
        if (strcmp(tag, "modelo")==0) {
            modelo=prop_actual->modelo;
            if (modelo && ( enableViewFrustum ||testaModelo(modelo->pontos)==INSIDE)) {
                do_Materiais(prop_actual->materiais);
                if(modelo->tipo==1)
                    desenha_RTime(modelo->u.rTime);
                else
                    desenha_vbo(modelo->u.vbo, prop_actual->texID);
                
                do_MattNeutro(prop_actual->materiais);
                do_Picking(prop_actual->picking, modelo->pontos,currentTime);
                n_desenhos++;
                
                //Desenhar caixas do ViewFrustum
                if(caixasDesenho)
                    desenhaCaixa(modelo->pontos);
            }
            //Actualiza para propModel actual
            prop_actual=prop_actual->next;
        }else
            if (strcmp(tag, "grupo")==0) {
                glPushMatrix();
                motor_XML((child));
                glPopMatrix();
            }else
                if (strcmp(tag, "translacao")==0) {
                        tra_actual=do_translacao(tra_actual, currentTime);
                    }else
                        if (strcmp(tag, "rotacao")==0) {
                            rot_actual=do_rotacao(rot_actual,currentTime);
                            
                        }else
                            if (strcmp(tag, "escala")==0)
                                   esc_actual=do_escala(esc_actual);
        
    }
}

void prepara_MotorXML(TiXmlNode* root){
    
    TiXmlNode *child=NULL;
    TiXmlAttribute * attr;
    Modelo modelo;
    PropModel propModel=NULL;
    const char* tag;
    float x,y,z,angulo,tempo;
    Point *listaPontos=NULL;
    int numeroPontos=-1;
    float timeTrans=-1;
    int flag;
    
    unsigned int t,tw,th;
	unsigned char *texData;
    
    
    for (root = root->FirstChild(); root; root=root->NextSibling()) {
        tag=root->Value();
        if (strcmp(tag, "grupo")==0) {
            prepara_MotorXML((root));
        }else
            if (strcmp(tag, "modelo")==0) {
                propModel=initPropModel();
                for(attr=root->ToElement()->FirstAttribute();attr;attr=attr->Next()){
                    if (strcmp(attr->Name(), "ficheiro")==0) {
                        modelo=search_Modelo(attr->Value(), lista_modelos);
                        if (!modelo) {
                            
                            std::regex e ("(.*)(.vbo)");
                            if(std::regex_match(attr->Value(), e) ){
                                lista_modelos=ler_VBO(attr->Value(),lista_modelos);
                                propModel->modelo=lista_modelos;
                                total_desenhos++;
                            }
                            else{
                                std::regex e ("(.*)(.3d)");
                                if(std::regex_match(attr->Value(), e) ){
                                    lista_modelos=ler_RTime(attr->Value(),lista_modelos);
                                    propModel->modelo=lista_modelos;
                                    total_desenhos++;
                                }
                                else
                                    printf("ERRO! Ficheiro '%s' inexistente\n", attr->Value());
                            }
                        }else{
                            propModel->modelo=modelo;
                            total_desenhos++;
                        }
                        
                    }else if (strcmp(attr->Name(), "textura")==0) {
                        //Carregar textura
                        ilEnable(IL_ORIGIN_SET);
                        ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
                        ilGenImages(1,&t);
                        ilBindImage(t);
                        ilLoadImage((ILstring)attr->Value());
                        tw = ilGetInteger(IL_IMAGE_WIDTH);
                        th = ilGetInteger(IL_IMAGE_HEIGHT);
                        ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
                        texData = ilGetData();
                        
                        glGenTextures(1,&propModel->texID);
                        
                        glBindTexture(GL_TEXTURE_2D,propModel->texID);
                        glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_WRAP_S,		GL_REPEAT);
                        glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_WRAP_T,		GL_REPEAT);
                        
                        glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_MAG_FILTER,   	GL_LINEAR);
                        glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_MIN_FILTER,    	GL_LINEAR);
                        
                        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
                        
                    }
                }
                for (child=root->FirstChild(); child; child=child->NextSibling()) {
                    tag=child->Value();
                    
                    //Propiedades do Picking
                    if(strcmp("picking", tag)==0){
                        propModel->picking=preparaPicking(child);
                    }else
                        //Propriedades dos Materiais
                        if(strcmp("materiais", tag)==0){
                        propModel->materiais=preparaMaterial(child);
                    }
                }
                
                //Adicionar PropModel
                l_PropModel=addPropModel(propModel, l_PropModel);
                
            }else
                if (strcmp(tag, "translacao")==0) {
                    x=y=z=0;
                    flag=0;
                    timeTrans=0;
                    for(attr=root->ToElement()->FirstAttribute();attr;attr=attr->Next()){
                        if (strcmp(attr->Name(), "tempo")==0)
                            timeTrans=atof(attr->Value());
                        else
                            if (strcmp(attr->Name(), "x")==0){
                                x=atof(attr->Value());
                                flag=1;}
                            else
                                if (strcmp(attr->Name(), "y")==0){
                                    y=atof(attr->Value());
                                    flag=1;}
                                else
                                    if (strcmp(attr->Name(), "z")==0){
                                        z=atof(attr->Value());
                                        flag=1;
                                    }
                    }
                    if(flag==1)
                        timeTrans=0;
                    listaPontos = NULL;
                    numeroPontos = -1;
                    numeroPontos = lerPontos(root, &listaPontos);
                    translacoes=insereTranslacao(listaPontos,translacoes,numeroPontos, timeTrans, x, y, z);
                }
                else
                    if (strcmp(tag, "rotacao")==0) {
                        angulo=x=y=z=0;
                        for(attr=root->ToElement()->FirstAttribute();attr;attr=attr->Next()){
                            if (strcmp(attr->Name(), "x")==0)
                                x=atof(attr->Value());
                            else
                                if (strcmp(attr->Name(), "y")==0)
                                    y=atof(attr->Value());
                                else
                                    if (strcmp(attr->Name(), "z")==0)
                                        z=atof(attr->Value());
                                    else
                                        if (strcmp(attr->Name(), "tempo")==0)
                                            tempo=atof(attr->Value());
                                        else
                                            if (strcmp(attr->Name(), "angulo")==0)
                                                angulo=atof(attr->Value());
                        }
                        if(angulo)
                            rotacoes=insereRotacao(0,angulo,x,y,z,rotacoes);
                        else
                            rotacoes=insereRotacao(tempo,0,x,y,z,rotacoes);
                    }else
                        if (strcmp(tag, "escala")==0) {
                            x=y=z=1;
                            for(attr=root->ToElement()->FirstAttribute();attr;attr=attr->Next()){
                                if (strcmp(attr->Name(), "x")==0)
                                    x=atof(attr->Value());
                                else
                                    if (strcmp(attr->Name(), "y")==0)
                                        y=atof(attr->Value());
                                    else
                                        if (strcmp(attr->Name(), "z")==0)
                                            z=atof(attr->Value());
                            }
                            escalas=insereEscala(x,y,z,escalas);
                        }

        
    }
}

