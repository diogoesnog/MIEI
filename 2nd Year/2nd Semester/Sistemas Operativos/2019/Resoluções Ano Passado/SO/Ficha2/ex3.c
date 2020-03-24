#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
/*
 * _exit(status) - termina o processo filho devolvendo uma valor de saida
 * wait(*status) - guarda no status o codigo de terminação do processo filho
 * WIFEXITED(status) - verdadeiro se o filho terminou normalmente. Falso, caso contrário
 * WEXITSTATUS(status) - devolve o exit_status do processo filho
 */

int main(){
	int i,status;
	int pid;
	
	for (i=0;i<10;i++){
		if ((pid=fork())==0){
			printf("Eu sou o filho %d e o meu pid é : %d\n",i,getpid());
			printf("O pid do meu pai é : %d\n",getppid() );
			_exit(i+1);
		}
		else {
			wait(&status);
			if (WIFEXITED(status))
			printf("Eu sou o pai e o valor de retorno do meu filho é : %d\n",WEXITSTATUS(status));
		}
	}

	return 0;

}