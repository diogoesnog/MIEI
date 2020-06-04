#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

int numeroVezes = 0;
int tempoDecorrido = 0;

void printTempoPassado()
{
    numeroVezes++;
    printf("Número de Segundos decorridos: %d\n", tempoDecorrido);
}

void printNumeroVezes()
{
    printf("Número de CTRL+c feitos: %d\n", numeroVezes);
}

void alarme()
{
    tempoDecorrido++;
    alarm(1);
}

int main()
{
    // Em vez de interromper o processo quando se clica em CRTL+C
    // Recorre-se à função printTempoPassado
    signal(SIGINT, printTempoPassado);

    // Em vez de interromper o processo quando se clica em CRTL+\
    // Recorre-se à função printNúmeroVezes
    signal(SIGQUIT, printNumeroVezes);

    // Executa a função alarme de um em um segundo
    signal(SIGALRM, alarme);

    alarm(1);

    while (1)
    {
        pause();
    }

    return 0;
}