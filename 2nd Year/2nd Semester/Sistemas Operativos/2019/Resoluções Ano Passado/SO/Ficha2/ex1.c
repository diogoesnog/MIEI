#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
/*
 * getpid() - pid do processo filho
 * getppid() - pid do processo pai
 */

int main(){
	
	printf("Pid do filho = %d\n",getpid());
	printf("Pid do pai = %d\n",getppid());

	return 0;
}