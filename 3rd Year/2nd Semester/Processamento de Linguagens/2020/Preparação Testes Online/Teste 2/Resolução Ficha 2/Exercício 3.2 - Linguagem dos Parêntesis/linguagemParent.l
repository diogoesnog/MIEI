%{
    #define ABREP   1000
    #define FECHAP  1001

    #define ERRO    -1
%}

%option noyywrap

%%

\(      return ABREP;
\)      return FECHAP;

.       return ERRO;

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