%{

    #include <stdio.h>

    // Esta versão é de expert
    // Para ligar o Flex ao Yacc
    extern int yylex(); // ou #include <yy.lex.c>

    int yyerror();

%}

%union {

    int     valorInteiro;
    char    operadorExp;

}

// Token são todos os símbolos terminais variáveis e com mais de um símbolo na sua constituição
%token  ERRO num operador 
%type <valorInteiro> num ExpAritm
%type <operadorExp>  operador
 
%%

SeqExpAritm     : SeqExpAritm '\n' ExpAritm         { printf("Valor Soma = %d\n", $3); }
                | ExpAritm                          { printf("Valor Soma = %d\n", $1); }
                ;


ExpAritm        : ExpAritm operador num             {
                                                        if(strcmp(&$2, "+") == 0) $$ = $1 + $3;
                                                        if(strcmp(&$2, "-") == 0) $$ = $1 - $3;
                                                    }     
                | num                               { $$ = $1; }
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