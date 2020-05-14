%{
    
#define INIC   5
#define FIM    6
#define VIRG   7
#define pal    8
#define num    9

%}

%option noyywrap

%%

[,]             return VIRG;
(?i:inicio)     return INIC;
(?i:fim)        return FIM;
[a-zA-Z]+       return pal;
[0-9]+          return num;
.|\n            ;

%%

int main() {
    
    int proximoSimbolo;

    // Estamos a fazer uma atribuição
    // Este valor lógico é sempre verdadeiro até ao EOF
    while( (proximoSimbolo = yylex()) ) {
        printf("%d \n", proximoSimbolo);
    }

    putchar('\n');

    return 0;
}