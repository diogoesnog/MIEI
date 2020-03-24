#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

/*
 * _exit(status) - termina o processo filho devolvendo uma valor de saida
 * wait(*status) - guarda no status o codigo de terminação do processo filho
 * WIFEXITED(status) - verdadeiro se o filho terminou normalmente. Falso, caso contrário
 * WEXITSTATUS(status) - devolve o exit_status do processo filho
 */

int main(){

    int i;
    int pid;
    int status;

    // Criar 10 processos filhos
    for(i=0; i<10; i++){

        // Cria-se um Processo Filho a partir do Processo Pai atual.
        pid = fork();

        if(pid==0){
            printf("Eu sou o processo filho número %d e o meu pid é = %d\n", (i+1), getpid());
            printf("O pid do meu processo pai é = %d\n", getppid());
            _exit(i+1);
        }
        else {
			wait(&status);
			if (WIFEXITED(status))
			printf("Eu sou o pai e o valor de retorno do meu filho é : %d\n",WEXITSTATUS(status));
            printf("-------------------------------------------------------\n");
		}
    }

    return 0;
}