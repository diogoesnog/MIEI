%{

    #include "y.tab.h"
    
%}

%option noyywrap

%%

[ \t\n\r]           ;

unidade             return unidade;
peso                return peso;
volume              return volume;

[()\[\].:,]         return *yytext;

[a-zA-Z]+           return pal;
[0-9]+              return numInt;
[0-9]+\.[0-9]+      return numFloat;

.                   return ERRO;

%%