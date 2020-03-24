#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
/*
int main(void){
	int i;
	//processo id
	pid_t pid;

	//erro na criação do processo filho
	if ((pid= fork())<0){
		perror("erro no fork");
		exit(1);
	}

	//Processo filho irá executar este if
	if(pid == 0){
		printf("pid do Filho: %d\n",getpid() );
		
	}
	// Processo pai vai executar este else
	else {
		printf ("pid do Pai: %d\n", getpid());
	}

	printf ("Esta região será executado por ambos processos \n\n");
	
	scanf("%d",&i);
	// caso de sucesso
	exit(0);
}


int main(void){

	int i,p;
	
		p = fork();
		if (p!=0)
		printf("myPID= %d, son or self = %d\n",getpid(),p);
	
	
	return 0;
}
*/

int main(){
	printf("Filho= %d, pai = %d\n",getpid(),getppid());
}
