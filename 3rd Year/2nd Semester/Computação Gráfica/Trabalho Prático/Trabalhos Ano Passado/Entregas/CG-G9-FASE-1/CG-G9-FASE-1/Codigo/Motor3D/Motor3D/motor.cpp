//
//  motor.cpp
//  Motor3D
//
//  Created by Hélder José Alves Gonçalves on 12/03/14.
//  Copyright (c) 2014 Duarte Nuno Ferreira Duarte. All rights reserved.
//

#include "motor.h"

void desenha_modelo(const char* filename){

    float cx,cy,cz;
    FILE *f = fopen(filename, "r");
    if(f){
        glBegin(GL_TRIANGLES);
        while (fscanf(f, "%f %f %f\n", &cx, &cy, &cz)!=EOF){
            glVertex3f(cx, cy, cz);
        }
        glEnd();
        fclose(f);
    }else
        printf("ERRO! Não fez load do ficheiro '%s'!\n",filename);

}

void motor_XML(TiXmlNode* root){
    
    TiXmlNode *child;
    TiXmlAttribute * attr;
    const char* tag;
    float x,y,z,angulo;
    
    
    for (child = root->FirstChild(); child; child=child->NextSibling()) {
        tag=child->Value();

        if (strcmp(tag, "modelo")==0) {
            attr=child->ToElement()->FirstAttribute();
            if (strcmp(attr->Name(), "ficheiro")==0) {
                desenha_modelo(attr->Value());
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
                    }
        
    }
}