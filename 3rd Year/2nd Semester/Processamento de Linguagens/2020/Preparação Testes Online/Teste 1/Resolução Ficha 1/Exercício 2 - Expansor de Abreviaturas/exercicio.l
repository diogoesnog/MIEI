/* Includes e Variáveis */
%{
    #include <string.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <sys/types.h>
    #include <sys/stat.h>

%}

%option noyywrap

/* Definir as Start Conditions usadas */
%x 

/* Processamento dos Dados - ERs e SC */
%%

%%

/* Função Main */
int main(int argc, char* argv[]){

    // Abrir o ficheiro de texto.
    yyin = fopen(argv[1], "r");

    yylex();

    return 0;
}