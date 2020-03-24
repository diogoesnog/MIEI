#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

// Implementar um programa que cria um ficheiro com 10MB de tamanho cujo nome é passado como argumento.
// O conteúdo do ficheiro propriamente dito é irrelevante: por exemplo, pode ser composto exclusivamente pelo caractere ‘a’.

int main(int argc, char**argv){

    // Quando e para abrir ficheiro usar os 3 argumentos.
    // argv[1] porque o argumento 0 e o executavel.
    // Função open devolve um descritor para um determinado ficheiro.
    int fd = open(argv[1], O_CREAT|O_WRONLY, 0600);

    int tamanho = 1024*1024; 

    for(int i=0; i<tamanho; i++){
        // Fd é o nosso descritor de ficheiro.
        write(fd, "a", 1);
    }

    printf("O descritor do ficheiro é:%d\n",fd);
}