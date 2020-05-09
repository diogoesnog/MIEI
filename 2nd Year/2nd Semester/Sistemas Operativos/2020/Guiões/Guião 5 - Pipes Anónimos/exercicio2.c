#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>

int main() {
	
	int pd[2];
	char buffer[1024];
	int stringLida;
    int stringEnvio;
	int i;

	// Criação do Pipe Anónimo.
	pipe(pd);

	// Criação do Processo Filho.
	int pid = fork();

	// Erro ao fazer o fork
	if(pid < 0){
		perror("fork");
		exit(1);
	}

    // Caso seja o Proceso Filho.
    if (pid == 0) {

		// Fecha o canal de escrita.
		// Dado que só vai ler.
        close(pd[1]);

        while ((stringLida = read(pd[0], buffer, sizeof(buffer))) > 0) {
            write(1, buffer, stringLida);
        }

		// Como já terminou de ler, fecha o canal de leitura.
        // Termina o seu processo.
        close(pd[0]);
        _exit(0);
    }
    
    // Caso seja o Processo Pai.
    else {
        
        // Fecha o canal de leitura.
        // Dado que vai escrever.
        close(pd[0]);

        while ((stringEnvio = read(0, buffer, 1024)) > 0) {
            write(pd[1], buffer, stringEnvio);
        }

        close(pd[1]);
    }
}
