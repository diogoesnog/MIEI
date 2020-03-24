#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

// Função que lê do monitor (daí o descritor de ficheiro 0) e escreve no monitor (1)

int main(int argc, char**argv){

    char c;

    while(read(0, &c, 1)){
        write(1, &c, 1);
    }
    
}