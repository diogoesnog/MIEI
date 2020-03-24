#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(){
	pid_t pid;

	if((pid = fork())==0){
		printf("Sou o filho.\n");
		printf("Pid: %d, Pid pai: %d\n",getpid(), getppid());
	}
	else{
		wait(NULL);
		printf("Sou o pai\n");
		printf("Pid: %d, Pid pai: %d\n",getpid(), getppid());
		printf("Pid do filho: %d\n", pid);
		
	}
	return 0;
}