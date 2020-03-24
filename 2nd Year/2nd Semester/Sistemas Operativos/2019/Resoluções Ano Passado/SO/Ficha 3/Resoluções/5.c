#include <unistd.h>
#include <stdio.h>

/* Implemente um programa que execute concorrentemente uma lista de execut ́aveis especificados como
argumentos da linha de comando. Considere os execut ́aveis sem quaisquer argumentos pr ́oprios. O
programa dever ́a esperar pelo fim da execuc ̧ a  ̃ o de todos processos por si criados. */

// int execlp(const char *file, const char *arg0, ..., NULL);
int main(int argc, char *argv[]) {
	
	int i,total = argc,pid;

	for(i=1;i<total;i++) {
		pid = fork();
		if(pid == 0) execlp(argv[i],argv[i],NULL);
	}

	for(i=1;i<total;i++) {
		wait(NULL);
	}
}

