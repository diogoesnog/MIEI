#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main() {

	int processosFilhos[10];
	int i;
	int status;

	// Criamos 10 processos filhos todos de uma vez.
	for(i = 0; i <= 10; i++) {

		processosFilhos[i] = fork();

		if (processosFilhos[i] == 0) {
			printf("Eu sou o processo filho número %d e o meu pid é = %d\n", (i+1), getpid());
			_exit(i);
		}
	}

	for(i = 0; i <= 10; i++) {
		
		// Forçamos o processo pai esperar pelo fim de um processo filho em específico.
		// No caso, iremos fazer isto para cada um dos 10 que criamos acima.
		waitpid(processosFilhos[i], &status, 0);

		// Caso o processo filho em causa tenha terminado bem.
		// Status refere-se ao do processo filho dessa iteração.
		if(WIFEXITED(status))
			printf("O processo filho número %d retornou o exit staus %d\n", processosFilhos[i], WEXITSTATUS(status));
	}

	return 0;
}