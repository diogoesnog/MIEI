#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
/* chamadas ao sistema: defs e decls essenciais */
/* chamadas wait*() e macros relacionadas */

/* Implemente um programa que crie dez processos filhos que dever ̃ao executar (potencialmente) em con-
corrˆencia. O pai dever ́a esperar pelo fim da execuc ̧ a  ̃ o de todos os seus filhos, imprimindo os respectivos
c ́odigos de sa ́ıda.*/

int main(int argc, char *argv[]) {
	
	int pid, i=0,s,status;
	int proc[10];
	
	for (i=0 ; i <10 ; i++) {
		proc[i] = fork();
		if (proc[i]  < 0) { perror("Fork falhou"); return 0; }
		if (proc[i] == 0) { printf("Sou o filho, com pid %i e o meu pai tem pid %i\n",getpid(),getppid()); _exit(i); }

	}
	

	i=0;

	for (i=0 ; i <10 ; i++) {
				waitpid(proc[i],&status,0); 
				if(WIFEXITED(status))
				printf("Terminou o filho com pid %i com o status: %i\n",proc[i],WEXITSTATUS(status)); 
		}


	return 1;
}