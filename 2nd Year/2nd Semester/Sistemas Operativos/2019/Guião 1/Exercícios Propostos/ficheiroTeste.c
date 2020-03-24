#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    int ficheiro = open(argv[1], O_WRONLY, 0600);

    char buffer[10];
    int reader;
    reader = read(ficheiro,&buffer[2],1);

    char caracter = reader + '0';
    printf("O número é: %c\n", caracter);	
	
}