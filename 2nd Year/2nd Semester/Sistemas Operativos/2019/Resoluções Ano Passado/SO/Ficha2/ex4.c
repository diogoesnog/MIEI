#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(){
	int pid[10];
	int i,status;

	for(i=0;i<10;i++){
		if ((pid[i] = fork())==0){
			printf("Eu sou o FILHO %d caraigoo e o meu pid é : %d \n",i+1,getpid() );
			_exit(i+1);
		}
	}

	for(i=0;i<10;i++){
		waitpid(pid[i],&status,0);
		if(WIFEXITED(status))
			printf("O filho %d retornou %d\n",pid[i],WEXITSTATUS(status) );
	}
return 0;
}