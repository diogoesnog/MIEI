%{
    #include <stdio.h>
    #include <string.h>

    extern int yylex();
    extern int yylineno;
    extern char* yytext;

    int yyerror();
    int erroSem(char *string);
%}

%union {
    int  numberValue;
    char carValue;
}

%token ERRO HALT PRINT READ SHOW SEPARADOR
%token <numberValue>    number
%token <carValue>       id

%type <numberValue>     Expressao Termo Fator

%%

Calculator      : { printf("\tpushn 26\nstart\n"); } ListaComandos { printf("stop\n"); }
                ;

ListaComandos   : ListaComandos Comando
                | Comando
                ;

Comando         : Print
                | Read
                | Show
                | Atribuicao
                ;

Print           : PRINT Expressao SEPARADOR             { 
                                                            printf("\twritei\n"); 
                                                            printf("\tpushs \"\\n\"\n");
                                                            printf("\twrites\n");
                                                        }
                ;

Read            : READ id SEPARADOR                     { 
                                                            printf("\tpushs \"Introduza um valor: \"\n");
                                                            printf("\twrites\n");
                                                            printf("\tread\n");
                                                            printf("\tatoi\n");
                                                            printf("\tstoreg %d\n", $2-'a');
                                                        }
                ;

Show            : SHOW SEPARADOR                        { 
                                                            for(int i = 0; i<26; i++) 
                                                                printf("\tpushg %d\n\twritei\n", i);
                                                                printf("\tpushs \", \"\n");
                                                                printf("\twrites\n");     
                                                        }
                ;

Atribuicao      : id '=' Expressao SEPARADOR            { printf("\tstoreg %d\n", $1-'a'); }
                ;

Expressao       : Expressao '+' Termo                   { printf("\tadd\n"); }
                | Expressao '-' Termo                   { printf("\tsub\n"); }
                | Termo
                ;

Termo           : Termo '/' Fator                       { 
                                                                if($3 != 0) printf("\tdiv\n");
                                                                else erroSem("Divisão por 0.\n"); 
                                                        }
                | Termo '*' Fator                       { printf("\tmul\n"); }
                | Fator
                ;

Fator           : id                                    { printf("\tpushg %d\n", $1-'a'); }
                | number                                { printf("\tpushi %d\n", $1); }
                | '(' Expressao ')'
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