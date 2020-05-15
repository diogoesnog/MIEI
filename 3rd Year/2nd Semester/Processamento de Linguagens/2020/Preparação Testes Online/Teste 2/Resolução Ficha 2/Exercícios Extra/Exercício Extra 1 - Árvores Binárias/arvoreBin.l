%{

    #include "y.tab.h"
    
%}

%option noyywrap

%%

[ \t\n\r]       ;

\(              return yytext[0];
\)              return *yytext;

(\-|\+)?[0-9]+  { yylval.valorInteiro = atoi(yytext); return num; }

.               return ERRO;

%%