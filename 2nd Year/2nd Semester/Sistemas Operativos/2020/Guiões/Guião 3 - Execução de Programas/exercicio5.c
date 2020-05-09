#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> /* random */
#include <sys/wait.h>

int main(int argc, char * argv[]) {

	if(argc < 2) {
		fprintf(stderr, "Nome  dos executáveis em falta.\n");
		return (-1);
	}

	int pid,i;

	for(i = 1; i < argc; i++){
		pid = fork();
		if (pid == 0) execlp(argv[i], argv[i], NULL);
	}
	
	for(i = 1; i < argc; i++){
		wait(NULL);
	}
}