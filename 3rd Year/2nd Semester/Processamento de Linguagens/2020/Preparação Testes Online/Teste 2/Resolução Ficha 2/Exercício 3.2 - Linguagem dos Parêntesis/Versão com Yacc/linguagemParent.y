%{

    #include <stdio.h>

    // Esta versão é de expert
    // Para ligar o Flex ao Yacc
    extern int yylex(); // ou #include <yy.lex.c>

    int yyerror();

%}

// O vazio não é um token, representa ausência de derivação
// O ERRO é um extra à linguagem mas deve ser sempre considerado
// O ERRO é símbolo terminal VARIÁVEL
// Os símbolos terminais '(' e ')' como são apenas constituídos por um símbolo, não viram Token
%token ERRO

%%

Parentesis  : '(' Parentesis ')' Parentesis
            | 
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