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
	int i, j, pd[2];
	char* instrucao = strdup("grep -v ^# /etc/passwd | cut -f7 -d: | uniq | wc -l");
	char** comandos = (char**) malloc(sizeof(char*));
	char** executar = (char**) malloc(sizeof(char*));
	char* s;

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
			close(pd[0]);
			dup2(pd[1],1);
			close(pd[1]);

			s = strtok(*(comandos), " ");
			for(j=0; s!=NULL; j++){
				executar[j] = (char*) malloc(strlen(s)*sizeof(char));
				strcpy(executar[j], s);
				s = strtok(NULL, " ");
			}
			executar[j] = NULL;

			execvp(executar[0], executar);
			perror(executar[0]);
			_exit(1);
		}
		else{
			close(pd[1]);
			dup2(pd[0], 0);
			close(pd[0]);
			comandos++;
		}
	}

	s = strtok(*(comandos), " ");
	for(j=0; s!=NULL; j++){
		executar[j] = (char*) malloc(strlen(s)*sizeof(char));
		strcpy(executar[j], s);
		s = strtok(NULL, " ");
	}
	executar[j] = NULL;

	execvp(executar[0], executar);
	perror(executar[0]);
	
	return 0;

}