%{

    #include <stdio.h>

    // Esta versão é de expert
    // Para ligar o Flex ao Yacc
    extern int yylex(); // ou #include <yy.lex.c>

    int yyerror();

%}

// Token são todos os símbolos terminais variáveis e com mais de um símbolo na sua constituição
// num como é um símbolo variável deve MESMO ser representado
%token ERRO DOISPONTOS num
 
%%

SeqListas   : Lista SeqListas
            |
            ;

Lista       : '[' ']'
            | '[' Elems ']'
            ;

Elems       : Elem
            | Elem ',' Elems
            | Lista
            ;

Elem        : num
            | Intervalo
            ;

Intervalo   : num DOISPONTOS num
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