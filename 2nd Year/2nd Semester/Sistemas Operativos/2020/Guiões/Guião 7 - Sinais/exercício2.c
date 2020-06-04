#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

int processosFilhos[5];

void terminaProcessos()
{
    for (int i = 0; i <= 5; i++)
    {
        if (processosFilhos[i] != 0)
        {
            printf("\nkill pid %d\n", processosFilhos[i]);
            kill(processosFilhos[i], SIGKILL);
        }
    }
    //_exit(0);
}

int main(int argc, char *argv[])
{
    char *palavra = argv[1];
    char *ficheiro = argv[2];

    int i;
    int status;

    // Criamos 5 processos filhos todos de uma vez.
    for (i = 0; i <= 5; i++)
    {

        processosFilhos[i] = fork();

        if (processosFilhos[i] == 0)
        {
            if (fork() == 0)
            {
                printf("Eu sou o %d\n", getpid());
                execlp("grep", "grep", palavra, ficheiro, NULL);
            }
            else
            {
                wait(NULL);
                terminaProcessos();
                return 0;
                //printf("AAAAA\n");

                //wait(NULL);
                //signal(SIGKILL, terminaProcessos);
            }
        }

        //_exit(i);
    }

    /*
    for (i = 0; i <= 5; i++)
    {
        return (0);
    }
    */

    return 0;
}
