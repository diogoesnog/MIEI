#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>


int main(int argn, char* args[]){
	int i = 2;

	while(args[i]!=NULL){
		if(fork()==0){
			execlp("head", "head", args[1], args[i], NULL);
			perror("head");
		}else wait(NULL);

		i++;
	}	

	return 0;
}