#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "directories.h"

// Auxiliar Functions: countLine, cleanName, numberIterations and inserEnd
int countLines(char *lineName){

    int result = 0;

    while(*lineName && *lineName++ == '-') ++result;

    return result;
}

char* cleanName(char *name, char *rootName){

    int i, j;

    for(i = 0; name[i] && '-' != name[i]; i++);

    if(name[i]){

        for(j = 1; name[i] = name[i+j];){
            // Remove all '-' and unnecessary spaces.
            if(name[i] == '-' || name[i] == ' ') j++;
            else i++;
        }
    }
    if(rootName != NULL && name[0] == '{'){
        char *endName = strchr(name, '.');
        name = strdup(rootName);
        strcat(name, endName);
    }

    return name;
}

int numberIterations(Directories *list, int lineLimit){

    int result = 0;
    int i = 0;

    Directories *current = list;

    while(current){
        if(current -> lineNumber == lineLimit) result = i;
        i++;
        current = current -> next;
    }

    return result;
}

Directories* insertEnd(Directories *list, int lN, int fileFoler, char *n, char *d){

    Directories *newList = malloc(sizeof(struct directories));
    Directories *current = list;

    while(current -> next != NULL)
        current = current -> next;

    newList -> lineNumber = lN;
    newList -> fileOrFolder = fileFoler;
    newList -> name = n;
    newList -> directory = d;
    newList -> next = NULL;

    current -> next = newList;

    return list;
}

// Principal Function: insertDirectory
Directories* insertDirectory(Directories *list, int fileFoler, char *name, char *rootName){

    int numberLines = countLines(name);
    char *newName = cleanName(name, rootName);

    Directories *newList = malloc(sizeof(struct directories));

    // Empty Linked List.
    if(list == NULL) {
        newList -> lineNumber = numberLines;
        newList -> fileOrFolder = fileFoler;
        newList -> name = newName;
        newList -> directory = newName;
        newList -> next = NULL;
        list = newList;
    }
    // Otherwise.
    else{

        int lineLimit = numberLines - 1;

        if(numberLines == 0) 
            list = insertEnd(list, numberLines, fileFoler, newName, newName);

        else{
            Directories *current = list;

            int number = numberIterations(list, lineLimit);

            while(current -> next != NULL && number != 0){
                number--;
                current = current -> next;
            }

            char *directory;
            directory = strdup(current -> directory);
            strcat(directory, strdup(newName));

            list = insertEnd(list, numberLines, fileFoler, newName, directory);
        }
    }

    return list;
}

// Auxiliar Function: lastDirectory
char* lastDirectory(Directories *list){
    
    Directories *current = list;

    while(current -> next != NULL)
        current = current -> next;

    return current -> directory;
}

// Principal Functions: createFolder, createFile
void createFolder(Directories *list){
    
    char *currentDirectory = lastDirectory(list);
    int status = mkdir(currentDirectory, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}

void createFile(Directories *list){

    char *currentDirectory = lastDirectory(list);
    FILE *newFile = fopen(currentDirectory, "w");
    fclose(newFile);
}

// Other Functions
Directories* init(){
    
    Directories *list = malloc(sizeof(struct directories));
    list = NULL;

    return list; 
}

char* getDirectory(Directories *list, char* nameFile){

    Directories *current = list;

    while(current != NULL && strcmp(current -> name, nameFile)){
        current = current -> next;
    }

    return current -> directory;
}

void printDirectories(Directories *list){

	while(list){
		printf("Name: %s\n", list -> name);

        if(list -> fileOrFolder == 1) printf("File\n");
        else printf("Diretory\n");
        
        printf("Directory: %s\n\n", list -> directory);
		list = list -> next;
	}
}