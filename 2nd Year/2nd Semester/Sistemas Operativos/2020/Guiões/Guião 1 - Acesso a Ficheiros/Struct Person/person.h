#include <stdlib.h>

typedef struct person{
    char *nome;
    int idade;
} Person;

Person newPerson(char *nome, int idade);
Person clonePerson(Person *pessoa);
int personAge(Person *pessoa);
Person personChangeAge(Person *pessoa, int age);