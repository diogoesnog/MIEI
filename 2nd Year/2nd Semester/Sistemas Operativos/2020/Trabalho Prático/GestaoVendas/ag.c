/* 
 * File:   Agregador
 * Author: Diogo Araújo, Diogo Nogueira, Hugo Moreira
 *
 * Version 2.0 - Final
 * Vamos guardando os varios artigos na estrutura.
 * Caso ja existam, apenas atualizamos a sua quantidade.
 * Imprime-se a estrutura no final.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "sv.h"
#include "ag.h"

Vendas conjuntoVendas;

int existeVenda(int codigoArtigo){
    int i;
    int resultado = 0;

    for(i=0; i<SIZE; i++){
        if (conjuntoVendas[i]->codigo == codigoArtigo)
            resultado = 1;
    }

    return resultado;
}

RegistoVenda* inicializaVenda(){
    RegistoVenda *novaVenda = (RegistoVenda*) malloc(sizeof(RegistoVenda));

    novaVenda->codigo = 0;
    novaVenda->quantidadeTotal = 0;
    novaVenda->montanteTotal = 0;
    novaVenda->proximaVenda = NULL;

    return novaVenda;
}

void inicializaVendas(Vendas vendas){
    int i;

    for(i=0; i<SIZE; i++){
        RegistoVenda *novaVenda = (RegistoVenda*) malloc(sizeof(RegistoVenda));

        novaVenda->codigo = EMPTY;
        novaVenda->quantidadeTotal = EMPTY;
        novaVenda->montanteTotal = EMPTY;
        novaVenda->proximaVenda = NULL;   

        vendas[i] =  novaVenda;
    }
}

void insereVenda(RegistoVenda *novaVenda){
    
    int chave = novaVenda->codigo; 

    if(conjuntoVendas[chave]->codigo == EMPTY)
        conjuntoVendas[chave] = novaVenda;
    else {
        novaVenda->proximaVenda = conjuntoVendas[chave]->proximaVenda;
        conjuntoVendas[chave]->proximaVenda = novaVenda;
    }
}

void interpretaVenda(struct Venda venda){

    int i;

    int codigoArtigo = venda.codigoArtigo;
    int quantidadeVendida = venda.quantArtigo;
    double montanteVenda = venda.montanteTotal;

    if(existeVenda(codigoArtigo)==0){
        RegistoVenda *novaVenda = inicializaVenda();

        novaVenda->codigo = codigoArtigo;
        novaVenda->quantidadeTotal = quantidadeVendida;
        novaVenda->montanteTotal = montanteVenda;
        
        insereVenda(novaVenda);
    }
    // Caso o codigo de venda ja exista.
    else{
        for(i=0; i<SIZE; i++){
            if (conjuntoVendas[i]->codigo == codigoArtigo){
                conjuntoVendas[i]->quantidadeTotal += quantidadeVendida;
                conjuntoVendas[i]->montanteTotal += montanteVenda;
            }
        } 
    }
}

void imprimeVendasAgregadas(){
    int i;

    for(i=0; i<SIZE; i++){
        if(conjuntoVendas[i]->codigo != EMPTY){
            int codigoArtigo = conjuntoVendas[i]->codigo;
            int quantidadeTotal = conjuntoVendas[i]->quantidadeTotal;
            double montanteTotal = conjuntoVendas[i]->montanteTotal;
            printf("Artigo %d. Quantidades Adquiridas: %d; Montante Total: %f\n", codigoArtigo, quantidadeTotal, montanteTotal);
        }
    }
}

int main(int argc, char** argv) {

    inicializaVendas(conjuntoVendas);

    struct Venda vendaLida;

    int ficheiroVendas = open("vendas.txt", O_RDONLY, 0777);

    while(read(ficheiroVendas, &vendaLida, sizeof(struct Venda))) interpretaVenda(vendaLida);
    
    imprimeVendasAgregadas();

    return 0;
}

