#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(){

	int pid; 
    int status;
	int i;

	pid = fork();

	for(i=0; i<2; i++){
		int j = 0;
        // Caso seja o filho, cria-se um processo filho do mesmo.
        // Este processo filho passa a ser o processo pai do novo que criou.
		if(pid==0){
			printf("Eu sou o processo filho com pid = %d e o meu pai tem pid = %d\n",getpid(), getppid());
			
			pid = fork();

			printf("Sou %d. O meu i está em %d\n", getpid(), i);
		}
        // Processo espera pelo fim da execução do seu único filho.
		else {
			wait(NULL);
			printf("FODASE - %i\n", getpid());
		}
	}
    
	return 0;
}