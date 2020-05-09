#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(){
    
    // O programa cria um processo filho.
    int pid = fork();
 
    if(pid < 0) { printf("Fork sofreu uma falha."); return 0; }
    
    // Processo Filho
    // Imprime seu identificador e o do seu pai
    if(pid == 0){
        printf("Sou o processo filho e o meu pid é = %d. O pid do meu processo pai é = %d\n", getpid(), getppid());
    }
    // Processo Pai
    // Imprime o seu identificador e do seu pai
    else {
        //wait(NULL); // Retorna o PID do Processo Filho que saiu.
        printf("Sou o processo pai e o meu pid é = %d. O meu filho tinha pid = %d\n", getpid(), pid);
    }

    return 1;
}