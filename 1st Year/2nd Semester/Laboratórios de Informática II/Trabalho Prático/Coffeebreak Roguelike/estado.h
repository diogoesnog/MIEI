#ifndef ___ESTADO_H___
#define ___ESTADO_H___

/**
@file estado.h
@brief Definição do estado e das funções que convertem estados em strings e vice-versa.
*/

/** 
\brief O nº máximo de inimigos. 
*/
#define MAX_INIMIGOS		100

/** 
\brief O nº máximo de obstáculos. 
*/
#define MAX_OBSTACULOS		100

/**
\brief Estrutura que armazena uma posição.
*/
typedef struct posicao {
	char x;
	char y;
} POSICAO;

/**
\brief Estrutura que armazena o estado do jogo.
*/
typedef struct estado {
	/** A posição do jogador. */
	POSICAO jog;
	/** O nº de inimigos. */
	char num_inimigos;
	/** O nº de obstáculos. */
	char num_obstaculos;
	/** Array com a posição dos inimigos. */
	POSICAO inimigo[MAX_INIMIGOS];
	/** Array com a posição dos obstáculos. */
	POSICAO obstaculo[MAX_OBSTACULOS];
	/** Array com a posição da saída. */
	POSICAO saida;
	/** Score. */
	int score;
	/** Best Score. */
	int bestscore;
	/** Ações. */
	char acao;
	/** Vidas. */
	int vidas;
	/** Nome Jogador. */
	char *nome;

} ESTADO;

/**
\brief Função que converte um estado numa string
@param e O estado
@returns A string correspondente ao estado e
*/
char *estado2str(ESTADO e);

/**
\brief Função que converte uma string num estado 
@param argumentos Uma string contendo os argumentos passados à CGI
@returns O estado correspondente à string dos argumentos
*/
ESTADO str2estado(char *argumentos);

#endif