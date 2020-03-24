#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>

int main(){
	char *instrucao = strdup("grep -v ^# /etc/passwd | cut -f7 -d: | uniq | wc -l");
	//write(1, instrucao, strlen(instrucao));
	char *s, *aux;
	int i, r, n, pd[2];
	char** comandos = (char**) malloc(sizeof(char*));
	char** executar = (char**) malloc(sizeof(char*));

	s = strtok(instrucao, "|");
	for(i=0; s!=NULL; i++){
		comandos[i] = (char*) malloc(strlen(s)*sizeof(char));
		strcpy(comandos[i], s);
		s = strtok(NULL, "|");
	}
	comandos[i] = NULL;

	while(*(comandos+1)!=NULL){
		pipe(pd);
		if(fork()==0){
			//dup2(pd[1], 1);
			aux = strdup(comandos[r]);
			s = strtok(aux, " ");
			for(i=0; s!=NULL; i++){
				executar[i] = (char*) malloc(strlen(s)*sizeof(char));
				strcpy(executar[i], s);
				s = strtok(NULL, " ");
			}	executar[i] = NULL;
			close(pd[0]);
			dup2(pd[1], 1); close(pd[1]);

			execvp(executar[0], executar);
			perror(executar[0]);
			_exit(1);
		}
		else {
			close(pd[1]);
			dup2(pd[0], 0); close(pd[0]);
			comandos++;
		}
	}

	aux = strdup(comandos[r]);
	s = strtok(aux, " ");
	for(i=0; s!=NULL; i++){
		executar[i] = (char*) malloc(strlen(s)*sizeof(char));
		strcpy(executar[i], s);
		s = strtok(NULL, " ");
	}	executar[i] = NULL;

	execvp(executar[0], executar);
	perror(executar[0]);

	return 0;
}