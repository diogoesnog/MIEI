/**
@file ficheiro.h
@brief Um header com as funções necessárias para leitura e escrita em ficheiro de texto.
*/

#include <stdio.h>

/**
\brief Função que escreve o estado num ficheiro de texto.
@param e Estado recebido para ser escrito.
*/
void escreve_estado(ESTADO e) {
    FILE * fp;
    fp=fopen("/var/www/html/files/state.txt","w");
    fprintf(fp,"%s",estado2str(e));
    fclose(fp);
}

/**
\brief Função que lê o estado dum ficheiro de texto.
@returns Estado lido no ficheiro.
*/
ESTADO ler_ficheiro() {
    char str[10000];
    FILE * fp;
    fp=fopen("/var/www/html/files/state.txt","r");

    if  (fp == NULL) {
        //perror("Não existe ficheiro");
        //exit(1);
        ESTADO nada = {0};
        return nada;
    }
    else {
    if(fscanf(fp,"%s",str)){}; // colocado num if para eliminar o warning do fscanf
    ESTADO novo = str2estado(str);
    fclose(fp);
    return novo;
    }
}