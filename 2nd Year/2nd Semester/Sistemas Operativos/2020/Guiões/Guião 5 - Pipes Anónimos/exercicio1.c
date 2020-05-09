#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>

// Processo Pai comunica com o processo Filho
int paiComunicaFilho(){

	int pid;
	int pd[2];
	char buffer[1024];

	// Criação do Pipe Anónimo.
	pipe(pd);

	// Criação do fork.
	pid = fork();

	// Caso dê erro ao fazer o fork.
	if(pid < 0){
		perror("fork");
		exit(1);
	}

	// Caso seja o processo Pai.
	if(pid > 0) {

		// Vamos escrever no Pai. 
		// Logo fecha-se o canal de leitura.
		close(pd[0]);

		char *stringEnvio = "Sou o teu Pai e quero falar contigo.\n";
		printf("String Enviada para o Filho - %s", stringEnvio);

		sleep(5);

		write(pd[1], stringEnvio, strlen(stringEnvio));
	}

	// Caso seja o processo Filho.
	else{

		// Vamos ler no Filho. 
		// Logos fecha-se o canal de escrita.
		close(pd[1]);

		int stringLida = read(pd[0], buffer, sizeof(buffer));

		write(1, buffer, stringLida);
		printf("String Enviada pelo meu Pai - %s", buffer);

		_exit(0);
	}

	return 0;
}

int main(int argc, char const *argv[]) {

	paiComunicaFilho();

	return 0;
}