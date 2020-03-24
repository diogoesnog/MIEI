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
	int stringLida;
	int i;

	pipe(pd);

	// Erro ao fazer o fork
	if((pid = fork()) < 0){
		perror("fork");
		exit(1);
	}

	if(pid == 0){

		close(pd[1]);

		/** Conseguimos demonstrar que se não existir nada no canal de leitura
		do pipe, ao colocarmos a verficação de EOF, ele termina a execução. */
		while( (stringLida = read(pd[0], buffer, sizeof(buffer))) > 0 ){
			write(1, buffer, stringLida);
		}
		_exit(0);
	}

	close(pd[0]);

	for(i=0; i!=4; i++){

		sleep(2);	 
		char *stringLida = "Tentei ler do canal de saída do pipe.\n";
		write(pd[1], stringLida, strlen(stringLida));
	}

	return 0;
}
