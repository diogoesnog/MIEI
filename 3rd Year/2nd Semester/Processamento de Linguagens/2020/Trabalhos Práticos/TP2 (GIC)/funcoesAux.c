#include <stdio.h>
#include <string.h>

#include "funcoesAux.h"

// Função que verifica se estamos perante uma Tag Automatically Self Closing.
// Assumem-se como Automatically Sel Closing Tags as 'img', 'link' e 'meta'.
int isAutoSelfClosing(char *text)
{
    if (strstr(text, "img") != NULL || strstr(text, "link") != NULL || strstr(text, "meta") != NULL)
        return 1;
    else
        return 0;
}

// Função que conta o número de espaços que da Tag fazem parte.
// Conta apenas os espaços iniciais. Quando deteta o primeiro caracter que não o espaço, devolve o resultado.
int countInitialSpaces(char *text)
{
    int numberSpaces = 0;

    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == ' ')
            numberSpaces++;
        else
            return numberSpaces;
    }
}

// Função que trata de escrever as Opening e Closing Tags já com os devidos espaços iniciais.
char *tagWithSpaces(char *text, int openingOrClosing, int typeTag, int numberSpaces)
{
    char *tag;
    char *spaces;

    // Caso seja uma Tag de Abertura.
    if (openingOrClosing == isOpening)
        tag = strdup("<");
    // Caso seja uma Tag de Fecho.
    else
        tag = strdup("</");

    // Caso a Tag tenha pelo menos um espaço.
    if (numberSpaces != 0)
    {
        spaces = strdup(" ");

        for (int i = 1; text[i] != '\0'; i++)
        {
            // Concatenação dos Espaços
            if (text[i] == ' ')
                strcat(spaces, strdup(" "));
            // Concatenação dos Espaços com o nome da Tag em si
            else
            {
                strcat(tag, &text[i]);
                // Caso seja uma Tag Default ou uma Tag Atributo de Fecho 
                if (typeTag == defaultTag || (typeTag == attributeTag && openingOrClosing == isClosing))
                {
                    strcat(tag, ">");
                    return strcat(spaces, tag);
                }
                // Caso seja uma Tag Self Closing
                else if (typeTag == selfClosingTag)
                {
                    strcat(tag, " />");
                    return strcat(spaces, tag);
                }
                // Outras opções.
                // Não se fecha a Tag. 
                // Esta opção serve para a Tag Atributo de Abertura, dado que tem os atributos antes de fecha.
                // Faz-se o fecho no Yacc.
                else
                {
                    return strcat(spaces, tag);
                }
            }
        }
    }
    
    // Caso a Tag não tenha Espaços.
    // Omite-se a Concatenação de Espaços.
    else
    {
        // Caso seja uma Tag Default ou uma Tag Atributo de Fecho 
        if (typeTag == defaultTag || (typeTag == attributeTag && openingOrClosing == isClosing))
        {
            strcat(tag, text);
            strcat(tag, ">");
            return tag;
        }
        // Caso seja uma Tag Self Closing
        else if (typeTag == selfClosingTag)
        {
            strcat(tag, " />");
            return strcat(spaces, tag);
        }
        // Outras opções.
        // Não se fecha a Tag. 
        // Esta opção serve para a Tag Atributo de Abertura, dado que tem os atributos antes de fecha.
        // Faz-se o fecho no Yacc.
        else
        {
            strcat(tag, text);
            return tag;
        }
    }
}