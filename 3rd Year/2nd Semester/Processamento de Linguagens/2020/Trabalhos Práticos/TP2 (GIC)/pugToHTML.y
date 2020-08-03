%{
    #define _GNU_SOURCE

    #include <stdio.h>
    #include <string.h>

    #include "funcoesAux.c"
    #include "funcoesAux.h"
    #include "structTags.h"

    extern int yylex();
    extern int yylineno;
    extern char* yytext;

    int yyerror();

    int numberSpaces = 0;
    char *openingTagWSpaces;
    char *closingTagWSpaces;
    char *openingTagWClosedTags;
    char *tagDiv;

    Tags *listTags;
%}

%union {    
    char *stringValue;
}

// Apenas são Tokens os Símbolos Terminais (Variáveis e Não Variáveis)
%token beginTag contentTag 
%token contentPipedTag
%token beginDiv idDiv classDiv 
%token nameAttribute valueAttribute

%type <stringValue> ContentPugFile
%type <stringValue> Tags Tag TagDefault TagAttribute TagSelfClosing TagPiped TagDiv
%type <stringValue> AttributeHandler Attributes Attribute
%type <stringValue> beginTag contentTag contentPipedTag beginDiv idDiv classDiv nameAttribute valueAttribute

%%

PugFile             :   ContentPugFile                                  {
                                                                            printf("%s", $1);
                                                                            printFinalClosingTags(listTags);
                                                                        }
                    ;

ContentPugFile      :   Tags                                            { asprintf(&$$, "%s", $1); }
                    ;

Tags                :   Tag '\n' Tags                                   { asprintf(&$$, "%s\n%s", $1, $3); }
                    |   Tag                                             { asprintf(&$$, "%s", $1); }
                    ;

Tag                 :   TagDefault                                      { asprintf(&$$, "%s", $1); }
                    |   TagAttribute                                    { asprintf(&$$, "%s", $1); }
                    |   TagSelfClosing                                  { asprintf(&$$, "%s", $1); }
                    |   TagPiped                                        { asprintf(&$$, "%s", $1); }
                    |   TagDiv                                          { asprintf(&$$, "%s", $1); }
                    ;

TagDefault          :   beginTag                                        { 
                                                                            // Verificar se consiste numa Tag 'img', 'meta' ou 'link'.
                                                                            // Estas Tags são assim tratadas como Self Closing.
                                                                            if(isAutoSelfClosing($1) == 1){
                                                                                numberSpaces = countInitialSpaces($1);
                                                                                openingTagWSpaces = tagWithSpaces($1, 1, 3, numberSpaces);

                                                                                listTags = insertTag(listTags, openingTagWClosedTags, numberSpaces);
                                                                                openingTagWClosedTags = newInitialTag(listTags, openingTagWSpaces, numberSpaces);
                                                                                listTags = removeClosedTags(listTags, numberSpaces);
                                                                                listTags = removeFirstTag(listTags);
                                                                                
                                                                                asprintf(&$$, "%s />", openingTagWClosedTags); 
                                                                            }

                                                                            // Caso contrário, trata-se como uma Tag normal.
                                                                            else{
                                                                                numberSpaces = countInitialSpaces($1);
                                                                                openingTagWSpaces = tagWithSpaces($1, 1, 2, numberSpaces);
                                                                                closingTagWSpaces = tagWithSpaces($1, 0, 2, numberSpaces);
                                                                                
                                                                                listTags = insertTag(listTags, closingTagWSpaces, numberSpaces);
                                                                                openingTagWClosedTags = newInitialTag(listTags, openingTagWSpaces, numberSpaces);
                                                                                listTags = removeClosedTags(listTags, numberSpaces);

                                                                                asprintf(&$$, "%s", openingTagWClosedTags);
                                                                            }
                                                                        }   
                    |   beginTag contentTag                             { 
                                                                            numberSpaces = countInitialSpaces($1);
                                                                            openingTagWSpaces = tagWithSpaces($1, 1, 2, numberSpaces);
                                                                            closingTagWSpaces = tagWithSpaces($1, 0, 2, numberSpaces);
                                                                            
                                                                            listTags = insertTag(listTags, closingTagWSpaces, numberSpaces);
                                                                            openingTagWClosedTags = newInitialTag(listTags, openingTagWSpaces, numberSpaces);
                                                                            listTags = removeClosedTags(listTags, numberSpaces);

                                                                            asprintf(&$$, "%s%s", openingTagWClosedTags, $2);
                                                                        }
                    |   beginTag '=' contentTag                         {
                                                                            numberSpaces = countInitialSpaces($1);
                                                                            openingTagWSpaces = tagWithSpaces($1, 1, 2, numberSpaces);
                                                                            closingTagWSpaces = tagWithSpaces($1, 0, 2, numberSpaces);
                                                                            
                                                                            listTags = insertTag(listTags, closingTagWSpaces, numberSpaces);
                                                                            openingTagWClosedTags = newInitialTag(listTags, openingTagWSpaces, numberSpaces);
                                                                            listTags = removeClosedTags(listTags, numberSpaces); 
                                                                            
                                                                            asprintf(&$$, "%s%s", openingTagWClosedTags, $3); 
                                                                        }
                    ;

TagAttribute        :   beginTag AttributeHandler                       {
                                                                            // Verificar se consiste numa Tag 'img', 'meta' ou 'link'.
                                                                            // Estas Tags são assim tratadas como Self Closing.
                                                                            if(isAutoSelfClosing($1) == 1){
                                                                                numberSpaces = countInitialSpaces($1);
                                                                                openingTagWSpaces = tagWithSpaces($1, 1, 3, numberSpaces);

                                                                                listTags = insertTag(listTags, openingTagWClosedTags, numberSpaces);
                                                                                openingTagWClosedTags = newInitialTag(listTags, openingTagWSpaces, numberSpaces);
                                                                                listTags = removeClosedTags(listTags, numberSpaces);
                                                                                listTags = removeFirstTag(listTags);

                                                                                asprintf(&$$, "%s %s />", openingTagWClosedTags, $2); 
                                                                            }

                                                                            // Caso contrário, trata-se como uma Tag normal.
                                                                            else{ 
                                                                                numberSpaces = countInitialSpaces($1);
                                                                                openingTagWSpaces = tagWithSpaces($1, 1, 3, numberSpaces);
                                                                                closingTagWSpaces = tagWithSpaces($1, 0, 3, numberSpaces);
                                                                                
                                                                                listTags = insertTag(listTags, closingTagWSpaces, numberSpaces);
                                                                                openingTagWClosedTags = newInitialTag(listTags, openingTagWSpaces, numberSpaces);
                                                                                listTags = removeClosedTags(listTags, numberSpaces);

                                                                                asprintf(&$$, "%s %s>", openingTagWClosedTags, $2);
                                                                            }
                                                                        }   
                    |   beginTag AttributeHandler contentTag            { 
                                                                            numberSpaces = countInitialSpaces($1);
                                                                            openingTagWSpaces = tagWithSpaces($1, 1, 3, numberSpaces);
                                                                            closingTagWSpaces = tagWithSpaces($1, 0, 3, numberSpaces);
                                                                            
                                                                            listTags = insertTag(listTags, closingTagWSpaces, numberSpaces);
                                                                            openingTagWClosedTags = newInitialTag(listTags, openingTagWSpaces, numberSpaces);
                                                                            listTags = removeClosedTags(listTags, numberSpaces);
                                                                            
                                                                            asprintf(&$$, "%s %s>%s", openingTagWClosedTags, $2, $3); 
                                                                        }
                    |   beginTag AttributeHandler '=' contentTag        { 
                                                                            numberSpaces = countInitialSpaces($1);
                                                                            openingTagWSpaces = tagWithSpaces($1, 1, 3, numberSpaces);
                                                                            closingTagWSpaces = tagWithSpaces($1, 0, 3, numberSpaces);
                                                                            
                                                                            listTags = insertTag(listTags, closingTagWSpaces, numberSpaces);
                                                                            openingTagWClosedTags = newInitialTag(listTags, openingTagWSpaces, numberSpaces);
                                                                            listTags = removeClosedTags(listTags, numberSpaces);

                                                                            asprintf(&$$, "%s %s>%s", openingTagWClosedTags, $2, $4); 
                                                                        }
                    ;

TagSelfClosing      :   beginTag '/'                                    { 
                                                                            numberSpaces = countInitialSpaces($1);
                                                                            openingTagWSpaces = tagWithSpaces($1, 1, 4, numberSpaces);

                                                                            listTags = insertTag(listTags, closingTagWSpaces, numberSpaces);
                                                                            openingTagWClosedTags = newInitialTag(listTags, openingTagWSpaces, numberSpaces);
                                                                            listTags = removeClosedTags(listTags, numberSpaces);
                                                                            listTags = removeFirstTag(listTags);
                                                                            
                                                                            asprintf(&$$, "%s", openingTagWClosedTags); 
                                                                        }
                    |   beginTag AttributeHandler '/'                   {
                                                                            numberSpaces = countInitialSpaces($1);
                                                                            openingTagWSpaces = tagWithSpaces($1, 1, 3, numberSpaces);

                                                                            listTags = insertTag(listTags, closingTagWSpaces, numberSpaces);
                                                                            openingTagWClosedTags = newInitialTag(listTags, openingTagWSpaces, numberSpaces);
                                                                            listTags = removeClosedTags(listTags, numberSpaces);
                                                                            listTags = removeFirstTag(listTags);
                                                                            
                                                                            asprintf(&$$, "%s %s />", openingTagWClosedTags, $2); 
                                                                        }
                    ;

TagPiped            :   beginTag contentPipedTag                        { 
                                                                            numberSpaces = countInitialSpaces($1);
                                                                            openingTagWSpaces = tagWithSpaces($1, 1, 2, numberSpaces);
                                                                            closingTagWSpaces = tagWithSpaces($1, 0, 2, numberSpaces);

                                                                            listTags = insertTag(listTags, closingTagWSpaces, numberSpaces);
                                                                            openingTagWClosedTags = newInitialTag(listTags, openingTagWSpaces, numberSpaces);
                                                                            listTags = removeClosedTags(listTags, numberSpaces);

                                                                            asprintf(&$$, "%s%s", openingTagWClosedTags, $2); 
                                                                        }
                    ;

TagDiv              : beginDiv idDiv classDiv                           {
                                                                            tagDiv = strdup($1);
                                                                            strcat(tagDiv, "div");

                                                                            numberSpaces = countInitialSpaces(tagDiv);
                                                                            openingTagWSpaces = tagWithSpaces(tagDiv, 1, 3, numberSpaces);
                                                                            closingTagWSpaces = tagWithSpaces(tagDiv, 0, 3, numberSpaces);
                                                                            
                                                                            listTags = insertTag(listTags, closingTagWSpaces, numberSpaces);
                                                                            openingTagWClosedTags = newInitialTag(listTags, openingTagWSpaces, numberSpaces);
                                                                            listTags = removeClosedTags(listTags, numberSpaces);

                                                                            asprintf(&$$, "%s id=\"%s\" class=\"%s\">", openingTagWClosedTags, $2, $3);                                                                            
                                                                        }
                    |   beginDiv idDiv                                  { 
                                                                            tagDiv = strdup($1);
                                                                            strcat(tagDiv, "div");

                                                                            numberSpaces = countInitialSpaces(tagDiv);
                                                                            openingTagWSpaces = tagWithSpaces(tagDiv, 1, 3, numberSpaces);
                                                                            closingTagWSpaces = tagWithSpaces(tagDiv, 0, 3, numberSpaces);
                                                                            
                                                                            listTags = insertTag(listTags, closingTagWSpaces, numberSpaces);
                                                                            openingTagWClosedTags = newInitialTag(listTags, openingTagWSpaces, numberSpaces);
                                                                            listTags = removeClosedTags(listTags, numberSpaces);

                                                                            asprintf(&$$, "%s id=\"%s\">", openingTagWClosedTags, $2);                                                                           
                                                                        }
                    |   beginDiv classDiv                               {
                                                                            tagDiv = strdup($1);
                                                                            strcat(tagDiv, "div");

                                                                            numberSpaces = countInitialSpaces(tagDiv);
                                                                            openingTagWSpaces = tagWithSpaces(tagDiv, 1, 3, numberSpaces);
                                                                            closingTagWSpaces = tagWithSpaces(tagDiv, 0, 3, numberSpaces);
                                                                            
                                                                            listTags = insertTag(listTags, closingTagWSpaces, numberSpaces);
                                                                            openingTagWClosedTags = newInitialTag(listTags, openingTagWSpaces, numberSpaces);
                                                                            listTags = removeClosedTags(listTags, numberSpaces);

                                                                            asprintf(&$$, "%s class=\"%s\">", openingTagWClosedTags, $2);
                                                                        }
                    ;

AttributeHandler    :   '(' Attributes ')'                              { asprintf(&$$, "%s", $2); }
                    ;

Attributes          :   Attributes Attribute                            { asprintf(&$$, "%s %s", $1, $2); }
                    |   Attribute                                       { asprintf(&$$, "%s", $1); }   
                    ;

Attribute           :   nameAttribute valueAttribute                    { asprintf(&$$, "%s\"%s\"", $1, $2); }
                    ;

%%

int main() {

    // Initializate Linked List of all Tags
    listTags = init();

    yyparse();

    return 0;
}

int yyerror() {
    
    printf("Erro Sintático ou Léxico na linha: %d com o texto: %s\n", yylineno, yytext);
    return 0;
}