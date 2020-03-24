#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

/*
 * pid == 0 : processo filho
 * pid 1= 0 : processo pai
 * wait(NULL) : o pai espera que qualquer filho termine
 */

int main(){
	int pid;
	pid = fork();

	if (pid==0){
		printf("Eu sou o filho e o meu pid é = %d, o pid do meu pai é : %d\n",getpid(),getppid());
		_exit(1);
	}
	else {
		wait(NULL);
		printf("Eu sou o pai e o meu pid é = %d, o pid do meu pai é : %d\n",getpid(),getppid() );
		printf("O pid do meu filho é = %d\n",pid );
	}
	return 0;
}