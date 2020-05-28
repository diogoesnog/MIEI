%{
    #include <stdio.h>
    #include <string.h>
    extern int yylex();
    extern int yylineno;
    int yyerror();
    int numAlunos = 0;
%}

%union {
    char *stringValue;
}

%token DECLINICIAL ABREALUNOS FECHAALUNOS ABREALUNO FECHAALUNO
%token ABREID FECHAID ABRENOME FECHANOME ABRENOTA FECHANOTA
%token ABREUC FECHAUC ABREVALOR FECHAVALOR ABRENOTAS FECHANOTAS
%token string ERRO

%type <stringValue> string Alunos Aluno Id Nome Notas Nota Uc Valor

%%

Turma   : DECLINICIAL ABREALUNOS Alunos FECHAALUNOS                 { printf("%s\n", $3); }
        ;

Alunos  : Alunos Aluno                                              { asprintf(&$$, "%s\n%s", $1, $2); }
        |
        ;

Aluno   : ABREALUNO Id Nome ABRENOTAS Notas FECHANOTAS FECHAALUNO   { numAlunos++; asprintf(&$$, "%s,%s,%s", $2, $3, $5); }
        ;

Id      : ABREID string FECHAID                                     { asprintf(&$$, "%s", $2); }
        ;

Nome    : ABRENOME string FECHANOME                                 { asprintf(&$$, "%s", $2); }
        ;

Notas   : Notas Nota                                                { asprintf(&$$, "%s,%s", $1, $2); }
        |
        ;

Nota    : ABRENOTA Uc Valor FECHANOTA                               { asprintf(&$$, "%s,%s", $2, $3); }
        ;

Uc      : ABREUC string FECHAUC                                     { asprintf(&$$, "%s", $2); }
        ;

Valor   : ABREVALOR string FECHAVALOR                               { asprintf(&$$, "%s", $2); }
        ;

%%

int main() {
    yyparse();

    return 0;
}

int yyerror() {
    printf("Erro Sintático ou Léxico na linha: %d\n", yylineno);

    return 0;
}