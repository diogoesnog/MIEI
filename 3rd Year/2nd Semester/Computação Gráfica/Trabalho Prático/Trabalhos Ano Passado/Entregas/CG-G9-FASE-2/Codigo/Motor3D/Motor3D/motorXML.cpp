//
//  motor.cpp
//  Motor3D
//
//  Created by Hélder José Alves Gonçalves on 12/03/14.
//  Copyright (c) 2014 Duarte Nuno Ferreira Duarte. All rights reserved.
//

#include "motorXML.h"

Modelo lista_modelos=NULL;

void desenha_modelo(Modelo modelo){
    int i;
    float *vertices=modelo->vertices;
    
    glBegin(GL_TRIANGLES);
    for (i=0; i<modelo->n_pontos; i+=3) {
        glVertex3f(vertices[i], vertices[i+1], vertices[i+2]);
    }
    glEnd();
    
}


void ler_modelo(const char* filename){
    int n_pontos,i=0;
    float cx,cy,cz,*vertices;
    FILE *f = fopen(filename, "r");
    if(f){
        fscanf(f, "%d\n", &n_pontos);
        vertices=(float*)malloc(n_pontos*sizeof(float));
        while (fscanf(f, "%f %f %f\n", &cx, &cy, &cz)!=EOF){
            vertices[i++]=cx;
            vertices[i++]=cy;
            vertices[i++]=cz;
        }
        fclose(f);
        lista_modelos=addModelo(filename, vertices, n_pontos, lista_modelos);
        desenha_modelo(lista_modelos);
    }else
        printf("ERRO! Não fez load do ficheiro '%s'!\n",filename);
    
}

void motor_XML(TiXmlNode* root){
    
    TiXmlNode *child;
    TiXmlAttribute * attr;
    Modelo modelo;
    const char* tag;
    float x,y,z,angulo;

    
    
    for (child = root->FirstChild(); child; child=child->NextSibling()) {
        tag=child->Value();

        if (strcmp(tag, "modelo")==0) {
            attr=child->ToElement()->FirstAttribute();
            if (strcmp(attr->Name(), "ficheiro")==0) {
                modelo=search_Modelo(attr->Value(), lista_modelos);
                if (modelo) {
                    desenha_modelo(modelo);
                }else
                    ler_modelo(attr->Value());
            }
        }else
            if (strcmp(tag, "grupo")==0) {
                glPushMatrix();
                motor_XML((child));
                glPopMatrix();
            }else
                if (strcmp(tag, "translacao")==0) {
                    x=y=z=0;
                    for(attr=child->ToElement()->FirstAttribute();attr;attr=attr->Next()){
                        if (strcmp(attr->Name(), "x")==0)
                            x=atof(attr->Value());
                        else
                            if (strcmp(attr->Name(), "y")==0)
                            y=atof(attr->Value());
                        else
                            if (strcmp(attr->Name(), "z")==0)
                                z=atof(attr->Value());
                    }
                    glTranslatef(x, y, z);
                }else
                    if (strcmp(tag, "rotacao")==0) {
                        angulo=x=y=z=0;
                        for(attr=child->ToElement()->FirstAttribute();attr;attr=attr->Next()){
                            if (strcmp(attr->Name(), "x")==0)
                                x=atof(attr->Value());
                            else
                                if (strcmp(attr->Name(), "y")==0)
                                    y=atof(attr->Value());
                                else
                                    if (strcmp(attr->Name(), "z")==0)
                                        z=atof(attr->Value());
                                    else
                                        if (strcmp(attr->Name(), "angulo")==0)
                                            angulo=atof(attr->Value());
                        }
                        glRotatef(angulo, x, y, z);
                    }else
                        if (strcmp(tag, "escala")==0) {
                            x=y=z=1;
                            for(attr=child->ToElement()->FirstAttribute();attr;attr=attr->Next()){
                                if (strcmp(attr->Name(), "x")==0)
                                    x=atof(attr->Value());
                                else
                                    if (strcmp(attr->Name(), "y")==0)
                                        y=atof(attr->Value());
                                    else
                                        if (strcmp(attr->Name(), "z")==0)
                                            z=atof(attr->Value());
                            }
                            glScalef(x, y, z);
                        }
        
    }
}