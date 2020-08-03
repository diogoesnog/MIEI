/* 
 * File:   Servidor de Vendas
 * Author: Diogo Araújo, Diogo Nogueira, Hugo Moreira
 *
 * Version 3.0 - Alteracao/Entrada Stock a funcionar.
 * Ja imprime para um ficheiro de vendas consoante o que existe em stock.
 * Nao permite vender caso nao haja stock para esse artigo.
 * Apenas falta lidar com a sincronização em si - Cliente a Cliente funcional.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h> 
#include <sys/stat.h>
#include <ctype.h>
#include <sys/stat.h>
#include <locale.h>
#include <time.h>

#include "sv.h"
#include "ma.h"

int numeroProcesso = 0;

int existeArtigo(int codigoArtigo){
    
    int ficheiroStock = open("stock.txt", O_RDONLY, 0666);
    
    struct ArtigoStock artigoLido;

    int resultado = 0;
    
    lseek(ficheiroStock, 0, SEEK_SET);
    
    while(read(ficheiroStock, &artigoLido, sizeof(struct ArtigoStock))){
        if(artigoLido.codigoArtigo==codigoArtigo) resultado = 1;
    }

    close(ficheiroStock);
    
    return resultado;
}

void insereNovaVenda(int codigoArtigo, int quantArtigo, int novaQuantArtigo){

    int ficheiroVendas = open("vendas.txt", O_CREAT | O_RDWR | O_APPEND, 0666);
    int ficheiroArtigos = open("artigos.txt", O_RDONLY, 0666);

    struct Venda novaVenda;
    struct Artigo artigoLido;

    while(read(ficheiroArtigos, &artigoLido, sizeof(struct Artigo))){
        if(artigoLido.codigoArtigo==codigoArtigo) 
        novaVenda.montanteTotal = artigoLido.precoArtigo*quantArtigo;
    }

    novaVenda.codigoArtigo = codigoArtigo;
    novaVenda.quantArtigo = quantArtigo;

    write(ficheiroVendas, &novaVenda, sizeof(struct Venda));

    close(ficheiroVendas);
    close(ficheiroArtigos);

    char *novaQuantidade = malloc(sizeof(novaQuantArtigo));
    sprintf(novaQuantidade, "%d", novaQuantArtigo);

    char *stringOutput;
    stringOutput = strdup(novaQuantidade);
    strcat(stringOutput, "\n");

    int logFile = open("resultados.txt", O_CREAT | O_RDWR | O_APPEND, 0666);
    write(logFile, stringOutput, strlen(stringOutput));

    close(logFile);

}

void verificaStockPreco(int codigoArtigo){
    
    int ficheiroStock = open("stock.txt", O_RDONLY, 0666);
    int ficheiroArtigos = open("artigos.txt", O_RDONLY, 0666);

    struct Artigo artigoLido;
    struct ArtigoStock stockArtigoLido;

    int stockArtigo;
    double precoArtigo;

    lseek(ficheiroStock, 0, SEEK_SET);
    lseek(ficheiroArtigos, 0, SEEK_SET);

    if(existeArtigo(codigoArtigo)==1){
        while(read(ficheiroStock, &stockArtigoLido, sizeof(struct ArtigoStock))){
            if(stockArtigoLido.codigoArtigo==codigoArtigo) {
                stockArtigo = stockArtigoLido.quantArtigo;
            }
        }
    }
    else stockArtigo = 0;

    close(ficheiroStock);

    while(read(ficheiroArtigos, &artigoLido, sizeof(struct Artigo))){
        if(artigoLido.codigoArtigo==codigoArtigo) precoArtigo = artigoLido.precoArtigo;
    }

    close(ficheiroArtigos);

    char *stock = malloc(sizeof(stockArtigo));
    sprintf(stock, "%d", stockArtigo);
    char *preco = malloc(sizeof(precoArtigo));
    sprintf(preco, "%f", precoArtigo);

    char *stringOutput;
    stringOutput = strdup(stock);
    strcat(stringOutput, " ");
    strcat(stringOutput, preco);
    strcat(stringOutput, "\n");

    int logFile = open("resultados.txt", O_CREAT | O_RDWR | O_APPEND, 0666);
    write(logFile, stringOutput, strlen(stringOutput));

    close(logFile);
}

void alteraQuantArtigo(int codigoArtigo, int quantArtigo){
    
    int ficheiroStock = open("stock.txt", O_RDWR);
    int quantNegativa;

    // Verificar se esta a entrar ou sair stock.
    if(quantArtigo>0) quantNegativa = 0;
    else quantNegativa = 1;

    // Caso se esta a abrir o ficheiro pela primeira vez.
    if(ficheiroStock<=-1){

        if(quantNegativa == 0){
            ficheiroStock = open("stock.txt", O_CREAT | O_RDWR | O_APPEND, 0666);

            struct ArtigoStock novoArtigo;

            novoArtigo.codigoArtigo = codigoArtigo;
            novoArtigo.quantArtigo = quantArtigo;

            write(ficheiroStock, &novoArtigo, sizeof(struct ArtigoStock));
        }
    }
    else{

        ficheiroStock = open("stock.txt", O_RDWR, 0666);
            
        if(existeArtigo(codigoArtigo) == 1) {
            
            struct ArtigoStock artigoLido;

            while(read(ficheiroStock, &artigoLido, sizeof(struct ArtigoStock))){

                if(artigoLido.codigoArtigo==codigoArtigo){
                
                    lseek(ficheiroStock, -sizeof(struct ArtigoStock), SEEK_CUR);

                    struct ArtigoStock novoArtigo;

                    if(artigoLido.quantArtigo + quantArtigo >= 0){
                        novoArtigo.codigoArtigo = codigoArtigo;
                        novoArtigo.quantArtigo = artigoLido.quantArtigo+quantArtigo;
                        write(ficheiroStock, &novoArtigo, sizeof(struct ArtigoStock));

                        if(quantNegativa == 1) insereNovaVenda(codigoArtigo, -quantArtigo, novoArtigo.quantArtigo);
                    }   
                }
            }
        }
        else {

            if(quantNegativa == 0){

                ficheiroStock = open("stock.txt", O_RDWR | O_APPEND, 0666);

                struct ArtigoStock novoArtigo;

                novoArtigo.codigoArtigo = codigoArtigo;
                novoArtigo.quantArtigo = quantArtigo;

                write(ficheiroStock, &novoArtigo, sizeof(struct ArtigoStock));
            }
        }
    }

    //close(ficheiroStock);
}

void geraAgregacao(){

    time_t tempoAtual;
    struct tm *informacao;

    char datePlusTime[30];
    char *nome;

    time(&tempoAtual);
    informacao = localtime(&tempoAtual);

    strftime(datePlusTime, sizeof(datePlusTime), "%FT%T", informacao);

    nome = strdup(datePlusTime);
    strcat(nome, ".txt");

    pid_t pid = fork();

    if(pid==0){
        int ficheiroOutput = open(nome, O_CREAT | O_RDWR | O_APPEND, 0666);
        dup2(ficheiroOutput, 1);
        execlp("./ag", "./ag", "vendas.txt", NULL);
        _exit(0);
    }
}

int main(int argc, char** argv) {
   
    int pipe, openPipe;
    char dadosRecebidos[1024];
    int i, status;
    pid_t pidProcesso;


    // Ciclo que permite que o Servidor de Vendas va recebendo os dados do Cliente de Vendas.
    for(;;){ 

		Comando *novoComando = malloc(sizeof(*novoComando));

        char *meuPipe = "gestorVendas";

        pipe = mkfifo(meuPipe, 0666);
        openPipe = open(meuPipe, O_RDWR);

        if(read(openPipe, novoComando, sizeof(*novoComando))>0){

            pidProcesso = fork();

            if(pidProcesso == -1){
                perror("Fork falhou.");
                return 1;
            }
            if(pidProcesso == 0){

                int codigoArtigo = novoComando->codigoArtigo;
                int quantArtigo = novoComando->quantidadeArtigo;

		        if(codigoArtigo == -1) geraAgregacao();

                if(codigoArtigo != -1 && quantArtigo == 0) {
                    printf("%d %d", codigoArtigo, quantArtigo);
                    verificaStockPreco(codigoArtigo);
                }

                if(codigoArtigo != -1 && quantArtigo !=0) {
                    printf("%d %d", codigoArtigo, quantArtigo);
                    alteraQuantArtigo(codigoArtigo, quantArtigo);
                }

                sleep(1);
                _exit(numeroProcesso);
                numeroProcesso++;
            }
        }

        for(i=0; i<numeroProcesso; i++){
            pidProcesso = wait(&status);
        }
    }

    return EXIT_SUCCESS;
}