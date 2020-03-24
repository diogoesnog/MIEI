#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(){
	int i;
	pid_t pid;

	pid = fork();
	for(i=0; i!=10;i++){
		if(pid==0){
			printf("Sou o filho %d, pid: %d, ppid: %d\n",i+1, getpid(), getppid() );
			pid = fork();
		}else {wait(NULL);}
	}
	return 0;
}