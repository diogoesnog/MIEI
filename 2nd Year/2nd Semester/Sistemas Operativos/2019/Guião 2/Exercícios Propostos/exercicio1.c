#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h>

int main(){

    int pid = fork();

    // Quando o fork da 0 e o filho.
    if(pid==0) printf("Filho -> Meu PID: %d / PID meu pai: %d\n",getpid(), getppid());
    else{
        printf("Pai -> Meu PID: %d / PID meu pai: %d\n" , getpid(), getppid());
    }

    return 0;

}