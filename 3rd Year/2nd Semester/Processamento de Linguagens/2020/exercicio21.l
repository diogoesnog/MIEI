%{
#define INIC   5
#define FIM    6
#define VIRG   7
#define pal    8
#define num    9
%}

%option noyywrap

%%

[,]             return VIRG;
(?i:inicio)     return INIC;
(?i:fim)        return FIM;
[a-zA-Z]+       return pal;
[0-9]+          return num;
.|\n            ;

%%