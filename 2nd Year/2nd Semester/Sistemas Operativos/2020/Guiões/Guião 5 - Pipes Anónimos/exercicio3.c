#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>

int main(){

	int pd[2];
	char buffer[1024];
	int pid;
	int stringLida, i, ficheiro;

	char *nomeFicheiro = "resultados.txt";

	// Criação do Pipe Anónimo.
	pipe(pd);

	// Criação de um Processo Filho.
	pid = fork();

	// Caso seja o Processo Pai.
	// Pai vai enviar ao Filho.
	// Pai envia o que é lido do stdin.
	if(pid > 0){
	
		// Fecha o canal de leitura.
		// Dado que só vai escrever/enviar.
		close(pd[0]);

		while( (stringLida = read(0, buffer, sizeof(buffer))) > 0 )
			write(pd[1], buffer, stringLida);
	}

	// Caso seja o Processo Filho.
	else{

		// Redirecionar o canal de Leitura do Pipe.
		// Vai ler do stdin do terminal.
		dup2(pd[0], 0);

		// Fecha o canal de leitura.
		// Dado que vai ler do stdin.
		// Depois de redirecionar podemos fechar o canal.
		close(pd[0]);

		for(i = 0; i != 1024; i++) buffer[i]='\0';

		while( (stringLida = read(0, buffer, sizeof(buffer))) > 0 ){

			ficheiro = open(nomeFicheiro, O_CREAT | O_TRUNC | O_RDWR, 0666);
			write(ficheiro, buffer, stringLida);

			pid = fork();	

			if(pid == 0){

				execlp("wc", "wc", nomeFicheiro, NULL);
				perror("wc");
				_exit(1);
			} 
			else wait(NULL);

		}
	}

	return 0;
}