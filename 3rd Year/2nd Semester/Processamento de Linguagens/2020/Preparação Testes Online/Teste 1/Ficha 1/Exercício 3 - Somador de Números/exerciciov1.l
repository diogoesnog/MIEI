/* Includes e Variáveis */
%{
    #include <string.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <sys/types.h>
    #include <sys/stat.h>

    int resultadoSomaAtual;
%}

%option noyywrap

/* Definir as Start Conditions usadas */

/* Processamento dos Dados - ERs e SC */
%%

\=          {
                printf("Soma Atual: %i\n", resultadoSomaAtual);
                resultadoSomaAtual = 0;
            }
            
[0-9]+      {resultadoSomaAtual = resultadoSomaAtual + atoi(yytext);}


.|\n        {;}

%%

/* Função Main */
int main(int argc, char* argv[]){

    resultadoSomaAtual = 0;

    // Abrir o ficheiro de texto.
    yyin = fopen(argv[1], "r");

    yylex();

    return 0;
}