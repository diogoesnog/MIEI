#include <math.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>

#include "catmullRom.h"

Ponto	*pontosGl = NULL;
int		contadorPontosGl = 0;

int lerPontos(TiXmlNode *root, Ponto **res){

	Ponto			*auxiliar = NULL, 
					*pontos = NULL, 
					*ultimo = NULL;

	int				contadorPontos = 0;
	const char		*tag;
	int				x, y, z;

    TiXmlNode		*child;
    TiXmlAttribute	*attr;    
     
    x=y=z=0;
    
    for (child=root->FirstChild(); child; child=child->NextSibling()) {
        tag=child->Value();
        if (strcmp(tag, "ponto")==0) {
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

            auxiliar=(Ponto*) malloc(sizeof(Ponto));
            auxiliar->coordenadas[0] = x; auxiliar->coordenadas[1] = y; auxiliar->coordenadas[2] = z;

            if(ultimo!=NULL) ultimo->proximo=auxiliar;

            ultimo=auxiliar;

            if(pontos==NULL) pontos=ultimo;
            
            contadorPontos++;            
        }
    }

    *res=pontos;

    return contadorPontos;
}


float getAt(int indice, Ponto *points, int l) {
    int i=0;
    float res=0.0;
    Ponto *aux=points;
    while(i++<indice && aux!=NULL){
        aux=aux->proximo;
    }
    
    res=aux->coordenadas[l];
    
    return res;
}

void getCatmullRomPoint(float t, int *indices, float *res, Ponto *points){
    
    int		i,j,k;
    float	aux[4];
    float	tt[4];

    tt[0]=t*t*t;
    tt[1]=t*t;
    tt[2]=t;
    tt[3]=1;

	// Matriz Catmull-Rom (4 por 4)
	float m[4][4] = {{-0.5f,  1.5f, -1.5f,  0.5f},
					 { 1.0f, -2.5f,  2.0f, -0.5f},
					 {-0.5f,  0.0f,  0.5f,  0.0f},
					 { 0.0f,  1.0f,  0.0f,  0.0f}};
    
	res[0] = 0.0; res[1] = 0.0; res[2] = 0.0;

    // Cálculo do ponto res = T * M * P
    for (k=0;k<3;k++){
        for (i=0;i<4;i++){
            aux[i]=0;
            for (j=0;j<4;j++){
                aux[i]+=(tt[j]*m[j][i]);
            }
        }
        for(i=0;i<4;i++){
            res[k]+=aux[i]*getAt(indices[i],points,k);
        }
    }
}

void getCatmullRomPointDerivada(float t, int *indices, float *res, Ponto *points) {
    
    int		i,j,k;
    float	aux[4];
    float	tt[4];

    tt[0]=3*t*t;
    tt[1]=2*t;
    tt[2]=1;
    tt[3]=0;

	// Matriz Catmull-Rom (4 por 4)
	float m[4][4] = {	{-0.5f,  1.5f, -1.5f,  0.5f},
						{ 1.0f, -2.5f,  2.0f, -0.5f},
						{-0.5f,  0.0f,  0.5f,  0.0f},
						{ 0.0f,  1.0f,  0.0f,  0.0f}};
    
	res[0] = 0.0; res[1] = 0.0; res[2] = 0.0;


	// Cálculo do ponto res = T * M * P
	for (k=0;k<3;k++){
        for (i=0;i<4;i++){
            aux[i]=0;
            for (j=0;j<4;j++){
                aux[i]+=(tt[j]*m[j][i]);
            }
        }
        for(i=0;i<4;i++){
            res[k]+=aux[i]*getAt(indices[i],points,k);
        }
    }
}

void getGlobalCatmullRomPoint(float gt, float *res){
    
	float t = gt * contadorPontosGl; 
	int index = floor(t);			
	t = t - index;				
    
	int indices[4];

	indices[0] = (index + contadorPontosGl-1)%contadorPontosGl;
    indices[1] = (indices[0]+1)%contadorPontosGl;
	indices[2] = (indices[1]+1)%contadorPontosGl;
    indices[3] = (indices[2]+1)%contadorPontosGl;
    
	getCatmullRomPoint(t, indices, res, pontosGl);
}

// Desenho das curvas cúbicas
void renderCatmullRomCurve(){

    int		i;
    float	res[3];

    glBegin(GL_LINE_LOOP);

    for(i=0;i<2000;i++){
        getGlobalCatmullRomPoint(i/2000.0f,res);
        glVertex3fv(res);
    }

    glEnd();
}

// Funções relativas à translação

Translacao* inserirTranslacao(Ponto *listaPontos, Translacao *translacoes, int numeroPontos, float tempo, float x, float y, float z){

    Translacao		*translacao = NULL,
					*translacaoFinal = NULL;

    translacao=(Translacao*) malloc(sizeof(Translacao));
    translacao->pontos = listaPontos;
    translacao->contador = numeroPontos;
    translacao->tempo = tempo;
    translacao->a = 0;
    translacao->ultimoTempo = 0;
    translacao->pX = x;
    translacao->pY = y;
    translacao->pZ = z;
    translacao->proximo = NULL;

	// Processo igual ao da rotação e escala.

    if(translacoes==NULL){
        translacoes=translacao;
    } else {
        if(translacoes!=NULL)
            for(translacaoFinal=translacoes; translacaoFinal->proximo!=NULL; translacaoFinal=translacaoFinal->proximo);
        translacaoFinal->proximo=translacao;
    }

    return translacoes;
}

Translacao* reproduzirTranslacao(Translacao* translacao, long tempo){

    if (translacao->tempo!=0){

        contadorPontosGl=translacao->contador;
        pontosGl = translacao->pontos;

        if(translacao->ultimoTempo==0)
            translacao->ultimoTempo=tempo;
        
        else{
            translacao->a+=((tempo-translacao->ultimoTempo)/(translacao->tempo*1000));
            translacao->ultimoTempo=tempo;

			getGlobalCatmullRomPoint((translacao->a),translacao->res);

			// Desenho das curvas que representam a trajetória.
            renderCatmullRomCurve();

            glTranslatef(translacao->res[0],translacao->res[1],translacao->res[2]);
        }
    }
    else {
        glTranslatef(translacao->pX,translacao->pY,translacao->pZ);
    }
    return translacao->proximo;
}

