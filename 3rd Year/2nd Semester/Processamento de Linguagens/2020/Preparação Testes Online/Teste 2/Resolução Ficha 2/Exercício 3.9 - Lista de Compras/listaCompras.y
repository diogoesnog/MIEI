%{

    #include <stdio.h>

    // Esta versão é de expert
    // Para ligar o Flex ao Yacc
    extern int yylex(); // ou #include <yy.lex.c>

    int yyerror();

%}

// Token são todos os símbolos terminais variáveis e com mais de um símbolo na sua constituição
// num como é um símbolo variável deve MESMO ser representado
%token ERRO
%token numInt numFloat pal
%token unidade peso volume
 
%%

ListaCompras    : ListaCompras Seccao
                | Seccao
                ;

Seccao          : pal ':' Itens
                ;

Itens           : Itens Item
                | Item
                ;

Item            : '(' numInt ',' pal ',' numFloat ',' Quantidade ')'
                ;

Quantidade      : '['   unidade   ':'   numInt      ']'
                | '['   peso      ':'   numInt      ']'
                | '['   peso      ':'   numFloat    ']'
                | '['   volume    ':'   numInt      ']'
                | '['   volume    ':'   numFloat    ']'
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