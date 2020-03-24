#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "person.h"

int main(){

    char* nome = malloc(sizeof(char));
    strcpy(nome,"Diogo Nogueira");

    Person person1 = newPerson(nome, 22);

    printf("Nome: %s\n",person1.nome);
    printf("Idade: %d\n",person1.idade);

    Person person2 = clonePerson(&person1);

    printf("Nome: %s\n",person2.nome);
    printf("Idade: %d\n",person2.idade);

    printf("Idade do Diogo: %d\n", personAge(&person1));
    printf("Nova Idade do Diogo: %d\n", personChangeAge(&person1, 23));
}

