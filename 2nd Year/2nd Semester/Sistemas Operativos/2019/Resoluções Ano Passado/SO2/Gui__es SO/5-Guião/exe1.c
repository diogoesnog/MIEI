#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>

// Processo pai comunica com o processo filho
int paiComunicaFilho(){

	int pd[2];
	char buffer[1024];
	int pid;
	int stringLida;

	pipe(pd);

	// Erro ao fazer o fork
	if((pid = fork()) < 0){
		perror("fork");
		exit(1);
	}

	// É o processo pai
	if(pid > 0){

		// Vamos escrever no pai. Então, fechamos a entrada para leitura do pipe.
		close(pd[0]);

		char *string = "Sou o teu pai e quero falar contigo.\n";

		sleep(5);
		write(pd[1], string, strlen(string));

	}
	// É o processo filho
	else{
		// Vamos ler no filho. Então, fechamos a entrada para escrita do pipe.
		close(pd[1]);

		stringLida = read(pd[0], buffer, sizeof(buffer));

		write(1, buffer, stringLida);
		//printf("O meu pai disse-me isto: %s", buffer);

		_exit(0);
	}

	return 0;
}

// Processo filho comunica com o processo pai
int filhoComunicaPai(){

	int pd[2];
	char buffer[1024];
	int pid;
	int stringLida;

	pipe(pd);

	// Erro ao fazer o fork
	if((pid = fork()) < 0){
		perror("fork");
		exit(1);
	}

	// É o processo pai
	if(pid == 0){

		// Vamos escrever no filho. Então, fechamos a entrada para leitura do pipe.
		close(pd[0]);

		char *string = "Sou o teu filho e quero falar contigo.\n";

		write(pd[1], string, strlen(string));

		_exit(0);

	}
	// É o processo pai
	else{
		// Vamos ler no filho. Então, fechamos a entrada para escrita do pipe.
		close(pd[1]);

		stringLida = read(pd[0], buffer, sizeof(buffer));

		write(1, buffer, stringLida);
		//printf("O meu filho disse-me isto: %s", buffer);

		exit(0);
	}

	return 0;
}

// Apenas para efeitos de teste.
int main(int argc, char const *argv[]){

	paiComunicaFilho();

	return 0;
}