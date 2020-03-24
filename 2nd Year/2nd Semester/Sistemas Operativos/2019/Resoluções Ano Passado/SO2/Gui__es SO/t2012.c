#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

int main(){
	char* instrucao = strdup("ls -la | cut -c 20-30 | grep -v echelinho");
	char** comandos = (char**) malloc(sizeof(char*));
	char** executar = (char**) malloc(sizeof(char*));
	char* s; 
	int i, n, pd[2];

	s = strtok(instrucao, "|");
	for(i=0; s!=NULL; i++){
		comandos[i] = (char*) malloc(strlen(s)*sizeof(char*));
		strcpy(comandos[i], s);
		s = strtok(NULL, "|");
	}
	comandos[i] = NULL;

	while(*(comandos+1)!=NULL){
		pipe(pd);
		if(fork()==0){
			close(pd[0]);
			dup2(pd[1],1); close(pd[1]);

			s = strtok(*(comandos), " ");
			for(i=0; s!=NULL; i++){
				*(executar+i) = (char*) malloc(strlen(s)*sizeof(char));
				strcpy(*(executar + i), s);
				s = strtok(NULL, " ");
			}
				executar[i] = NULL;

			execvp(executar[0], executar);
			perror(executar[0]);
			_exit(1);
		}else{
			close(pd[1]);
			dup2(pd[0],0); close(pd[0]);
			comandos++;
		}
	}

	s = strtok(*(comandos), " ");
	for(i=0; s!=NULL; i++){
		*(executar+i) = (char*) malloc(strlen(s)*sizeof(char));
		strcpy(*(executar + i), s);
		s = strtok(NULL, " ");
	}
	executar[i] = NULL;

	execvp(executar[0], executar);
	perror(executar[0]);
	return 0;
}