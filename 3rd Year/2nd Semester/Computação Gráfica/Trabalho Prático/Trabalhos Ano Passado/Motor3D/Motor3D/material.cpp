//
//  material.cpp
//  Motor3D
//
//  Created by Hélder José Alves Gonçalves on 27/05/14.
//  Copyright (c) 2014 Duarte Nuno Ferreira Duarte. All rights reserved.
//

#include "material.h"

Material initMaterial(int tipo){

    Material novo=(Material)malloc(sizeof(NMaterial));
    
    novo->tipo=tipo;
    novo->cor[0]=0;
    novo->cor[1]=0;
    novo->cor[2]=0;
    novo->next=NULL;
    
    return novo;
}

Material preparaMaterial(TiXmlNode *root){
    
    TiXmlAttribute *attr=NULL;
    Material matt=NULL, l_materiais=NULL;
    const char *tag=NULL;
    
    for(root=root->FirstChild(); root; root=root->NextSibling()){
        
        tag=root->Value();
        if(strcmp("ambiente", tag)==0){
            matt=initMaterial(GL_AMBIENT);
            for(attr=root->ToElement()->FirstAttribute();attr;attr=attr->Next()){
                if (strcmp(attr->Name(), "r")==0)
                    matt->cor[0]=atof(attr->Value());
                else
                    if (strcmp(attr->Name(), "g")==0)
                        matt->cor[1]=atof(attr->Value());
                    else
                        if (strcmp(attr->Name(), "b")==0)
                            matt->cor[2]=atof(attr->Value());
            }
            //Adicionar à lista ligada a propriedade;
            matt->next=l_materiais;
            l_materiais=matt;
        }else
            if(strcmp("difusa", tag)==0){
                matt=initMaterial(GL_DIFFUSE);
                for(attr=root->ToElement()->FirstAttribute();attr;attr=attr->Next()){
                    if (strcmp(attr->Name(), "r")==0)
                        matt->cor[0]=atof(attr->Value());
                    else
                        if (strcmp(attr->Name(), "g")==0)
                            matt->cor[1]=atof(attr->Value());
                        else
                            if (strcmp(attr->Name(), "b")==0)
                                matt->cor[2]=atof(attr->Value());
                }
                //Adicionar à lista ligada a propriedade;
                matt->next=l_materiais;
                l_materiais=matt;
            }else
                if(strcmp("especular", tag)==0){
                    matt=initMaterial(GL_SPECULAR);
                    for(attr=root->ToElement()->FirstAttribute();attr;attr=attr->Next()){
                        if (strcmp(attr->Name(), "r")==0)
                            matt->cor[0]=atof(attr->Value());
                        else
                            if (strcmp(attr->Name(), "g")==0)
                                matt->cor[1]=atof(attr->Value());
                            else
                                if (strcmp(attr->Name(), "b")==0)
                                    matt->cor[2]=atof(attr->Value());
                    }
                    //Adicionar à lista ligada a propriedade;
                    matt->next=l_materiais;
                    l_materiais=matt;
                }else
                    if(strcmp("emissiva", tag)==0){
                        matt=initMaterial(GL_EMISSION);
                        for(attr=root->ToElement()->FirstAttribute();attr;attr=attr->Next()){
                            if (strcmp(attr->Name(), "r")==0)
                                matt->cor[0]=atof(attr->Value());
                            else
                                if (strcmp(attr->Name(), "g")==0)
                                    matt->cor[1]=atof(attr->Value());
                                else
                                    if (strcmp(attr->Name(), "b")==0)
                                        matt->cor[2]=atof(attr->Value());
                        }
                        //Adicionar à lista ligada a propriedade;
                        matt->next=l_materiais;
                        l_materiais=matt;
                    }else
                        if(strcmp("ambiente", tag)==0){
                            matt=initMaterial(GL_AMBIENT);
                            for(attr=root->ToElement()->FirstAttribute();attr;attr=attr->Next()){
                                if (strcmp(attr->Name(), "r")==0)
                                    matt->cor[0]=atof(attr->Value());
                                else
                                    if (strcmp(attr->Name(), "g")==0)
                                        matt->cor[1]=atof(attr->Value());
                                    else
                                        if (strcmp(attr->Name(), "b")==0)
                                            matt->cor[2]=atof(attr->Value());
                            }
                            //Adicionar à lista ligada a propriedade;
                            matt->next=l_materiais;
                            l_materiais=matt;
                        }else
                            if(strcmp("ambDiff", tag)==0){
                                matt=initMaterial(GL_AMBIENT_AND_DIFFUSE);
                                for(attr=root->ToElement()->FirstAttribute();attr;attr=attr->Next()){
                                    if (strcmp(attr->Name(), "r")==0)
                                        matt->cor[0]=atof(attr->Value());
                                    else
                                        if (strcmp(attr->Name(), "g")==0)
                                            matt->cor[1]=atof(attr->Value());
                                        else
                                            if (strcmp(attr->Name(), "b")==0)
                                                matt->cor[2]=atof(attr->Value());
                                }
                                //Adicionar à lista ligada a propriedade;
                                matt->next=l_materiais;
                                l_materiais=matt;
                            }
        
    }
    return l_materiais;
}

void do_Materiais(Material lista){
    Material aux=lista;
    
    while (aux) {
        glMaterialfv(GL_FRONT, aux->tipo, aux->cor);
        aux=aux->next;
    }
}

void do_MattNeutro(Material lista){
    Material aux=lista;
    float neutro[3]={0,0,0};
    
    while (aux) {
        glMaterialfv(GL_FRONT, aux->tipo, neutro);
        aux=aux->next;
    }
}



