#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]){

    // ESCRITA

    // O 0 antes do 6 significa que a base e octal.
    // fd e o descritor de ficheiro
    int fd = open("a.txt", O_CREAT|O_WRONLY, 0640);
    
    printf("fd=%d\n",fd);

    //write("a.txt","ola\n",4); // Completamente errado
    write(fd,"ola\n",4);

    close(fd);

    // LEITRUA

    char dados[100];

    fd = open("a.txt", O_RDONLY);

    read(fd, dados, 8);
    dados[8] = '\0'; // Isto resolve o problema de baixo. ou so o 0. ou 0x0.
    
    printf("Lido: %s\n", dados);  // Errado. Porque esta a imprimir demasiado lixo depois do ola por causa do \n.

    write(1, dados, n); // substitui o printf de cima.  1=STDOUT

    close(fd);
}