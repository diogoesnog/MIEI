#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

int main(int argn, char* args[]) {

    // Abrir o Pipe com Nome para escrever para enviar ao Servidor
    int fileDescriptor = open("newFifo", O_WRONLY);

    // O Cliente envia ao Servidor os seus argumentos
    for(int i = 0; args[i] != NULL; i++){
        write(fileDescriptor, args[i], strlen(args[i]));
    }

    puts("O Cliente terminou de comuniar.");

    return 0;
}