/* Includes e Variáveis */
%{
    #include <string.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <sys/types.h>
    #include <sys/stat.h>

    int resultadoSomaAtual;
    int comecarSoma;
%}

%option noyywrap

/* Definir as Start Conditions usadas */
%x SOMA

/* Processamento dos Dados - ERs e SC */
%%

\+          {
                if(comecarSoma == 0) {comecarSoma = 1; BEGIN SOMA;}
                else {printf("Soma Atual: %i\n", resultadoSomaAtual); resultadoSomaAtual = 0; comecarSoma = 0; BEGIN INITIAL;}
            }

<SOMA>{
        \+          {BEGIN INITIAL;}

        [0-9]+      {resultadoSomaAtual = resultadoSomaAtual + atoi(yytext);}

        .|\n        {;}
    }         

.|\n        {;}

%%

/* Função Main */
int main(int argc, char* argv[]){

    resultadoSomaAtual = comecarSoma = 0;

    // Abrir o ficheiro de texto.
    yyin = fopen(argv[1], "r");

    yylex();

    return 0;
}