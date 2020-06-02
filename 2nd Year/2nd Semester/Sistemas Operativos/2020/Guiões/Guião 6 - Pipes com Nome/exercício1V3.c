#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

// Programa que aproveita o pipe do exercício anterior de nome "fifo"
// Repete para stdout todas as linhas de texto lidas a partir do pipe
int main() {

    char buffer[1024];
    int bytesLidos;
    int fileDescriptor;

    fileDescriptor = open("fifo", O_RDONLY);

    while( (bytesLidos = read(fileDescriptor, buffer, sizeof(buffer))) > 0 ) {
        write(1, buffer, bytesLidos);
    }

    return 0;
}