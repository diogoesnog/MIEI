%{

    #include "y.tab.h"
    
%}

%option noyywrap

%%

[ \t\r] ;

\n      return '\n';

\+|-    { yylval.operadorExp = *yytext; return operador; }

[0-9]+  { yylval.valorInteiro = atoi(yytext); return num; }

.       return ERRO;

%%