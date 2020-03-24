#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(){

	if(fork()==0){
		puts("sou o filho da sofia");
		execlp("ls", "ls", "-l", NULL);
		//perror("ls");
		_exit(1);
	}else{
		wait(NULL);
		puts("Pai após o filho invocar o ls");
	}
	
	return 0;
}
