%{

    #include "y.tab.h"
    
%}

%option noyywrap

%%

[ \t\r]                     ;

\n                          return '\n';

[()*\/\-+]                  return *yytext;

[0-9]+                      { yylval.valorInteiro = atoi(yytext); return num; }

.                           return ERRO;

%%