#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "person.h"

Person newPerson(char* nome, int idade){

    int tamanhoNome = strlen(nome) + 1;
    char *nomePessoa = malloc(sizeof(char[tamanhoNome]));
    strcpy(nomePessoa,nome);

    Person *person = malloc(sizeof(struct person));

    person->nome = nomePessoa;
    person->idade = idade;

    return *person;
}

Person clonePerson(Person *pessoa){

    int tamanhoNome = strlen((pessoa->nome) +1);
    char *nomePessoa = malloc(sizeof(char[tamanhoNome]));
    strcpy(nomePessoa,pessoa->nome);

    Person *clonePerson = malloc(sizeof(struct person));

    clonePerson->nome = nomePessoa;
    clonePerson->idade = pessoa->idade;

    return *clonePerson;
}

void destroyPerson(Person *pessoa){
    free(pessoa->nome);
}

int personAge(Person *pessoa){
    return pessoa->idade;
}

int personChangeAge(Person *pessoa, int idade){
    pessoa->idade = idade;
    return pessoa->idade;
}