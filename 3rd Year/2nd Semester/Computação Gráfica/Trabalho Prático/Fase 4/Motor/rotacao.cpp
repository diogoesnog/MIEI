#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>

#include "rotacao.h"

// Inser��o de uma nova rota��o.

Rotacao inserirRotacao(float periodo, float angulo, float x, float y, float z, Rotacao rotacoes){
    
	Rotacao	rotacao=NULL, 
			novasRotacoes=rotacoes;
    
	// Criamos uma nova rota��o com os valores passados como par�metro.
	rotacao = (Rotacao) malloc(sizeof(TRotacao));
	rotacao->x = x;
	rotacao->y = y;
	rotacao->z = z;

    if(periodo==0){
		rotacao->angulo=angulo;
		rotacao->periodo=0;
    }
    else{
		rotacao->periodo = periodo*1000;
		rotacao->angulo=0;
    }

	rotacao->proximo=NULL;
    
    if(!rotacoes) return rotacao;
    while(rotacoes->proximo) rotacoes=rotacoes->proximo;

    rotacoes->proximo = rotacao;

    return novasRotacoes;
}

// Reprodu��o das rota��es.

Rotacao reproduzirRotacao(Rotacao rotacao, long tempoAtual){

    if(rotacao->periodo!=0)
        glRotatef(360*(tempoAtual%rotacao->periodo)/ rotacao->periodo, rotacao->x, rotacao->y, rotacao->z);
    else
        glRotatef(rotacao->angulo, rotacao->x, rotacao->y, rotacao->z);
    
    return rotacao->proximo;
}
