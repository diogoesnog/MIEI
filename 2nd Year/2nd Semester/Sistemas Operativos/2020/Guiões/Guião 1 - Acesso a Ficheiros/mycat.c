#include <sys/types.h>

#include <unistd.h> // Chamadas ao Sistema
#include <fcntl.h> // O_RDONLY, O_WRONLY, O_CREATE, O_*

#define SIZE 1024

// Exercício Proposto 2

// Programa com funcionalidade similiar ao comando cat.
// 1. Ler do stdin (teclado) e escrever para o stdout (terminal). [x]
int main (int argc, char *argv[]) {

    int byteslidos;
    char *buffer[SIZE];

    while( (byteslidos = read(0, buffer, SIZE)) > 0) {
        write(1, buffer, byteslidos);
    }
}