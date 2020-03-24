#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void func(char *i){
    char *p;
    p = malloc(sizeof(char*));
    strcpy(p,i);
    printf("Hello Diogo: %s\n", i);
}   