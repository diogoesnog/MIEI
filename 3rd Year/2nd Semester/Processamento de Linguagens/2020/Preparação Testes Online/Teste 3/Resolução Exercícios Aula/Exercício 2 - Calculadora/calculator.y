%{
    #include <stdio.h>
    #include <string.h>
    #include "read.h"

    extern int yylex();
    extern int yylineno;
    extern char* yytext;

    int tabSimbolos[26] = {0};
    int yyerror();
%}

%union {
    int  numberValue;
    char carValue;
}

%token HALT PRINT READ SHOW SEPARADOR
%token ERRO number id

%type <numberValue>     number Expressao Termo Fator
%type <carValue>        id

%%

Calculator      : ListaComandos
                ;

ListaComandos   : ListaComandos Comando         { printf("Reconheci um comando.\n"); }
                | Comando                       { printf("Reconheci um comando.\n"); }
                ;

Comando         : Print
                | Read
                | Show
                | Halt
                | Atribuicao
                ;

Print           : PRINT Expressao SEPARADOR             { printf(">> %d\n", $2); }
                ;

Read            : READ id SEPARADOR                     {
                                                                tabSimbolos[$2-'a'] = readInt();
                                                                printf(">> %c: %d\n", $2, tabSimbolos[$2-'a']);
                                                        }
                ;

Show            : SHOW SEPARADOR                        { 
                                                                for(int i = 0; i<26; i++) 
                                                                        if(tabSimbolos[i] != 0) printf(">> %c: %d\n", i+'a', tabSimbolos[i]); 
                                                        }
                ;

Halt            : HALT SEPARADOR                        { 
                                                                printf(">> Até à próxima.\n"); 
                                                                return 0; 
                                                        }
                ;

Atribuicao      : id '=' Expressao SEPARADOR            { 
                                                                tabSimbolos[$1-'a'] = $3; 
                                                                printf(">> %c: %d\n", $1, $3); 
                                                        }
                ;

Expressao       : Expressao '+' Termo                   { $$ = $1+$3; }
                | Expressao '-' Termo                   { $$ = $1-$3; }
                | Termo                                 { $$ = $1; }
                ;

Termo           : Termo '/' Fator                       { 
                                                                if($3 != 0) $$ = $1/$3; 
                                                                else erroSem("Divisão por 0.\n"); 
                                                        }
                | Termo '*' Fator                       { $$ = $1*$3; }
                | Fator                                 { $$ = $1; }
                ;

Fator           : id                                    { $$ = tabSimbolos[$1-'a']; }
                | number                                { $$ = $1; }
                | '(' Expressao ')'                     { $$ = $2; }
                ;

%%

int main() {
    yyparse();

    return 0;
}

int erroSem(char *s) {
        printf("Erro Semântico na linha: %d: %s\n", yylineno, s);

        return 0;
}

int yyerror() {
    printf("Erro Sintático ou Léxico na linha: %d com o texto: %s\n", yylineno, yytext);

    return 0;
}