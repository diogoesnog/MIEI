#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char**argv){

    int i = 1; 

    int byte;
    char buffer[100];
    int ficheiro;

    char *string = NULL;

    // Caso o número de argumentos passado seja menor que 1, não se está a abrir um ficheiro.
    // Estamos a receber linhas no standard input.
    if(argv[1]==NULL){
        // Enquanto se ler caracteres em cada linha, imprime-se.
        // Não esquecer que o read lê um bloco de 10 bytes por cada linhas.
        while( (byte = read(0,buffer,10)) > 0 ){
            printf(" %d  %s\n", i++, buffer);
            for(int n=0; n!=10; buffer[n++] = '\0');
        }
    }
    // Caso contrário, estamos a querer abrir um ficheiro.
    else{
        // Abrimos o ficheiro apenas para leitura.
        ficheiro = open(argv[1], O_RDONLY);
        byte = read(ficheiro,buffer,100);

        // O strtok separa as strings que estão separadas pelo \n.
        // \n porque é o segundo parâmetro.
        string = strtok(buffer, "\n");

        while(string!=NULL){
            printf(" %d  %s\n", i++, string);
            string = strtok(NULL, "\n");
        }
    }

    return 0;
}