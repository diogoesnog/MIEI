#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>


int main(int argn, char* args[]){
	char buffer[10];
	int pd[2], res, r, n, i;
	pipe(pd);

	if(argn==1){
		puts("sem argumentos");
		return (-1);
	}

	for(i=1; i!=argn; i++){ 
		if(fork()==0){
			execlp(args[i], args[i], NULL);
			perror(args[i]);
		}
	}

	for(i=0; i!=argn; i++) wait(NULL);

	return 0;
}