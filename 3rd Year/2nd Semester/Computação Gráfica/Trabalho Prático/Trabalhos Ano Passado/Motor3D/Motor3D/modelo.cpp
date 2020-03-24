//
//  modelo.cpp
//  Motor3D
//
//  Created by Hélder José Alves Gonçalves on 09/04/14.
//  Copyright (c) 2014 Duarte Nuno Ferreira Duarte. All rights reserved.
//

#include "modelo.h"
int cor_picks=1;

PropModel initPropModel(){
    PropModel aux=(PropModel)malloc(sizeof(NPropModel));
    aux->modelo=NULL;
    aux->materiais=NULL;
    aux->picking=NULL;
    aux->texID=0;
    aux->next=NULL;
    
    return aux;
}


PropModel addPropModel(PropModel novo, PropModel lista){
    PropModel aux=lista;
    if(!lista)
        return novo;
    
    while (aux->next)
        aux=aux->next;
    aux->next=novo;
    
    return lista;
}

Modelo addVbo(const char* nome, GLuint *buffers, int n_indices, unsigned short *indices, ViewFrustum viewFrustum, Modelo lista){
    
    Modelo aux=(Modelo)malloc(sizeof(NModelo));
    Vbo novo=(Vbo)malloc(sizeof(NVbo));

    //Definiçoes do modelo de VBO
    novo->nome=nome;
    novo->n_indices=n_indices;
    novo->indices=indices;
    novo->buffers=buffers;
    
    //Definiçoes para o lista de Modelos
    aux->next=lista;
    aux->tipo=2;
    aux->pontos=viewFrustum;
    aux->u.vbo=novo;
    
    return aux;
}


void desenha_vbo(Vbo vbo, unsigned int texID){
    
    //Bind da Textura
    glBindTexture(GL_TEXTURE_2D,texID);
    
    //Associação dos Buffers
    glBindBuffer(GL_ARRAY_BUFFER,vbo->buffers[0]);
    glVertexPointer(3,GL_FLOAT,0,0);
    glBindBuffer(GL_ARRAY_BUFFER,vbo->buffers[1]);
    glNormalPointer(GL_FLOAT,0,0);
    glBindBuffer(GL_ARRAY_BUFFER,vbo->buffers[2]);
    glTexCoordPointer(2, GL_FLOAT,0,0);
    
    //Desenhar com indices
    glDrawElements(GL_TRIANGLES, vbo->n_indices ,GL_UNSIGNED_SHORT, vbo->indices);
    
    //Para nehuma textura estar seleccionada
    glBindTexture(GL_TEXTURE_2D,0);
     
}

Modelo ler_VBO(const char* filename, Modelo lista){
    
    //Inicializações
    int n_pontos,n_indices, tex_pontos,i=0;
    unsigned short *indices, sx,sy,sz;
    float cx,cy,cz,*vertices=NULL,*normais=NULL,*texB=NULL;
    FILE *f = fopen(filename, "r");
    GLuint *buffers=NULL;
    ViewFrustum viewFrustum=NULL;
    
    //Testa se ficheiro existe
    if(f){
        //Lê os MAX e MIN para o ViewFrustum
        viewFrustum=(ViewFrustum)malloc(sizeof(NViewFrustum));
        fscanf(f, "%f %f %f %f %f %f\n", &viewFrustum->maxX, &viewFrustum->minX, &viewFrustum->maxY, &viewFrustum->minY, &viewFrustum->maxZ, &viewFrustum->minZ);
        
        
        //Lê o número total de pontos e aloca memória
        fscanf(f, "%d\n", &n_pontos);
        tex_pontos=(2*n_pontos)/3;
        
        vertices=(float*)malloc(n_pontos*sizeof(float));
        normais=(float*)malloc(n_pontos*sizeof(float));
        texB=(float*)malloc(tex_pontos*sizeof(float));
        
        //Lê todos os pontos que estão no ficheiro
        while (i<n_pontos){
            fscanf(f, "%f %f %f\n", &cx, &cy, &cz);
            vertices[i++]=cx;
            vertices[i++]=cy;
            vertices[i++]=cz;
        }
        i=0;
        //Lê o número total de indices e aloca memória
        fscanf(f, "%d\n", &n_indices);
        indices=(unsigned short*)malloc(n_indices*sizeof(unsigned short));
        
        //Lê todos os indices que estão no ficheiro
        while (i<n_indices){
            fscanf(f, "%hu %hu %hu\n", &sx, &sy, &sz);
            indices[i++]=sx;
            indices[i++]=sy;
            indices[i++]=sz;
        }

        //Lê as Normais que estão no ficheiro
        if (fscanf(f, "%f %f %f\n", &cx, &cy, &cz)!=EOF) {
            i=0;
            normais[i++]=cx;
            normais[i++]=cy;
            normais[i++]=cz;
            while (i<n_pontos){
                fscanf(f, "%f %f %f\n", &cx, &cy, &cz);
                normais[i++]=cx;
                normais[i++]=cy;
                normais[i++]=cz;
            }
        }
        
        //Lê as Coordenadas de textura que estão no ficheiro
        if (fscanf(f, "%f %f\n", &cx, &cy)!=EOF) {
            i=0;
            texB[i++]=cx;
            texB[i++]=cy;
            while (i<tex_pontos){
                fscanf(f, "%f %f\n", &cx, &cy);
                texB[i++]=cx;
                texB[i++]=cy;
            }
        }

        
        fclose(f);
        
        
        //Aloca memória para os buffers
        buffers=(GLuint*)malloc(3*sizeof(GLuint));
        
        //Guarda pontos na memória da gráfica
        glGenBuffers(3, buffers);
        glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
        glBufferData(GL_ARRAY_BUFFER,n_pontos*sizeof(float), vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER,buffers[1]);
        glBufferData(GL_ARRAY_BUFFER,n_pontos*sizeof(float), normais, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER,buffers[2]);
        glBufferData(GL_ARRAY_BUFFER,tex_pontos*sizeof(float), texB, GL_STATIC_DRAW);
        
        free(vertices);
        free(normais);
        free(texB);
        
        //Adiciona a VBO à estrutura
        return addVbo(filename, buffers, n_indices, indices, viewFrustum, lista);
    }else
        printf("ERRO! Não fez load do ficheiro '%s'!\n",filename);
    
    return lista;
    
}

//Real Time '.3d'
Modelo addRTime(const char* nome, float *vertices, int n_pontos, ViewFrustum viewFrustum, Modelo lista){
    
    Modelo aux=(Modelo)malloc(sizeof(NModelo));
    RTime novo =(RTime)malloc(sizeof(NRTime));
    
    //Definiçoes do modelo de RealTime
    novo->nome=nome;
    novo->vertices=vertices;
    novo->n_pontos=n_pontos;
    
    //Definiçoes para o lista de Modelos
    aux->next=lista;
    aux->tipo=1;
    aux->pontos=viewFrustum;
    aux->u.rTime=novo;

    return aux;
}


void desenha_RTime(RTime modelo){
    int i;
    float *vertices=modelo->vertices;
    
    glBegin(GL_TRIANGLES);
    for (i=0; i<modelo->n_pontos; i+=3) {
        glVertex3f(vertices[i], vertices[i+1], vertices[i+2]);
    }
    glEnd();
    
}


Modelo ler_RTime(const char* filename, Modelo lista){
    int n_pontos,i=0;
    float cx,cy,cz,*vertices;
    FILE *f = fopen(filename, "r");
    ViewFrustum viewFrustum=NULL;
    
    if(f){
        
        //Lê os MAX e MIN para o ViewFrustum
        viewFrustum=(ViewFrustum)malloc(sizeof(NViewFrustum));
        fscanf(f, "%f %f %f %f %f %f\n", &viewFrustum->maxX, &viewFrustum->minX, &viewFrustum->maxY, &viewFrustum->minY, &viewFrustum->maxZ, &viewFrustum->minZ);
        
        
        fscanf(f, "%d\n", &n_pontos);
        vertices=(float*)malloc(n_pontos*sizeof(float));
        while (fscanf(f, "%f %f %f\n", &cx, &cy, &cz)!=EOF){
            vertices[i++]=cx;
            vertices[i++]=cy;
            vertices[i++]=cz;
        }
        fclose(f);
        return addRTime(filename, vertices, n_pontos, viewFrustum, lista);
    }else
        printf("ERRO! Não fez load do ficheiro '%s'!\n",filename);
    return lista;
}


Modelo search_Modelo(const char* nome, Modelo lista){
    
    while (lista) {
        
        if(lista->tipo==1){
            if (strcmp(nome, lista->u.rTime->nome)==0)
                return lista;
        }else{
            if (strcmp(nome, lista->u.vbo->nome)==0)
                return lista;
        }
        lista=lista->next;
    }
    return NULL;
}

//--------- Picking -----------// Não devia estar aqui, mas estava a dar problema com includes e não estava com paciencia xD
Picking initPicking(){
    
    Picking picking=(Picking)malloc(sizeof(NPicking));
    picking->cor=cor_picks;
    picking->descricao="Sem descrição";
    picking->titulo="Sem titulo";
    picking->desenha=0;
    cor_picks++;
    
    return picking;
    
}


Picking preparaPicking(TiXmlNode *root){
    
    Picking picking=initPicking();
    const char* tag=NULL;
    int flag=0;
    
    
    for(root=root->FirstChild(); root; root=root->NextSibling()){

        tag=root->Value();
        if(strcmp("descricao", tag)==0){
            flag=1;
            picking->descricao=root->FirstChild()->Value();

        }else if(strcmp("titulo", tag)==0){
            flag=1;
            picking->titulo=root->FirstChild()->Value();
            
        }
    }
    
    
    if(flag)
        return picking;
    
    free(picking);
    return NULL;
    
}

void renderBitmapString(float x,float y,float z,void *font,char *string) {
    
    char *c;
    glRasterPos3f(x, y, z);
    for (c=string; *c != '\0'; c++) {
       // glutBitmapCharacter(font, *c);
         glutBitmapCharacter(font, *c);
    }
}

void do_Picking(Picking pick,ViewFrustum viewFC, long time){
    if (pick && pick->desenha==1) {
        
        int luz=1, textura=1;
        if(!glIsEnabled(GL_LIGHTING))
            luz=0;
        
        if(!glIsEnabled(GL_TEXTURE_2D))
            textura=0;
        
        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
        
        if(time-pick->pressTime>5000)
            pick->desenha=0;
        
        renderBitmapString(0, 2*viewFC->maxY, 0, GLUT_BITMAP_HELVETICA_18, (char*)pick->titulo);
        renderBitmapString(0, viewFC->maxY, 0, GLUT_BITMAP_HELVETICA_12, (char*)pick->descricao);

        
        if(luz)
            glEnable(GL_LIGHTING);
        
        if(textura)
            glEnable(GL_TEXTURE_2D);
    }
}


    


