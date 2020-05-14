%{

    #define ABREP       1000
    #define FECHAP      1001
    #define VIRG        1002
    #define DOISPONTOS  1003

    #define num         1004

    #define ERRO    -1
    
%}

%option noyywrap

%%

\[              return ABREP;
\]              return FECHAP;
,               return VIRG;
\.\.            return DOISPONTOS;
(\-|\+)?[0-9]+  return num;

.               return ERRO;

%%

int main() {

    int proximoSimbolo;

    // Estamos a fazer uma atribuição
    // Este valor lógico é sempre verdadeiro até ao EOF
    while( (proximoSimbolo = yylex()) ) {
        printf("%d ", proximoSimbolo);
    }

    putchar('\n');

    return 0;

}