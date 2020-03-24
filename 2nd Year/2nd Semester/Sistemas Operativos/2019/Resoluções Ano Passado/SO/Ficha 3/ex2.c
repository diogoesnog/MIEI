#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> /* random */
#include <sys/wait.h>


int main(){
	int pid = fork();

	if (pid==0){
		execlp("ls","ls","-l",NULL);
		_exit(0);
	}
	else{
		wait(NULL);
	}
	return 0;
}