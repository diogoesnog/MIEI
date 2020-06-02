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
// Repete para o pipe do todas as linhas de texto lidas do stdin
int main() {

    char buffer[1024];
    int bytesLidos;
    int fileDescriptor;

    fileDescriptor = open("fifo", O_WRONLY);

    while( (bytesLidos = read(0, buffer, sizeof(buffer))) > 0 ) {
        write(fileDescriptor, buffer, bytesLidos);
    }

    return 0;
}