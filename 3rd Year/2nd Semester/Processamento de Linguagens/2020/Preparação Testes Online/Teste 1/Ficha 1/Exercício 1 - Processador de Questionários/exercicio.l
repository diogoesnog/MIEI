/* Includes e Variáveis */
%{
    #include <string.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <sys/types.h>
    #include <sys/stat.h>

    char *eu;
    char *ele;
    int i;
%}

%option noyywrap

/* Definir as Start Conditions usadas */
%x EU ELE

/* Processamento dos Dados - ERs e SC */
%%
^(?i:eu)[ ]*\=[ ]*      {BEGIN EU;}

^(?i:ele)[ ]*\=[ ]*     {BEGIN ELE;}

<EU>{
    
    \..*\n              {BEGIN INITIAL;}

    [^.]+               {eu = strdup(yytext);}
}

<ELE>{
    
    \..*\n              {BEGIN INITIAL;}

    [^.]+               {ele = strdup(yytext);}
}

<*>                     {;}

^(?i:eu)[ ]*\:          {printf("%s:", eu);}

^(?i:ele)[ ]*\:         {printf("%s:", ele);}

%%

/* Função Main */
int main(int argc, char* argv[]){

    eu = ele = "";

    yyin = fopen(argv[1], "r");

    yylex();

    return 0;
}