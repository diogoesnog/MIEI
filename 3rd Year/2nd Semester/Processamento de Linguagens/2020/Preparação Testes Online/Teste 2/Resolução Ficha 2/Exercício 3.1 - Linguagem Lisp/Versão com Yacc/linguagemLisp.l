%{

    #include "y.tab.h"

%}

%option noyywrap

%%

[ \t\n\r]+          ; // Regra de Eliminação.

\(                  return *yytext;
\)                  return *yytext;

[0-9]+              return num;
[a-zA-Z]+           return pal;

.                   return ERRO;

%%
