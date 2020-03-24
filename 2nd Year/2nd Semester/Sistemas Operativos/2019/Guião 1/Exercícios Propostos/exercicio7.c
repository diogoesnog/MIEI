#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

struct Person{
  char *nome;
  char *idade;
};

int main(int argc, char** argv){

    int file = open("output.dat", O_CREAT | O_RDWR);

    struct Person human;

    char *nome = "Diogo Nogueira";
    char *idade = "22.23";
    human.nome = strdup(nome);
    human.idade = strdup(idade);

    write(file, &human, sizeof(struct Person));

    struct Person human2;

    char *nome2 = "Filipe Gomes";
    char *idade2 = "21.23";
    human2.nome = strdup(nome2);
    human2.idade = strdup(idade2);

    write(file, &human2, sizeof(struct Person));

    struct Person human3;

    char *nome3 = "Teresa Leite Castro";
    char *idade3 = "22.2";
    human3.nome = strdup(nome3);
    human3.idade = strdup(idade3);

    write(file, &human3, sizeof(struct Person));

    struct Person human4;

    char *nome4 = "Tiago Nogueira";
    char *idade4 = "22";
    human4.nome = strdup(nome4);
    human4.idade = strdup(idade4);

    write(file, &human4, sizeof(struct Person));

    struct Person humanoLido;

    lseek(file,0,SEEK_SET);

    while(read(file, &humanoLido, sizeof(struct Person))){
        
        if(strcmp(humanoLido.nome, "Teresa Leite Castro")==0){

          
              lseek(file, -sizeof(struct Person), SEEK_CUR);
              
              struct Person novaPessoa;
              novaPessoa.nome = humanoLido.nome;
              char *novaIdade = "40.1212";
              novaPessoa.idade = strdup(novaIdade);

              write(file, &novaPessoa, sizeof(struct Person));

              // Talvez seja desnecessário.
              // lseek(file, sizeof(struct Person), SEEK_CUR);
     
        }
    }

    lseek(file,0, SEEK_SET);

    while(read(file, &humanoLido, sizeof(struct Person))){
        printf("%s - ", humanoLido.nome);
        printf("%s\n", humanoLido.idade);

    }
    

    return 0;
}