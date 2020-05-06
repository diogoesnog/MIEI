#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main() {

    // Cria-se um novo processo.
    int pid = fork();

    // Quando o fork da 0 e o filho.
    if(pid==0) printf("Filho -> Meu PID: %d / PID meu pai: %d\n",getpid(), getppid());
    else{
        printf("Pai -> Meu PID: %d / PID meu pai: %d\n" , getpid(), getppid());
    }

    return 0;
}