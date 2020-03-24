#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *args[]){
	int n, i;

	for(i=1; args[i]!=NULL; i++){
		if(fork()==0){
			execlp(args[i], args[i], NULL);
			//perror(args[i]);
		}
	}

	for(n=0; n!=i; n++) wait(NULL);
	
	return 0;
}