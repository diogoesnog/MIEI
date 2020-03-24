#include <sys/types.h>
#include <stdio.h>
#include <string.h> 

#include <unistd.h> // Chamadas ao Sistema
#include <fcntl.h> // O_RDONLY, O_WRONLY, O_CREATE, O_*

#define SIZE 1024

// Exercício Proposto 3

// Programa que implementa a leitura de uma linha (sequência terminada por \n)
// Devolver o número de bytes lidos na linha em si.
ssize_t myreadln(int fileDescriptor, char *buffer, size_t nbytes){

    int resultado = 0;
    int i = 0;

    while( i<nbytes && read(fileDescriptor, &buffer[i], 1)){

        if(buffer[i] == '\n') return i;
        i++;
    }

    return i;

}

ssize_t myreadlnAll(int fileDescriptor, char *buffer, size_t nbytes){
}

void main () {

    char buffer[SIZE];

    // Damos o 0 porque é do teclado que ele fará o "parse" da informação.
    int numeroBytes = myreadln(0, buffer, SIZE);
    printf("Usando ReadLine Byte a Byte.\n");
    printf("Número Bytes da Linha: %d\n", numeroBytes);

}