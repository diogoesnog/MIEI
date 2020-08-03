/* 
 * File:   Cliente de Vendas
 * Author: Diogo Araújo, Diogo Nogueira, Hugo Moreira
 *
 * Created on 18 de Abril de 2019, 17:23
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h> 

#include "ma.h"
#include "sv.h"

void interpretaComandoCV(char *buffer){

    int openPipe = open("gestorVendas", O_WRONLY);

    char *argumento = strtok(buffer, " ");
    
    char *quantArtigo = NULL;
    char *codigoArtigo = NULL;

    // Retira o primeiro parametro do comando.
    codigoArtigo = strdup(argumento);

    argumento = strtok(NULL, " ");

    // Significa que tem o comando tem mais do que um parametro.
    if(argumento!=NULL) {
        quantArtigo = strdup(argumento);

        Comando *novoComando = malloc(sizeof(*novoComando));
        novoComando->codigoArtigo = atoi(codigoArtigo);
        novoComando->quantidadeArtigo = atoi(quantArtigo);

        write(openPipe, novoComando, sizeof(*novoComando));
    }
    // Caso so tenha 1 parametro.
    else{
        Comando *novoComando = malloc(sizeof(*novoComando));
        novoComando->codigoArtigo = atoi(codigoArtigo);
        novoComando->quantidadeArtigo = 0;

        write(openPipe, novoComando, sizeof(*novoComando));
    }
}

int main(int argc, char** argv) {
        
    char buffer[1024];
    char caracterLido = 0;
    int lidos;
    int i = 0;
    int j;    

    for(j=0; j<sizeof(buffer); j++) buffer[j]='\0';

    while((lidos = read(0, &caracterLido, 1))>0){

        if(caracterLido != '\0'){
            buffer[i] = caracterLido;
            i++;
        }
        
        // If criado para se interpretar cada comando.
        if(caracterLido == '\n'){
            interpretaComandoCV(buffer);
            // Limpeza buffer.
            for(j=0; j<sizeof(buffer); j++) buffer[j]='\0';
            i=0;
        }
    }

    // Ultimo comando do ficheiro.
    // O Ultimo comando nao possui a mudanca de linha, dai a individualizacao.
    interpretaComandoCV(buffer);

    return 0;
}