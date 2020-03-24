#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>


int main(){
	int i,status;
	pid_t pid;

	for(i=0; i!=10; i++){
		if((pid=fork())==0){ // if(!fork()){
			printf("Sou o filho\nPid: %d, Pid Pai: %d\n",getpid(), getppid());
			_exit(i+1);
		}else{
			wait(&status);
			if(WIFEXITED(status))
				printf("Sou o Pai\nO filho %d retornou: %d\n",pid, WEXITSTATUS(status));
		}
	}

	return 0; // o stor nao meteu
}