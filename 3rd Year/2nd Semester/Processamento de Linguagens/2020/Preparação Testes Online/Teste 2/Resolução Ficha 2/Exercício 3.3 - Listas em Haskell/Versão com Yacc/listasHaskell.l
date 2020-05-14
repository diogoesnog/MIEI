%{

    #include "y.tab.h"
    
%}

%option noyywrap

%%

[ \t\n\r]       ;

\[              return *yytext;
\]              return *yytext;
,               return *yytext;

\.\.            return DOISPONTOS;

(\-|\+)?[0-9]+  return num;

.               return ERRO;

%%