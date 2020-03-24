#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
/* chamadas ao sistema: defs e decls essenciais */
/* chamadas wait*() e macros relacionadas */

int main(int argc, char *argv[]) {
	
	int pid, i=0;
	
	
	for (i=0 ; i <10 ; i++) {
		pid = fork();
		if (pid < 0) { perror("Fork falhou"); return 0; }
		if (pid == 0) { printf("Sou o filho, com pid %i e o meu pai tem pid %i\n",getpid(),getppid()); _exit(i); }
		else { waitpid(pid,NULL,0) ; printf("Terminou o filho com pid %i que era o numero %i\n",pid,i); }
	}
	return 1;
	
	
	
}