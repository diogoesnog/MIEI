#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(){
	int pid,status;
	int i;

	pid = fork();

	for(i=0;i<10;i++){
		if(pid==0){
			printf("Eu sou o filho com pid : %d e o meu pai tem pid :%d\n",getpid(),getppid() );
			pid = fork();
		}
		else
			wait(NULL);
	}
	return 0;
}