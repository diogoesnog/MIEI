#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>

int main(int argn, char* args[]){
	int i, n, fdOut, fdImp, impFlag = 0, outFlag = 0; 
	char *imputFile = NULL, *outputFile = NULL;
	char **executar;
	executar = (char**) malloc(sizeof(char*));
	if(argn==1){ puts("Sem argumentos"); return -1;	}

	i = 1;
	if(strcmp(args[i], "-i")==0){
		imputFile = (char*) malloc(strlen(args[i++])*sizeof(char));
		strcpy(imputFile, args[i++]);
		impFlag = 1;
	}else{
		if(strcmp(args[i], "-o")==0){
			outputFile = (char*) malloc(strlen(args[i++])*sizeof(char));
			strcpy(outputFile, args[i++]);
			outFlag = 1;
		}
	}

	if(strcmp(args[i], "-o")==0){
		outputFile = (char*) malloc(strlen(args[i++])*sizeof(char));
		strcpy(outputFile, args[i++]);
		outFlag = 1;
	}else{
		if(strcmp(args[i], "-i")==0){
			imputFile = (char*) malloc(strlen(args[i++])*sizeof(char));
			strcpy(imputFile, args[i++]);
			impFlag = 1;
		}
	}

	for(n = 0; args[i]!=NULL; i++, n++){
		executar[n] = (char*) malloc(strlen(args[i])*sizeof(char));
		strcpy(executar[n], args[i]);
	}
	executar[n] = NULL;

	if(impFlag!=0){
		fdImp = open(imputFile, O_RDONLY);
		dup2(fdImp, 0); close(fdImp);
	}
	if(outFlag!=0){
		fdOut = open(outputFile, O_CREAT | O_TRUNC | O_WRONLY, 0666);
		dup2(fdOut, 1); close(fdOut);
	}

	if(fork()==0){
		execvp(executar[0], executar);
		perror(executar[0]);
		_exit(1);
	}else wait(NULL);

	return 0;	
}