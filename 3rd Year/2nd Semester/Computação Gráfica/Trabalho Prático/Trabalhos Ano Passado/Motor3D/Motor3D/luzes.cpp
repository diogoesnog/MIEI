//
//  luzes.cpp
//  Motor3D
//
//  Created by Hélder José Alves Gonçalves on 26/05/14.
//  Copyright (c) 2014 Duarte Nuno Ferreira Duarte. All rights reserved.
//

#include "luzes.h"

int n_luzes=0;
Luz luzes=NULL;

Luz initLuz(int tipo){
    
    Luz novo=(Luz)malloc(sizeof(NLuz));
    novo->luz=GL_LIGHT0+n_luzes;
    novo->tipo=tipo;
    novo->propriedade[0]=0;
    novo->propriedade[1]=0;
    novo->propriedade[2]=0;
    novo->propriedade[3]=1;
    novo->next=NULL;
    
    return novo;
}

void preparaLuzes(TiXmlNode* root){
    
    TiXmlNode *child ;
    TiXmlAttribute * attr;
    const char *tag;
    Luz luz=NULL;
    
    for (root=root->FirstChild(); root && n_luzes<8 ; root=root->NextSibling()) {
        
        if (strcmp("luz", root->Value())==0) {
            
            //Activa Luz
            glEnable(GL_LIGHT0+n_luzes);
            luz=initLuz(GL_POSITION);
            
            for(attr=root->ToElement()->FirstAttribute();attr;attr=attr->Next()){
                if (strcmp(attr->Name(), "tipo")==0){
                    if (strcmp("ponto",attr->Value())==0)
                        luz->propriedade[3]=1;
                    else
                        if (strcmp("direcional",attr->Value())==0)
                            luz->propriedade[3]=0;
                }else
                    if (strcmp(attr->Name(), "x")==0)
                        luz->propriedade[0]=atof(attr->Value());
                    else
                        if (strcmp(attr->Name(), "y")==0)
                            luz->propriedade[1]=atof(attr->Value());
                        else
                            if (strcmp(attr->Name(), "z")==0)
                                luz->propriedade[2]=atof(attr->Value());
            }
            //Adicionar à lista ligada a propriedade;
            luz->next=luzes;
            luzes=luz;
            
            //Procura propriedades da LUZ
            for (child=root->FirstChild(); child; child=child->NextSibling()) {

                tag=child->Value();
                if(strcmp("ambiente", tag)==0){
                    luz=initLuz(GL_AMBIENT);
                    for(attr=child->ToElement()->FirstAttribute();attr;attr=attr->Next()){
                        if (strcmp(attr->Name(), "r")==0)
                            luz->propriedade[0]=atof(attr->Value());
                        else
                            if (strcmp(attr->Name(), "g")==0)
                                luz->propriedade[1]=atof(attr->Value());
                            else
                                if (strcmp(attr->Name(), "b")==0)
                                    luz->propriedade[2]=atof(attr->Value());
                    }
                    //Adicionar à lista ligada a propriedade;
                    luz->next=luzes;
                    luzes=luz;
                }else
                    if(strcmp("difusa", tag)==0){
                        luz=initLuz(GL_DIFFUSE);
                        for(attr=child->ToElement()->FirstAttribute();attr;attr=attr->Next()){
                            if (strcmp(attr->Name(), "r")==0)
                                luz->propriedade[0]=atof(attr->Value());
                            else
                                if (strcmp(attr->Name(), "g")==0)
                                    luz->propriedade[1]=atof(attr->Value());
                                else
                                    if (strcmp(attr->Name(), "b")==0)
                                        luz->propriedade[2]=atof(attr->Value());
                        }
                        //Adicionar à lista ligada a propriedade;
                        luz->next=luzes;
                        luzes=luz;
                    }else
                        if(strcmp("ambDiff", tag)==0){
                            luz=initLuz(GL_AMBIENT_AND_DIFFUSE);
                            for(attr=child->ToElement()->FirstAttribute();attr;attr=attr->Next()){
                                if (strcmp(attr->Name(), "r")==0)
                                    luz->propriedade[0]=atof(attr->Value());
                                else
                                    if (strcmp(attr->Name(), "g")==0)
                                        luz->propriedade[1]=atof(attr->Value());
                                    else
                                        if (strcmp(attr->Name(), "b")==0)
                                            luz->propriedade[2]=atof(attr->Value());
                            }
                            //Adicionar à lista ligada a propriedade;
                            luz->next=luzes;
                            luzes=luz;
                        }else
                            if(strcmp("especular", tag)==0){
                                luz=initLuz(GL_SPECULAR);
                                for(attr=child->ToElement()->FirstAttribute();attr;attr=attr->Next()){
                                    if (strcmp(attr->Name(), "r")==0)
                                        luz->propriedade[0]=atof(attr->Value());
                                    else
                                        if (strcmp(attr->Name(), "g")==0)
                                            luz->propriedade[1]=atof(attr->Value());
                                        else
                                            if (strcmp(attr->Name(), "b")==0)
                                                luz->propriedade[2]=atof(attr->Value());
                                }
                                //Adicionar à lista ligada a propriedade;
                                luz->next=luzes;
                                luzes=luz;
                            }
                
            }
            n_luzes++;
        }
    }
    
}

void defineLuzes(){
    Luz aux=luzes;
    while (aux) {
        glLightfv(aux->luz, aux->tipo, aux->propriedade);
        
        //Actualiza a cabeça da lista
        aux=aux->next;
    }
}


