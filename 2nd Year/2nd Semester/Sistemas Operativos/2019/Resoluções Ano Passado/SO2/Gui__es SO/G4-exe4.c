#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

int main(int argn, char* args[]){
	/*redir [-i entrada] [-o saida] comando arg1 args2 ... */
	char *s, *fileInput, *fileOutput;
	char** executar = (char**) malloc(sizeof(char*));
	int i, n, fdOut, fdInp, outflag, inpflag;
	outflag = inpflag = 0;
	fileOutput = fileInput = NULL;

	i = 1;
	if(args[i]==NULL){ puts("Sem argumentos"); return -1; }
	
	if(strcmp(args[i], "-i")==0){
		fileInput = (char*) malloc(strlen(args[i++])*sizeof(char));
		strcpy(fileInput, args[i++]);
		inpflag = 1;
	}else{
		if(strcmp(args[i], "-o")==0){
			fileOutput = (char*) malloc(strlen(args[i++])*sizeof(char));
			strcpy(fileOutput, args[i++]);
			outflag = 1;
		}
	}
/*
	if(strcmp(args[i], "-o")==0){
		fileOutput = (char*) malloc(strlen(args[i++])*sizeof(char));
		strcpy(fileOutput, args[i++]);
		outflag = 1;
	}else{
		if(strcmp(args[i], "-i")==0){
			fileInput = (char*) malloc(strlen(args[i++])*sizeof(char));
			strcpy(fileInput, args[i++]);
			inpflag = 1;
		}
	}*/

	if(inpflag!=0){
		fdInp = open(fileInput, O_RDONLY);
		perror(fileInput);
		dup2(fdInp, 0);
		close(fdInp);
	}
	if(outflag!=0){
		fdOut = open(fileOutput, O_CREAT| O_TRUNC | O_WRONLY, 0666);
		perror(fileOutput);
		dup2(fdOut, 1);
		close(fdOut);
	}

	for(n=0; args[i]!=NULL; i++, n++){
		executar[n] = (char*) malloc(strlen(args[i])*sizeof(char));
		strcpy(executar[n], args[i]);
	}
	executar[n] = NULL;

	if(fork()==0){
		execvp(executar[0], executar);
		perror(executar[0]);
		_exit(1);
	}
	else {wait(NULL); }
	return 0;
}