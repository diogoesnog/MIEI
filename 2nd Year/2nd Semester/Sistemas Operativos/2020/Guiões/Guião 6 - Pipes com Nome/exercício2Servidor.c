#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

int main()
{

    int bytesLidos;
    char buffer[1024];

    // Criar um novo Pipe com Nome com outro nome do já criado
    mkfifo("newFifo", 0777);

    // Abrir o Pipe com Nome para leitura do que vem do Cliente
    // Abrir o ficheiro log.txt onde se vão escrever as mensagens vindas do Cliente
    int fileDescriptor1 = open("newFifo", O_RDONLY);
    int fileDescriptor2 = open("log.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);

    // O que está a ser lido do STDIN passa para o Pipe com Nome
    dup2(fileDescriptor1, 0);
    close(fileDescriptor1);

    // O que está a ser escrito no STDOUT passa para o ficheiro log.txt
    dup2(fileDescriptor2, 1);
    close(fileDescriptor2);

    // Note-se que aqui vamos lendo do STDIN dado que sabemos que já está a ser redirecionado para o Pipe com Nome
    // Escrevemos no STDOUt dado que sabemos que irá para o ficheiro log.txt
    while ((bytesLidos = read(0, buffer, sizeof(buffer))) > 0)
    {
        write(1, buffer, bytesLidos);
    }

    return 0;
}