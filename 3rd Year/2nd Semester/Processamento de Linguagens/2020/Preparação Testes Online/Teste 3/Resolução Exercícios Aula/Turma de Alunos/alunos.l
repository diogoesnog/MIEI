%{
    #include "y.tab.h"
%}

%option yylineno

%x TEXTO

%%

[ \t\n\r]               ;

\<\?xml[^?]+\?\>        return DECLINICIAL;
\<alunos\>              return ABREALUNOS;
\<\/alunos\>            return FECHAALUNOS;
\<aluno\>               return ABREALUNO;
\<\/aluno\>             return FECHAALUNO;
\<id\>                  { BEGIN TEXTO; return ABREID; }
\<\/id\>                return FECHAID;
\<nome\>                { BEGIN TEXTO; return ABRENOME; }
\<\/nome\>              return FECHANOME;
\<notas\>               return ABRENOTAS;
\<\/notas\>             return FECHANOTAS;
\<nota\>                return ABRENOTA;
\<\/nota\>              return FECHANOTA;
\<uc\>                  { BEGIN TEXTO; return ABREUC; }
\<\/uc\>                return FECHAUC;
\<valor\>               { BEGIN TEXTO; return ABREVALOR; }
\<\/valor\>             return FECHAVALOR;

<TEXTO>[^<]+            { BEGIN INITIAL; yylval.stringValue = strdup(yytext); return string; }

.                       return ERRO; 


