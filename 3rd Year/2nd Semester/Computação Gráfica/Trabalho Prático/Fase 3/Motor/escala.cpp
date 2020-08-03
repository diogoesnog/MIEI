#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>

#include "escala.h"

// Inser��o de uma nova escala.

Escala inserirEscala(float x, float y, float z, Escala escalas){

    Escala	escala=NULL, 
			novasEscalas=escalas;
    
	// Criamos uma nova escala com os valores passados como par�metro.
    escala = (Escala) malloc(sizeof(TEscala));
    escala->x = x;
    escala->y = y;
    escala->z = z;
    escala->proximo = NULL;
    
	// Percorremos todas as escalas, inserindo a nova no final da Lista.
    if(!escalas) return escala;
    while (escalas->proximo) escalas = escalas->proximo;
    
	escalas->proximo = escala;
    
    return novasEscalas;
}

// Reprodu��o das escalas.

Escala reproduzirEscala(Escala escala){
    glScalef(escala->x, escala->y, escala->z);
    return escala->proximo;
}