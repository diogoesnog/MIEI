#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>


void bash(){

	int argumento, i, pid;

	char comando[1024];
	char* executar[512];

 	char* comandoDividido;

	for(i=0; i!=1024; i++) comando[i] = '\0';

	puts("Introduza o seu programa (e os eventuais argumentos).\n");

	while( (argumento = read(0, comando, 1024) ) >0 ){
		
		comandoDividido = strtok(comando, " ");

		for(i=0; comandoDividido!=NULL; i++){

			executar[i] = (char*) malloc(sizeof(char));
			strcpy(executar[i], comandoDividido);

			comandoDividido = strtok(NULL, " ");
		}

		executar[i] = '\0';

		if(strcmp(executar[0], "exit")==0){
			execlp("exit","exit", NULL);
			perror("exit");
		}

		if((pid=fork())==0){
			printf("\nComeçamos a execução do seu programa '%s'\n", executar[0]);
			execvp(executar[0], executar);
		} else wait(NULL);

		
	for(i=0; i!=1024; i++) comando[i] = '\0';

	}
}

int main(void){

	bash();

	return 0;
}