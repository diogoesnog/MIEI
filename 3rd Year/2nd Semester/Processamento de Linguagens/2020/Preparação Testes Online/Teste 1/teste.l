/* Includes e Variáveis */
%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    char *name;

%}

%option noyywrap

/* Definir as Start Conditions usadas */


/* Processamento dos Dados - ERs e SC */
%%

\+/[]*[a-zA-Z]    {printf("\item ");}
\+/"---"        {printf("\% ");}
\+[0-9]+   {printf("%s", yytext+1);}

%%

/* Função Main */
int main(int argc, char* argv[]){

    name = "Diogo";
    // Abrir o ficheiro de texto.
    yyin = fopen(argv[1], "r");

    yylex();

    return 0;
}