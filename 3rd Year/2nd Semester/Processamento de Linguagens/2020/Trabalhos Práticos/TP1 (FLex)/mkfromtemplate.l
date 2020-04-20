/* Includes e Variáveis */
%{
    #include <string.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include "directories.h"

    char *name;
    char *email;
    char *author;

    FILE *currentFile;
    char *currentDirectory;
    char *currentNameFile;

    Directories *directories; 
%}

%option noyywrap

/* Definir as Start Conditions usadas */
%x META TREE FICHEIRO CONTENT

/* Processamento dos Dados - ERs e SC */
%%

"=== meta" {
    BEGIN META;
}

"=== tree" {
    BEGIN TREE;
}

<META>{
    "email: "[^\n]+ {
        email = strdup(yytext+7);
    }
    
    "author: "[^\n]+ {
        author = strdup(yytext+8);
        BEGIN INITIAL;
    }
    \n {;}
}

<TREE>{
    ^\{"%name%"\}\/ {
        char *directory = strdup(name);
        strcat(directory, "/");

        directories = insertDirectory(directories, isFolder, strdup(directory), NULL);
        createFolder(directories);
    }

    ^[a-zA-Z]+\/ {
        directories = insertDirectory(directories, isFolder, strdup(yytext), NULL);
        createFolder(directories);
    }
    
    ^\-+\ [a-zA-Z]+\.[a-z]+ {
        directories = insertDirectory(directories, isFile, strdup(yytext), NULL);
        createFile(directories);
    }

    ^\-+\ [a-zA-Z]+ {
        directories = insertDirectory(directories, isFile, strdup(yytext), NULL);
        createFile(directories);
    }

    ^\-+\ \{"%name%"\}\.[a-z]+ {
        directories = insertDirectory(directories, isFile, strdup(yytext), strdup(name));
        createFile(directories);
    }

    ^\-+\ [a-zA-Z]+\/ {
        directories = insertDirectory(directories, isFolder, strdup(yytext), NULL);
        createFolder(directories);
    }

    ===[ ] {BEGIN FICHEIRO;}
    
    \n  {;}
    
}

<FICHEIRO>{
    \{"%name%"\}\.[a-z]+ {
        char *nameFile = strdup(name);
        char *extension = strchr(yytext, '.');
        strcat(nameFile, extension);

        currentNameFile = nameFile;
    }

    [a-zA-Z\.]+ {
        currentNameFile = strdup(yytext);
    }

    \n {
        BEGIN CONTENT;
        currentDirectory = getDirectory(directories, strdup(currentNameFile));
        currentFile = fopen(currentDirectory, "a+");
    }
    
}

<CONTENT>{
    \{"%name%"\} {
        fwrite(name, strlen(name), 1, currentFile);
    }

    \{"%email%"\} {
        fwrite(email, strlen(email), 1, currentFile);
    }

    \{"%author%"\} {
        fwrite(author, strlen(author), 1, currentFile);
    }

    .|\n {
        fwrite(yytext, strlen(yytext), 1, currentFile);
    }
    
    ===[ ] {
        fclose(currentFile);
        currentDirectory = currentNameFile = "";
        
        BEGIN FICHEIRO;
    }
}

%%

/* Função Main */
int main(int argc, char* argv[]){

    if(argc == 3){

        // Global Variables Values
        email = author = "";
        name = strdup(argv[1]);
        directories = init();

        // Open template file
        yyin = fopen(argv[2], "r");
        
        // FLex Process
        yylex();
    }   
    else {
        printf("mkfromtemplate name template");
        return 1;
    }

    return 0;
}