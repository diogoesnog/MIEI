#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argn, char* args[]){
	int i=1;

	while(args[i]!=NULL && args[i+1]!=NULL){
		if(fork()==0){
			execlp("cmp","cmp", args[i], args[i+1], NULL );
			perror("cmp");
		}else wait(NULL);

		i++;
	}
}