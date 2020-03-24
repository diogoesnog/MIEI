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

	pipe(pd);

	pid = fork();

	if(pid > 0){
	
		close(pd[0]);

		while( (stringLida = read(0, buffer, sizeof(buffer))) > 0 )
			write(pd[1], buffer, stringLida);
	}
	else{

		dup2(pd[0], 0);

		// Fechamos o canal de leitura porque vamos escrever no pipe.
		close(pd[0]);

		for(i=0; i!=1024; i++) buffer[i]='\0';

		while( (stringLida = read(0, buffer, sizeof(buffer))) > 0 ){

			ficheiro = open(nomeFicheiro, O_CREAT | O_TRUNC | O_RDWR, 0666);
			write(ficheiro, buffer, stringLida);

			pid = fork();	

			if(pid == 0){
				execlp("wc", "wc", nomeFicheiro, NULL);
				perror("wc");
				_exit(1);
			} else wait(NULL);

		}
	}

	return 0;
}