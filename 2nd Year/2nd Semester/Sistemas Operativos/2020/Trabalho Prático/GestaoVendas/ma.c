/* 
 * File:   Manutenção de Artigos
 * Author: Diogo Araújo, Diogo Nogueira, Hugo Moreira
 * 
 * Version 3.0 - Final
 * Todos os requisitos completamente funcionais.
 * O código de cada artigo é usado também como marcador da posição do nome no ficheiro strings.txt.
 * O ficheiro strings.txt contém todos os registos de alterações de nomes alguma vez já feitos. 
 * O nome mais recente de um artigo é então o primeiro a contar desde o fim do ficheiro até ao início.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include<sys/wait.h> 

#include "ma.h"
#include "sv.h"

void insereArtigo(char *nomeArtigo, double precoArtigo){

    // Ficheiros para a escrita informações dos artigos.
    int ficheiroArtigos = open("artigos.txt", O_RDWR);
    int ficheiroNomesArtigos = open("strings.txt", O_CREAT | O_RDWR | O_APPEND, 0666);

    // Caso não se consigo abrir o ficheiro artigos.txt.
    // Significa que é a primeira vez que estamos a escrever nele.
    // Atribuimos o número 1 ao seu código numérico.
    if(ficheiroArtigos<=-1){

        ficheiroArtigos = open("artigos.txt",  O_CREAT | O_RDWR | O_APPEND, 0666);

        // Escrita da struct no ficheiro artigos.txt.
        struct Artigo novoArtigo;

        novoArtigo.codigoArtigo = 1;
        novoArtigo.precoArtigo = precoArtigo;
        write(ficheiroArtigos, &novoArtigo, sizeof(struct Artigo));

        // Escrita do nome no ficheiro strings.txt.
        char *posicaoArtigo = malloc(sizeof(novoArtigo.codigoArtigo));
        sprintf(posicaoArtigo, "%d", novoArtigo.codigoArtigo);
        char *ficheiroString;

        ficheiroString = strdup(posicaoArtigo);
        strcat(ficheiroString, " ");
        strcat(ficheiroString, nomeArtigo);
        strcat(ficheiroString, "\n");
        write(ficheiroNomesArtigos, ficheiroString, strlen(ficheiroString));

        // Fecho dos descritores de ficheiros.
        close(ficheiroArtigos);
        close(ficheiroNomesArtigos);
    }
    // Caso não seja o primeiro artigo a ser inserido.
    else{    
        ficheiroArtigos = open("artigos.txt", O_RDWR | O_APPEND, 0666);

        // Apontador de para leitura/escrita do ficheiro mudado para o último artigo.
        lseek(ficheiroArtigos, -sizeof(struct Artigo), SEEK_END);

        // Obtenção do código da struct correspondente ao último artigo.
        struct Artigo ultimoArtigo;
        read(ficheiroArtigos, &ultimoArtigo, sizeof(struct Artigo));
        int codigoUltimoArtigo = ultimoArtigo.codigoArtigo;

        // Escrita da struct no ficheiro artigos.txt.
        struct Artigo novoArtigo;

        novoArtigo.codigoArtigo = codigoUltimoArtigo+1;
        novoArtigo.precoArtigo = precoArtigo;

        lseek(ficheiroArtigos, 0, SEEK_END);
        write(ficheiroArtigos, &novoArtigo, sizeof(struct Artigo));

        // Escrita do nome no ficheiro strings.txt.
        char *posicaoArtigo = malloc(sizeof(novoArtigo.codigoArtigo));
        sprintf(posicaoArtigo, "%d", novoArtigo.codigoArtigo);
        char *ficheiroString;

        ficheiroString = strdup(posicaoArtigo);
        strcat(ficheiroString, " ");
        strcat(ficheiroString, nomeArtigo);
        strcat(ficheiroString, "\n");
        write(ficheiroNomesArtigos, ficheiroString, strlen(ficheiroString));

        // Fecho dos descritores de ficheiros.
        close(ficheiroArtigos);
        close(ficheiroNomesArtigos);
    }
}

void alteraNomeArtigo(int codigoArtigo, char *nomeArtigo){

    int ficheiroNomesArtigos = open("strings.txt", O_CREAT | O_RDWR | O_APPEND, 0666);

    char *posicaoArtigo = malloc(sizeof(codigoArtigo));
    sprintf(posicaoArtigo, "%d", codigoArtigo);
    char *ficheiroString;

    ficheiroString = strdup(posicaoArtigo);
    strcat(ficheiroString, " ");
    strcat(ficheiroString, nomeArtigo);
    strcat(ficheiroString, "\n");
    write(ficheiroNomesArtigos, ficheiroString, strlen(ficheiroString));

    close(ficheiroNomesArtigos);
}

void alteraPrecoArtigo(int codigoArtigo, double precoArtigo){

    int ficheiroArtigos = open("artigos.txt", O_RDWR, 0666);

    struct Artigo artigoLido;

    lseek(ficheiroArtigos, 0, SEEK_SET);

    while(read(ficheiroArtigos, &artigoLido, sizeof(struct Artigo))){

        if(artigoLido.codigoArtigo == codigoArtigo){
            
            lseek(ficheiroArtigos, -sizeof(struct Artigo), SEEK_CUR);

            struct Artigo novoArtigo;

            novoArtigo.codigoArtigo = artigoLido.codigoArtigo;
            novoArtigo.precoArtigo = precoArtigo;

            write(ficheiroArtigos, &novoArtigo, sizeof(struct Artigo));
        }
    }

    close(ficheiroArtigos);
}

void comunicaServidor(){

    int openPipe = open("gestorVendas", O_WRONLY);

    Comando *novoComando = malloc(sizeof(*novoComando));
    novoComando->codigoArtigo = -1;
    novoComando->quantidadeArtigo = 0;

    write(openPipe, novoComando, sizeof(*novoComando));

    close(openPipe);
}

void interpretaComandoMA(char *buffer){

    int numeroArgumento=0;

    char *argumento = strtok(buffer, "\n");
    
    char *nomeArtigo;
    char *precoArtigo;
    char *codigoArtigo;
    char buffer2[1024];

    if(strcmp(argumento, "a")==0) comunicaServidor();

    else{
    
        argumento = strtok(buffer, " ");
        char *comando = strdup(argumento);

        while(argumento!=NULL && numeroArgumento<3){


            switch (numeroArgumento){

                case 0: argumento = strtok(NULL, " ");
                        break;
                case 1: {
                    if(strcmp(comando, "i")==0){
                        nomeArtigo = strdup(argumento);
                        argumento = strtok(NULL, "\n");
                    }
                    if(strcmp(comando, "n")>=0){
                        codigoArtigo = strdup(argumento);
                        argumento = strtok(NULL, "\n");
                    }
                    break;
                }
                case 2: {
                    if(strcmp(comando, "i")==0 || strcmp(comando, "p")==0) {
                        precoArtigo = strdup(argumento);
                        argumento = NULL;
                    }
                    if(strcmp(comando, "n")==0) {
                        nomeArtigo = strdup(argumento);
                        argumento = NULL;
                    }
                    break;
                }
            }

            numeroArgumento++;
        }

        if(strcmp(comando, "i")==0) insereArtigo(nomeArtigo, atof(precoArtigo));
        if(strcmp(comando, "n")==0) alteraNomeArtigo(atoi(codigoArtigo), nomeArtigo);
        if(strcmp(comando, "p")==0) alteraPrecoArtigo(atoi(codigoArtigo), atof(precoArtigo));
        }
}

int main(int argc, char const *argv[]){

    char buffer[1024];
    char caracterLido = 0;
    int lidos;
    int i = 0;
    int j;
    char *novo;

    for(j=0; j<sizeof(buffer); j++) buffer[j]='\0';

    while((lidos = read(0, &caracterLido, 1))>0){

        if(caracterLido != '\0'){
            buffer[i] = caracterLido;
            i++;
        }

        if(caracterLido == '\n'){
            interpretaComandoMA(buffer);
            for(j=0; j<sizeof(buffer); j++) buffer[j]='\0';
            i = 0;
        }
        
    }
    
    interpretaComandoMA(buffer);
    return 0;
}