#include <sys/types.h>
#include <stdio.h>

#include <unistd.h> // Chamadas ao Sistema
#include <fcntl.h> // O_RDONLY, O_WRONLY, O_CREATE, O_*

#define SIZE 1024

// Exercício Proposto 1

// Programa com funcionalidade similar ao comando cp.
// 1. Copiar um ficheiro. [x]
// 2. Copiar um ficheiro ou Vários para uma diretoria. 
// 3. Copiar uma diretoria ou Várias para outra diretoria.

int main (int argc, char *argv[]) {

    int source, destination;
    int byteslidos;
    char *buffer[SIZE];
    
    // Caso se dêem apenas 1 ou 2 argumentos.
    // mycp
    // mycp ficheiro
    if(argc == 1 || argc == 2) {

        printf("Necessário fornecer todos parâmetros.");
        printf("\nmycp ficheiro ficheiro/diretoria\n");
    }
    // Caso se dêem apenas 3 argumentos.
    // mycp ficheiro ficheiro/diretoria
    else if(argc == 3) {
        
        source = open(argv[1], O_RDONLY);

        if(source == -1) printf("Erro ao abrir o ficheiro Solicitado.\n");
        else {
            // O_CREATE e O_TRUNC é para truncar um ficheiro existente ou criar um novo.
            destination = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC);
            
            if(destination == -1) printf("Erro ao abrir/criar o ficheiro Solicitado.\n");

            while( (byteslidos = read(source, buffer, SIZE)) > 0) {
                write(destination, buffer, byteslidos);
            }
        }
    }
}