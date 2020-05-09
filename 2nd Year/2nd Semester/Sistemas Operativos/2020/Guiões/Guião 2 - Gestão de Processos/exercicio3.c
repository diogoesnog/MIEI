#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

/*
 * _exit(status) - Termina o processo filho devolvendo uma valor de saida.
 * wait(*status) - Guarda no status o codigo de terminação do processo filho e retorna o pid do processo filho que terminou.
 * WIFEXITED(status) - Verdadeiro se o filho terminou normalmente. Falso, caso contrário.
 * WEXITSTATUS(status) - Devolve o exit_status do processo filho.
 */

int main() {

    int i;
    int pid;
    int status;

    // Criar 10 processos filhos
    for(i = 1; i <= 10; i++) {

        // Cria-se um Processo Filho a partir do Processo Pai atual.
        pid = fork();

        if(pid == 0) {
            printf("Eu sou o processo filho número %d e o meu pid é = %d\n", (i), getpid());
            printf("O pid do meu processo pai é = %d\n", getppid());
            _exit(i);
        }
        else {
            // A variável status é o que foi atualizado no exit do processo filho.
            // Daí dar o mesmo valor do i.
			pid_t filho = wait(&status);

			if (WIFEXITED(status)){
                printf("Eu sou o pai e o valor de retorno do meu filho é : %d\n", WEXITSTATUS(status));
                printf("E o seu PID é : %d\n", filho);
                printf("-------------------------------------------------------\n");
            }
		}
    }

    return 0;
}