#include <iostream>

#include "tinyxml/tinyxml.h"

typedef struct ponto {
    float coordenadas[3] = {0.0f, 0.0f,0.0f};
    struct ponto *proximo = NULL;
} Ponto;

typedef struct translacao {
    float res[3];
    int contador;
    Ponto *pontos;
    float tempo;
    float a;
    float ultimoTempo;
    float pX;
    float pY;
    float pZ;
    struct translacao *proximo;
}Translacao;


int lerPontos(TiXmlNode* root, Ponto **res);

void getCatmullRomPoint(float t, int *indices, float *res, Ponto *points);
void getCatmullRomPointDerivada(float t, int *indices, float *res, Ponto *points);
void getGlobalCatmullRomPoint(float gt, float *res);
void renderCatmullRomCurve();

Translacao* inserirTranslacao(Ponto *listaPontos, Translacao *translacoes, int numeroPontos, float tempo, float x, float y, float z);
Translacao* reproduzirTranslacao(Translacao* translacao, long tempo);

