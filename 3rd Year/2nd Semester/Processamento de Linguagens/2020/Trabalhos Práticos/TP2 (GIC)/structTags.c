#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structTags.h"

// Função de Inicialização da Lista Ligada.
Tags *init()
{

    Tags *listTags = malloc(sizeof(struct tags));
    listTags = NULL;

    return listTags;
}

// Função de Inserção na Lista Ligada.
// Inserção feita no início da Lista.
Tags *insertTag(Tags *listTags, char *nameTag, int numberSpaces)
{
    Tags *newList = malloc(sizeof(struct tags));

    // Lista Ligada vazia.
    if (listTags == NULL)
    {
        newList->numberSpaces = numberSpaces;
        newList->closingTag = nameTag;
        newList->next = NULL;
    }
    // Lista Ligada não vazia.
    else
    {
        newList->numberSpaces = numberSpaces;
        newList->closingTag = nameTag;
        newList->next = listTags;
    }

    listTags = newList;

    return listTags;
}

// Função de remoção do primeiro elemento da Lista Ligada.
// Usada para as Self Closing Tags.
Tags *removeFirstTag(Tags *listTags){
    return listTags->next;
}

// Função de remoção das Tags que já fecharam fechadas no HTML em si e já não são precisas.
Tags *removeClosedTags(Tags *listTags, int numberSpaces)
{

    if (listTags->next == NULL)
    {
        return listTags;
    }
    else
    {
        Tags *firstElement = listTags;
        Tags *newList = listTags->next;

        if (numberSpaces <= newList->numberSpaces)
        {
            newList = newList->next;

            while (newList && numberSpaces <= newList->numberSpaces)
            {
                newList = newList->next;
            }

            firstElement->next = newList;
            listTags = firstElement;

            return firstElement;
        }
        else
        {
            return listTags;
        }
    }
}

// Função para devolver a Opening Tag com as devidas Closed Tags, caso seja preciso fechar alguma(s) Tag(s).
char *newInitialTag(Tags *listTags, char *initialTag, int numberSpaces)
{
    char *newTag;

    if (listTags->next == NULL)
    {
        return initialTag;
    }
    else
    {
        Tags *newList = listTags->next;

        if (numberSpaces <= newList->numberSpaces)
        {
            newTag = strdup(newList->closingTag);
            newList = newList->next;

            while (newList && numberSpaces <= newList->numberSpaces)
            {
                strcat(newTag, "\n");
                strcat(newTag, strdup(newList->closingTag));
                newList = newList->next;
            }

            strcat(newTag, "\n");
            strcat(newTag, strdup(initialTag));

            return newTag;
        }
        else
        {
            return initialTag;
        }
    }
}

// Função de impressão das Tags que existem na Lista Ligada.
// Texto formatado para aparecer com as devidas mudanças de linha em termos de HTML.
void printFinalClosingTags(Tags *listTags)
{
    printf("\n");

    while (listTags)
    {
        printf("%s\n", listTags->closingTag);
        listTags = listTags->next;
    }
}

// Função de impressão usada para testes ao longo do projeto.
void printTags(Tags *listTags)
{

    while (listTags)
    {

        printf("Tag Name: %s\n", listTags->closingTag);
        printf("Number Spaces: %i\n", listTags->numberSpaces);

        listTags = listTags->next;
    }
}