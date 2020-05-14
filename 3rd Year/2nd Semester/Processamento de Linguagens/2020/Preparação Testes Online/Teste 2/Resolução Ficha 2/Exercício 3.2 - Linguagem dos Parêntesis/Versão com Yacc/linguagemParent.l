%{
    #include "y.tab.h"
%}

%option noyywrap

%%

[ \t\n\r]   ;

\(          return yytext[0]; //Ou *yytext
\)          return yytext[0];

.           return ERRO;

%%