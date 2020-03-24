#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
/* chamadas ao sistema: defs e decls essenciais */
/* chamadas wait*() e macros relacionadas */

/* Implemente um programa que crie uma descendˆencia em profundidade de dez processos, ou seja, o
processo cria um filho, este filho cria outro, e assim por diante at ́e ao d ́ecimo n ́ıvel de descendˆencia.
Cada processo dever ́a imprimir o seu pid e o pid do seu pai. Se desejar, poder ́a obrigar cada processo a
esperar pelo fim da execuc ̧ a  ̃ o do seu (eventualmente) u  ́ nico filho. */

int main(int argc, char *argv[]) {
	
	int pid,i=0,status;
	
	for(i=0;i<10;i++) {
		pid=fork();
		if(pid>0) { 
				wait(NULL); 
				if(WIFEXITED(status))	printf("Terminou o filho numero: %i\n",WEXITSTATUS(status)); 
				exit(0); 
		} 
		printf("Sou o filho numero %i, com pid %i e o meu pai tem pid %i\n",i, getpid(),getppid());
		if (i==9) _exit(0);
		
	}
	
	return 0;
	
	
}