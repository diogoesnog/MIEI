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
%type   <valorInteiro> num ABin
 
%%

SeqABin     : SeqABin ABin              { printf("Soma Elementos = %d\n", $2); } // Aqui também estamos perante uma nova ABin 
            | ABin                      { printf("Soma Elementos = %d\n", $1); } // Isto é quando chegamos ao fim de uma ABin, logo retornamos o valor final
            ;

ABin        : '(' ')'                   { $$ = 0; } // Isto são as Ações Semânticas
            | '(' num ABin ABin ')'     { $$ = $2 + $3 + $4; } // Apenas nos interessa os valores de num, ABin e ABin
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