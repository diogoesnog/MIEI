#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
/* chamadas ao sistema: defs e decls essenciais */
/* chamadas wait*() e macros relacionadas */

int main(int argc, char *argv[]) {
	
	int pid;
	
	pid = fork();
	
	if (pid < 0) { perror("Fork falhou"); return 0; }
	if (pid == 0) { printf("Sou o filho, com pid %i e o meu pai tem pid %i\n",getpid(),getppid()); return 0; }
	else { wait(NULL) ; printf("Sou o pai tenho pid %i e o meu filho tinha pid %i\n",getpid(), pid); }
	
	return 1;
	
	
	
}