#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

/*
 * Pid = 0 : Processo Filho
 * Pid = 1 : Processo Pai
 * wait(NULL) : O Processo Pai espera que o Processo Filho termine
 */


int main(){
    
    int pid = fork();
 
    if(pid < 0) { printf("Fork sofreu uma falha."); return 0; }
    if(pid==0){
        printf("Sou o processo filho e o meu pid é = %d. O pid do meu processo pai é = %d\n", getpid(), getppid());
    }
    else {
        //wait(NULL); // Retorna o PID do Processo Filho que saiu.
        printf("Sou o processo pai e o meu pid é = %d. O meu filho tinha pid = %d\n", getpid(), pid);
    }

    return 1;
}