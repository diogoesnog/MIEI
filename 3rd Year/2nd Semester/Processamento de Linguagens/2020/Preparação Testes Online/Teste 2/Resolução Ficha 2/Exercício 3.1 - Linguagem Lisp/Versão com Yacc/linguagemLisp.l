%{

    #define ABREP   1000
    #define FECHAP  1001

    #define PAL     1002
    #define NUM     1003

    // É importante sinalizar sempre o erro.
    #define ERRO    -1 

%}

%option noyywrap

%%

[ \t\n\r]+          ; // Regra de Eliminação.

\(                  return ABREP;
\)                  return FECHAP;
 
[a-zA-Z]+           return PAL;
(\+|\-)?[0-9]+       return NUM; // Colocamos a possibilidade de inserir sinal nos números.

.                   return ERRO;

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