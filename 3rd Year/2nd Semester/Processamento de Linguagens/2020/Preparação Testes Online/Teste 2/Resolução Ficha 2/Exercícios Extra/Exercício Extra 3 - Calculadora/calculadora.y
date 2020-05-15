%{

    #include <stdio.h>

    // Esta versão é de expert
    // Para ligar o Flex ao Yacc
    extern int yylex(); // ou #include <yy.lex.c>

    int yyerror();

%}

%union {

    int valorInteiro;

}

// Token são todos os símbolos terminais variáveis e com mais de um símbolo na sua constituição
%token  ERRO num
%type <valorInteiro> num Calculadora Expressao Termo Fator
 
%%

Calculadora : Expressao '\n'        { printf("Valor = %d\n", $1); }
            ;

Expressao   : Termo                 { $$ = $1; }
            | Expressao '+' Termo   { $$ = $1 + $3; }
            | Expressao '-' Termo   { $$ = $1 - $3; }
            ;

Termo       : Fator                 { $$ = $1; }
            | Termo '*' Fator       { $$ = $1 * $3; }
            | Termo '/' Fator       { if($3) $$ = $1 / $3; else yyerror(); }
            ;

Fator       : num                   { $$ = $1; }
            | '(' Expressao ')'     { $$ = $2; }
            ;

%%

int main() {

    yyparse();

    return 0;
}

int yyerror() {
    
    printf("Erro Sintático.\n");

    return 0;
}