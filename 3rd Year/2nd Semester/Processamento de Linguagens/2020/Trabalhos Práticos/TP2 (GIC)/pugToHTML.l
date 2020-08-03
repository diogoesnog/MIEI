%{
    #include "y.tab.h"

    // Variáveis usadas para o Piped Text.
    char *pipedText;
    char *auxPipedText;
    int sizePipedText;

    // Variáveis usadas para o Id e Class de uma Div.
    char *classDivText;
    char *auxClassDivText;
    int sizeClassDivText;

    // Variável usada para controlar o número de parâmetros da Class de uma Div.
    int numberParamClassDiv = 1;
%}

%option yylineno

/* Start Conditions */
%x CONTENTTAG
%x CONTENTATTRIBUTE     ATTRIBUTETEXT 
%x CONTENTPIPEDTAG      PIPEDTEXT 
%x IDENTIFIERDIV        CLASSDIV

%%

[ ]                             ;
\n                              return *yytext;
\(                              return *yytext;
\)                              return *yytext;
\/                              return *yytext;
\'                              return *yytext;
\,                              return *yytext;
\=                              { BEGIN CONTENTTAG; return *yytext; } /* Conteúdo da Tag está entre aspas seguido do caracter '='. */

    /* Expressão Regular para extrair o Início da maioria das Tags. */
^[ ]*[a-zA-Z0-9]+               { yylval.stringValue = strdup(yytext); return beginTag; }
    
    /* Expressão Regular para extrair o Conteúdo da maioria das Tags. */
    /* Assume-se que o Pug está bem escrito. Início da Tag separado de um espaço relativamente ao Conteúdo em si. */
[ ][^\ ].*                      { yylval.stringValue = strdup(yytext+1); return contentTag; }
    
    /* Expressão Regular para extrair o Nome de um Atributo e começar a extração do Conteúdo em si. */
[ ]*[a-zA-Z]+\=/[\'|\"]         { yylval.stringValue = strdup(yytext); BEGIN CONTENTATTRIBUTE; return nameAttribute; }

    /* Expressão Regular para começar a extração de todo o Conteúdo de um Piped Text. */
\n[ ]+/\|                       { pipedText = (char*) malloc(100); sizePipedText = 100; BEGIN CONTENTPIPEDTAG; }

    /* Expressões Regulares para começar a extração do valor do Id e da Class de qualquer Div. */
    /* Primeira expressão para quando o div possui um Id. */
    /* Segunda expressão para quando o div não possui um Id. */
^[ ]*/\#                        { classDivText = (char*) malloc(100); sizeClassDivText = 100; yylval.stringValue = strdup(yytext); BEGIN IDENTIFIERDIV; return beginDiv; }
^[ ]*/\.                        { classDivText = (char*) malloc(100); sizeClassDivText = 100; yylval.stringValue = strdup(yytext); BEGIN CLASSDIV; return beginDiv; }

    /* Start Condition para extrair o Conteúdo que está entre aspas seguido do caracter '=' e um espaço. */
    /* Assume-se que possam ser as plicas e as aspas normais. */
<CONTENTTAG>{
    [ ]+[\'|\"]                     ;
    [^\'\"]*                        { yylval.stringValue = strdup(yytext); return contentTag; }
    .                               { BEGIN INITIAL; }
}

    /* Start Condition para iniciar a extração do Conteúdo de um Atributo que está entre aspas seguido do caracter '='. */
    /* Start Condition diferente da anterior. Anterior é usada para o teste de uma Tag. Esta para o texto/valor de um atributo. */
    /* Assume-se que os vários atributos possam estar separados por uma vírgula ou um espaço. */
    /* Quando se deteta uma vírgula ou um espaço volta-se ao início para o interpretador detetar um possível novo atributo. */
<CONTENTATTRIBUTE>{
    [\'|\"]                         { BEGIN ATTRIBUTETEXT; }
    \,[ ]+|[ ]+                     { BEGIN INITIAL; }
}

    /* Start Condition para extrair o Conteúdo que está entre aspas seguido do caracter '='. */
    /* Primeira expressão é para quando se deteta o caractér ','. Volta-se à SC anterior para começar um novo atributo. */
    /* Segund expressão é para quando se deteta o caractér ' '. Volta-se à SC anterior para começar um novo atributo. */
    /* Terceira expressão é para quando se deteta o caractér ')'. Sai-se da SC dado que não há mais atributos. */
<ATTRIBUTETEXT>{
    [^\'\"]*[\'|\"]/\,              { 
                                        yytext[strlen(yytext)-1]='\0'; // Para não levar a plica/aspa no yytext.
                                        
                                        yylval.stringValue = strdup(yytext); 
                                        
                                        BEGIN CONTENTATTRIBUTE; 
                                        return valueAttribute; 
                                    }
    [^\'\"]*[\'|\"]/[ ]+            { 
                                        yytext[strlen(yytext)-1]='\0'; // Para não levar a plica/aspa no yytext.
                                        
                                        yylval.stringValue = strdup(yytext); 
                                        
                                        BEGIN CONTENTATTRIBUTE; 
                                        return valueAttribute; 
                                    }
    [^\'\"]*[\'|\"]/\)              { 
                                        yytext[strlen(yytext)-1]='\0'; // Para não levar a plica/aspa no yytext.

                                        yylval.stringValue = strdup(yytext); 
                                        
                                        BEGIN INITIAL; 
                                        return valueAttribute; 
                                    }
}

    /* Start Condition para iniciar a extração do Conteúdo de um Piped Text. */
    /* Primeira expressão é para quando estamos no primeiro parágrafo de Conteúdo de Piped Text. Começa-se a SC seguinte para começar a extração. */
    /* Segunda expressão é para quando estamos nos próximos parágrafos de Conteúdo de Piped Text. Começa-se a SC seguinte para começar a extração. */
<CONTENTPIPEDTAG>{
    \|[ ]+                          { BEGIN PIPEDTEXT; }
    \n[ ]+\|/[ ]+                   { BEGIN PIPEDTEXT; }
} 

    /* Start Condition para extrair o Conteúdo de um Piped Text. */
    /* Primeira expressão é para quando ainda existem mais parágrafos de conteúdo. Volta-se à SC anterior para começar um novo parágrafo. */
    /* Segunda expressão é para quando não existem mais parágrafos de conteúdo. Sai-se da SC dado que não há mais parágrafos. */
    /* Reallocs servem para garantir que há espaço suficiente para fazer o concat dos vários parágrafos. */
<PIPEDTEXT>{
    [^\ ].*/\n[ ]+\|                {
                                        sizePipedText += strlen(yytext);
                                        auxPipedText = realloc(pipedText, sizePipedText);
                                        
                                        strcat(auxPipedText, yytext);
                                        pipedText = auxPipedText;

                                        BEGIN CONTENTPIPEDTAG; 
                                    }                            
    [^\ ].*                         {
                                        sizePipedText += strlen(yytext);
                                        auxPipedText = realloc(pipedText, sizePipedText);

                                        strcat(auxPipedText, " "); 
                                        strcat(auxPipedText, yytext);  
                                        pipedText = auxPipedText; 
                                        
                                        yylval.stringValue = strdup(pipedText); 
                                        
                                        BEGIN INITIAL; 
                                        return contentPipedTag; 
                                    }
}

    /* Start Condition para extrair o valor do Id da Div e iniciar a extração do valor da Class caso as mesmas existam. */
    /* Primeira expressão é para quando existe Class depois do ID. Começa-se SC seguinte para começar a extrair os valores da Class. */
    /* Segunda expressão é para quando não existe Class depois do ID. Volta-se ao início para se continuar o parse de novas Tags. */
<IDENTIFIERDIV>{
    [\#][^\.]*/\.                   { 
                                        yylval.stringValue = strdup(yytext+1); 
                                        
                                        BEGIN CLASSDIV; 
                                        return idDiv; 
                                    }
    [^\.\n]*                        { 
                                        yylval.stringValue = strdup(yytext+1); 
                                        BEGIN INITIAL; 
                                        return idDiv;
                                    }
}

    /* Start Condition para extrair o valor da Class. */
    /* Primeira expressão é para quando existem mais valores para a Class. Começa-se novamente esta SC para o parde do valor seguinte. */
    /* Segunda expressão é para quando não existem mais valores para a Class. Volta-se ao início para se continuar o parse de novas Tags. */
    /* Reallocs servem para garantir que há espaço suficiente para fazer o concat dos vários parágrafos. */
    /* A variável numberParamClassDiv serve para controlar o numero de parâmetros da Class da Div. Caso seja só uma, não se coloca um espaço no início da mesma. */
<CLASSDIV>{
    \.[^\.\n]*/\.                   {
                                        numberParamClassDiv++;
                                        
                                        sizeClassDivText += strlen(yytext);
                                        auxClassDivText = realloc(classDivText, sizeClassDivText);

                                        strcat(auxClassDivText, yytext+1);
                                        classDivText = auxClassDivText;

                                        yylval.stringValue = strdup(classDivText);

                                        BEGIN CLASSDIV;  
                                    }
    \.[^\.\n]*                      {
                                        sizeClassDivText += strlen(yytext);
                                        auxClassDivText = realloc(classDivText, sizeClassDivText);

                                        if(numberParamClassDiv != 1) strcat(auxClassDivText, " "); 
                                        strcat(auxClassDivText, yytext+1);
                                        classDivText = auxClassDivText;

                                        yylval.stringValue = strdup(classDivText);

                                        numberParamClassDiv = 1;
                                        BEGIN INITIAL; 
                                        return classDiv; 
                                    }
}

%%