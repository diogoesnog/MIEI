#include <stdlib.h>

typedef struct person{
    char *nome;
    int idade;
} Person;

Person newPerson(char *nome, int idade);
Person clonePerson(Person *pessoa);
void destroyPerson(Person *pessoa);
int personAge(Person *pessoa);
int personChangeAge(Person *pessoa, int age);