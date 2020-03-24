#include <unistd.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

// 2.
int main(){
	

	//Eu sou o filho
	if(fork()==0){
		printf("Eu sou o filho\n");
		execl("/bin/ls","ls","-l",NULL);
		_exit(1);
	}
	else{
		wait(NULL);
		printf("Eu sou o pai\n");
	}
	
	return 0;
}
