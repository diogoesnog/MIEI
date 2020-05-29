%{
    #include "y.tab.h"
%}

%option yylineno

%%

[ \t\r\n]                 ;

;                       return SEPARADOR;

[+*\-/=()]              return *yytext;

(?i:halt)               return HALT;
(?i:print)              return PRINT;
(?i:read)               return READ;
(?i:show)               return SHOW;

[0-9]+                  { yylval.numberValue = atoi(yytext); return number; }
[a-z]                   { yylval.carValue = *yytext; return id; }
\/\/.*                  { yylval.commentValue = strdup(yytext+2); return comment; }
\"[^"]*\"               { yyext[yyleng-1] = '\0'; yylval.stringValue = strdup(yytext+1); return string; }

.                       return ERRO; 


