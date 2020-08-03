/**
\mainpage Coffeebreak - Projeto LI2

@author Diogo Araújo.
@author Diogo Nogueira.
@author Ivo Pimenta.

@version 1.0
@date 11.06.2017

O Coffeebreak foi um projeto realizado no âmbito da Unidade Curricular: Laboratórios de Informática II e que consistiu em implementar um jogo do tipo Roguelike.<br>
Esta página html que contém toda a documentação do nosso código tem o intuito de esclarecer todas as funções por nós criadas e que tornaram possível a perfeita execução do nosso jogo.
*/                                                                                                                                                                                                                                                                                                                                                                                                             

/**
@file jogo.c
@brief Função que gera o jogo em si, invocando todas as outras funções essenciais ao seu funcionamento.
@author Diogo Araújo. 
@author Diogo Nogueira.
@author Ivo Pimenta.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "cgi.h"
#include "estado.h"
#include "ficheiro.h"
#include "bestscores.h"

/** 
\brief O  tamanho máximo do buffer. 
*/
#define MAX_BUFFER		10240

/**
\brief O tamanho da janela do browser. 
*/
#define TAM				10

/**
\brief O tamanho da àrea jogável.
*/
#define ESCALA			62

/**
\brief Função que verifica se uma posição é válida de ser ocupada pelo jogador.
@param x Coordenada x dessa posição.
@param y Coordenada y dessa posição.
@returns 1 ou 0 consoante o boolean da lógica pedida.
*/
int posicao_valida(int x, int y) {
	return x >= 0 && y >= 0 && x < TAM && y < TAM;
}

/**
\brief Função que imprime uma casa 
@param x Coordenada x dessa casa.
@param y Coordenada y dessa casa.
*/
void imprime_casa(int x, int y) {
	char *cor[] = {"#cccccc", "#e5e5e5"};
	int idx = (x + y) % 2;
	QUADRADO(x, y,ESCALA, cor[idx]);
}

/** 
\brief Função que imprime uma casa transparente para que não exista sobreposição entre jogador e inimigo.
@param x Coordenada x dessa casa.
@param y Coordenada y dessa casa.
*/
void imprime_casa_transparente(int x, int y) {
	QUADRADO_TRANSPARENTE(x, y,ESCALA);
}

/** 
\brief Função que verifica se duas posições são iguais em termos de coordenadas.
@param p Posicão do jogador.
@param x Coordenada x da posição a comparar.
@param y Coordenada y da posição a comparar.
@returns 1 ou 0 consoante o boolean da lógica pedida.
*/
int posicao_igual (POSICAO p, int x, int y){
	return p.x == x && p.y == y;
}

/** 
\brief Função que verifica se uma determinada casa contém um inimigo.
@param e Estado atual do jogo.
@param x Coordenada x da casa a verificar.
@param y Coordenada y da casa a verificar.
@returns 1 ou 0 consoante o boolean da lógica pedida.
*/
int tem_inimigo (ESTADO e, int x, int y){
	int i;
	for (i = 0; i < e.num_inimigos;i++)
		if (posicao_igual (e.inimigo[i],x,y))
			return 1;
	return 0;
}

/**
\brief Função que verfica se uma determinada casa contém um obstáculo.
@param e Estado atual do jogo.
@param x Coordenada x da casa a verificar.
@param y Coordenada y da casa a verificar.
@returns 1 ou 0 consoante o boolean da lógica pedida.
*/
int tem_obstaculo (ESTADO e, int x, int y){
	int i;
	for (i = 0; i < e.num_obstaculos ;i++)
		if (posicao_igual (e.obstaculo[i],x,y))
			return 1;
	return 0;
}

/**
\brief Função que verifica se uma determinada casa contém um jogador.
@param e Estado atual do jogo.
@param x Coordenada x da casa a verificar.
@param y Coordenada y da casa a verificar.
@returns 1 ou 0 consoante o boolean da lógica pedida.
*/
int tem_jogador (ESTADO e, int x, int y) {
	return e.jog.x == x && e.jog.y == y;
}

/**
\brief Função que verifica se uma determinada casa contém a saída.
@param e Estado atual do jogo.
@param x Coordenada x da casa a verificar.
@param y Coordenada y da casa a verificar.
@returns 1 ou 0 consoante o boolean da lógica pedida.
*/
int tem_saida(ESTADO e, int x, int y){
	return e.saida.x == x && e.saida.y == y;
}

/**
\brief Função que verifica se uma determinada casa se encontra ocupada com todos as possibilidades.
@param e Estado atual do jogo.
@param x Coordenada x da casa a verificar.
@param y Coordenada y da casa a verificar.
@returns 1 ou 0 consoante o boolean da lógica pedida.
*/
int casa_ocupada(ESTADO e, int x, int y) {
	return tem_inimigo(e,x,y) || tem_obstaculo(e,x,y) || tem_jogador(e,x,y) || tem_saida(e,x,y);
}

/**
\brief Função que verifica se uma determinada casa se encontra ocupada com um obstáculo ou com um jogador.
@param e Estado atual do jogo.
@param x Coordenada x da casa a verificar.
@param y Coordenada y da casa a verificar.
@returns 1 ou 0 consoante o boolean da lógica pedida.
*/
int casa_ocupada2(ESTADO e, int x, int y) {
	return tem_obstaculo(e,x,y) || tem_jogador(e,x,y);
}

/**
\brief Função que inicializa um inimigo de forma aleatória numa casa livre.
@param e Estado atual do jogo.
@returns Estado com as modificações apropriadas.
*/
ESTADO inicializar_inimigo (ESTADO e) {
	char x,y;
	do {
	x = random() % TAM;
	y = random() % TAM;
	} while (casa_ocupada (e,x,y) || tem_saida(e,x,y));
	e.inimigo[(int)e.num_inimigos].x = x;
	e.inimigo[(int)e.num_inimigos].y = y;
	e.num_inimigos++;
	return e;
}

/**
\brief Função que inicializa todos os inimigos até total de inimigos definidos.
@param e Estado atual do jogo.
@param num_inimigos Nº total de inimigos.
@returns Estado com as modificações apropriadas.
*/
ESTADO inicializar_inimigos (ESTADO e, int num_inimigos){
	int i;
	for (i=0;i<num_inimigos;i++)
		e = inicializar_inimigo (e);
	return e;
}

/**
\brief Função que inicializa um obstáculo de forma aleatória.
@param e Estado atual do jogo.
@returns Estado com as modificações apropriadas.
*/
ESTADO inicializar_obstaculo (ESTADO e) {
	char x,y;
	do {
	x = random() % TAM;
	y = random() % TAM;
	} while (casa_ocupada (e,x,y) || tem_saida(e,x,y));
	e.obstaculo[(int)e.num_obstaculos].x = x;
	e.obstaculo[(int)e.num_obstaculos].y = y;
	e.num_obstaculos++;
	return e;
}

/**
\brief Função que inicializa todos os obstáculos até ao total de obstáculos definidos.
@param e Estado atual do jogo.
@param num_obstaculos Nº total de obstáculos.
@returns Estado com as modificações apropriadas.
*/
ESTADO inicializar_obstaculos (ESTADO e, int num_obstaculos){
	int i;
	for (i=0;i<num_obstaculos;i++)
		e = inicializar_obstaculo (e);
	return e;
}

/**
\brief Função que inicializa a saída de forma aleatória.
@param e Estado atual do jogo.
@returns Estado com as modificações apropriadas.
*/
ESTADO inicializar_saida (ESTADO e) {
	char x,y;
	do {
	x = random() % TAM;
	y = random() % TAM;
	} while (casa_ocupada (e,x,y));
	e.saida.x = x;
	e.saida.y = y;
	return e;
}

/**
\brief Função que inicializa um estado completamente novo.
@param score Score total do jogo anterior.
@returns Estado com as modificações apropriadas.
*/
ESTADO inicializar(int score) {
	ESTADO e;
	memset(&e, 0, sizeof(ESTADO));

	e.jog.x = random() % TAM;
	e.jog.y = random() % TAM;
	e.score = score;
	e.vidas = 10;
	e = inicializar_inimigos (e,13);
	e = inicializar_obstaculos (e, 20);
	e = inicializar_saida (e);
	return e;
}

/**
\brief Função que inicializa um estado apropriado caso o jogador passe ao próximo nível.
@param e Estado atual do jogo.
@returns Estado com as modificações apropriadas.
*/
ESTADO inicializar_nivel(ESTADO e) {
	ESTADO new;
	memset(&new, 0, sizeof(ESTADO));
	
	new.jog.x = random() % TAM;
	new.jog.y = random() % TAM;
	new.score = e.score;
	new.vidas = e.vidas;
	new = inicializar_inimigos (new,13);
	new = inicializar_obstaculos (new, 20);
	new = inicializar_saida (new);
	return new;
}

/**
\brief Função que atualiza o estado do jogo movendo os inimigos.
@param e Estado atual do jogo.
@returns Estado com as modificações apropriadas.
*/
ESTADO atualiza_inimigos (ESTADO e) {
	int i;
	int x = e.jog.x;
	int y = e.jog.y;
	int dx;
	int dy;
	int distancia;

	for (i=0; i < ((int)e.num_inimigos); i++) {
		int xi = e.inimigo[i].x;
		int yi = e.inimigo[i].y;
		dx = 0; // Apenas para não dar warning de maybe uninitialized variable.
		dy = 0; // Apenas para não dar warning de maybe uninitialized variable.
		if(x==xi) dx=0;
		if(x>xi) dx=1;
		if(x<xi) dx=-1;

		if(y==yi) dy=0;
		if(y>yi) dy=1;
		if(y<yi) dy=-1;

		if(abs(x-xi)>abs(y-yi)) distancia = abs(x-xi);
		else distancia = abs(y-yi);
	
		if (!casa_ocupada(e,xi+dx, yi+dy)) {
			xi+=dx;
			yi+=dy;
		}
		else if (!casa_ocupada(e, xi, yi+dy)) {
			yi+=dy;
		}
		else if (!casa_ocupada(e, xi+dx, yi)) {
			xi+=dx;
		}
		if (distancia > 1) {
			e.inimigo[i].x = xi;
			e.inimigo[i].y = yi;
		}
		else {
			e.vidas--;
		}
	}
	return e;
}

/**
\brief Função que destrói um inimigo.
@param e Estado atual do jogo.
@param i Identificador/número do inimigo.
@returns Estado com as modificações apropriadas.
*/
ESTADO destroi_inimigo (ESTADO e, int i) {
	int k;
	for (k=i+1; k<e.num_inimigos; k++) {
		e.inimigo[k-1] = e.inimigo[k];
	}
	e.vidas++;
	e.num_inimigos--;
	return e;
}

/**
\brief Função que move o jogador destruindo o inimigo caso o mesmo seja selecionado.
@param e Estado atual do jogo.
@param dx Coordenada x que é somada à posição atual do jogador a casa para onde o jogador vai.
@param dy Coordenada y que é somada à posição atual do jogador a casa para onde o jogador vai.
@param acao Ação que define o movimento do jogador.
*/
void imprime_movimento(ESTADO e,int dx, int dy, char acao) {
	int x = e.jog.x+dx;
	int y = e.jog.y+dy;
	
	if(!posicao_valida(x, y))
		return;
	if (casa_ocupada2(e, x, y))
		return;

	if(tem_inimigo(e, x, y)) {
		int i;
		for (i=0; i<e.num_inimigos; i++) {
			if (x==e.inimigo[i].x && y==e.inimigo[i].y) {
				e = destroi_inimigo(e, i);
				e.score += 20;
			}
		}
	}
	
	char link[MAX_BUFFER];
	sprintf(link, "http://localhost/cgi-bin/jogo?%c", acao);
	ABRIR_LINK(link);
	imprime_casa_transparente(x, y);
	FECHAR_LINK;
}

/** 
\brief Função que imprime o jogador atribuindo a devida ação.
@param e Estado atual do jogo.
*/
void imprime_jogador(ESTADO e) {
	imprime_movimento(e,1 ,0 ,'1');
	imprime_movimento(e,1, 1,'2');
	imprime_movimento(e,0 ,1 ,'3');
	imprime_movimento(e,-1, 1 ,'4');
	imprime_movimento(e,-1,0 ,'5');
	imprime_movimento(e,-1 ,-1 ,'6');
	imprime_movimento(e,0,-1,'7');
	imprime_movimento(e,1 ,-1 ,'8');
	IMAGEM(e.jog.x, e.jog.y, ESCALA, "link.png");	
}

/**
\brief Função que lê o estado.
@param *args Argumentos recebidos da Query String.
@returns Estado com as modificações apropriadas.
*/
ESTADO ler_link(char *args) {
	if(strlen(args) == 0) {
		return inicializar(0);
	}
	ESTADO e = ler_ficheiro();
	e.acao = *args;
	return e;
}

/** 
\brief Função que imprime todos os inimigos até ao total definido. 
@param e Estado atual do jogo.
*/
void imprime_inimigos(ESTADO e) {
	int i;
	for(i = 0; i < e.num_inimigos; i++)
		IMAGEM(e.inimigo[i].x, e.inimigo[i].y, ESCALA, "enemy.png");
}

/** 
\brief Função que imprime todos os obstáculos até ao total definido.
@param e Estado atual do jogo.
*/
void imprime_obstaculos(ESTADO e) {
	int i;
	for(i = 0; i < e.num_obstaculos; i++)
		IMAGEM(e.obstaculo[i].x, e.obstaculo[i].y, ESCALA, "rock.png");
}

/** 
\brief Função que imprime a única saída do jogo.
@param e Estado atual do jogo.
*/
void imprime_saida(ESTADO e) {
	IMAGEM(e.saida.x, e.saida.y, ESCALA, "door.png");
}

/** 
\brief Função que imprime as vidas do jogador.
@param e Estado atual do jogo.
*/
void imprime_vidas(ESTADO e) {
	int vidas = e.vidas;
	int i;
	int local = 20;
	for (i=0; i<vidas; i++){
		IMAGEM(40+((i*22)+local), 13, 20, "life.png");}
}

/**
\brief Função que cria um pop-up em forma de imagem a anunciar o fim do jogo.
@param e Estado atual do jogo.
@returns Estado com as modificaões apropriadas.
*/
ESTADO fim_jogo (ESTADO e) {
	IMAGEMFJ(0,0,620,"gameover.png");
	escreve_score(e.score);
	return e;
}

/**
\brief Função que cria um novo mapa quando o jogador chega à saída.
@param e Estado atual do jogo.
@returns Estado com as modificações apropriadas.
*/
ESTADO saida(ESTADO e){
		if(e.jog.x == e.saida.x && e.jog.y == e.saida.y) {
		e.score+=100;
		e = inicializar_nivel(e);
	}
	return e;
}

/**
\brief Função que decide quando o inimigo morre.
@param e Estado atual do jogo.
@param x Coordenada x do inimigo.
@param y Coordenada y do inimigo.
@returns Estado com as modificações apropriadas.
*/
ESTADO mata_inimigo(ESTADO e, int x, int y) {
	if(tem_inimigo(e, x, y)) {
		int i;
		for (i=0; i<e.num_inimigos; i++) {
			if (x==e.inimigo[i].x && y==e.inimigo[i].y) {
				e = destroi_inimigo(e, i);
				e.score += 20;
			}
		}
	}
	return e;
}
/**
\brief Função que move o jogador.
@param e Estado atual do jogo.
@param dx Coordenada x que soma à posição atual do jogador a casa para onde o jogador vai.
@param dy Coordenada y que soma à posição atual do jogador a casa para onde o jogador vai.
@returns Estado com as modificações apropriadas.
*/
ESTADO mover_jogador(ESTADO e, int dx, int dy) {
	int x = e.jog.x+dx;
	int y = e.jog.y+dy;
	
	if(!posicao_valida(x, y))
		return e;
	if (casa_ocupada2(e, x, y))
		return e;
	e = mata_inimigo(e,x,y);
	e.jog.x = x;
	e.jog.y = y;

	e = saida(e);
	e = atualiza_inimigos(e);

	return e;
}

/**
\brief Função que decide para onde o jogador se move de acordo com a ação.
@param e Estado atual do jogo.
@param acao Decide qual a direção do jogador.
@returns Estado com as modificações apropriadas.
*/
ESTADO 	processa_acao(ESTADO e, char acao) {
	if (acao=='1') {
		e = mover_jogador(e, +1, 0);		
	}
	if (acao=='2') {
		e = mover_jogador(e,1,1);
	}
	if (acao=='3') {
		e = mover_jogador(e,0,1);	
	}
	if (acao=='4') {
		e = mover_jogador(e,-1,1);
	}
	if (acao=='5') {
		e = mover_jogador(e,-1,0);
	}
	if (acao=='6') {
		e = mover_jogador(e,-1,-1);
	}
	if (acao=='7') {
		e = mover_jogador(e,0,-1);
	}
	if (acao=='8') {
		e = mover_jogador(e,1,-1);
	}
	return e;
}

/**
\brief Função que verifica as vidas do jogador, decidindo o rumo do jogo.
@param e Estado atual do jogo.
*/
void verifica_vidas(ESTADO e) {
	if (e.vidas>0) {
		imprime_jogador(e);
		imprime_vidas(e); 
	}
	else e = fim_jogo(e);
}

/**
\brief Função que imprime todas as imagens e textos do jogo.
@param e Estado atual do jogo.
*/
void imagens(ESTADO e){
	char scorestr[MAX_BUFFER];
	char bestscorestr[MAX_BUFFER];
	int* scores = ler_scores();
	IMAGEML(750,-30,350,"logo.png");
	TEXTOS(800,335,1,"SCORE:");
	sprintf(scorestr,"%d",e.score);
	TEXTOP(800,370,1,scorestr);
	TEXTOBS(930,335,1,"BEST SCORES:");
	sprintf(bestscorestr,"%d",scores[0]);
	TEXTOP(930,370,1,bestscorestr);
	sprintf(bestscorestr,"%d",scores[1]);
	TEXTOP(930,390,1,bestscorestr);
	sprintf(bestscorestr,"%d",scores[2]);
	TEXTOP(930,410,1,bestscorestr);
	sprintf(bestscorestr,"%d",scores[3]);
	TEXTOP(930,430,1,bestscorestr);
	sprintf(bestscorestr,"%d",scores[4]);
	TEXTOP(930,450,1,bestscorestr);
	IMAGEMR(900,500,62,"reset.png");
}

/** 
\brief Função main.
*/
int main() {
	int x, y;
	srandom(time(NULL));
	ESTADO e = ler_link(getenv("QUERY_STRING"));
	
	COMECAR_HTML;
	ABRIR_SVG(1200, 650);
	for(y = 0; y < 10; y++)
		for(x = 0; x < 10; x++)
			imprime_casa(x, y);
	
	e=processa_acao(e,e.acao);
	
	imprime_inimigos(e);
	imprime_obstaculos(e);
	imprime_saida(e);
	
	verifica_vidas(e);
	escreve_estado(e);
	imagens(e);
	FECHAR_SVG;
	return 0;
}