#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>

#include <unistd.h> // Chamadas ao Sistema
#include <fcntl.h> // O_RDONLY, O_WRONLY, O_CREATE, O_*


#include "person.h"

Person newPerson(char* nome, int idade){

    char *novoNome = malloc(1000*sizeof(char));
    strncpy(novoNome, nome, strlen(nome)+1);

    Person *person = malloc(sizeof(struct person));

    person->nome = novoNome;
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

int personAge(Person *pessoa){
    return pessoa->idade;
}

Person personChangeAge(Person *pessoa, int idade){
    
    Person *newPerson = malloc(sizeof(struct person));

    newPerson->nome = pessoa->nome;
    newPerson->idade = idade;

    return *newPerson;
}

void imprimirPessoas() {

    int ficheiro = open("persons", O_RDONLY);
    
    struct person agePerson;
    
    while(read(ficheiro, &agePerson, sizeof(struct person))) {
        printf("%s\n", agePerson.nome);
    }

    close(ficheiro);
}

int main(int argc, char const *argv[]) {

    if(argc > 2 && strcmp(strdup(argv[1]), "-i") == 0) {
    
        int ficheiro = open("persons", O_CREAT | O_RDWR | O_APPEND, 0666);

        struct person addPerson = newPerson("Diogo Nogueira", 12);
        write(ficheiro, &addPerson, sizeof(struct person));

        close(ficheiro);
    }
    
    else if(argc > 2 && strcmp(strdup(argv[1]), "-u") == 0) {
    }

    else printf("Não selecionou nenhuma opção.\n");
    
    imprimirPessoas();
}