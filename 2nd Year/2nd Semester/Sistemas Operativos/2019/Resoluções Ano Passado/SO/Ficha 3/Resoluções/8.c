#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

	int total = argc, i,pid,status;
	int run[argc], contador[argc];
	
	for(i=1;i<argc;i++) {
		contador[i] = 0;
		while(run[i] != 0) {
		pid = fork();
		if(pid==0) { execlp(argv[i],argv[i],NULL); }
		else { 
			waitpid(pid,&status,0);
			if(WIFEXITED(status)) { run[i] = WEXITSTATUS(status); contador[i]++;}
			}
		}
	}
	printf("O programa executou:\n");
	for(i=1;i<argc;i++) {
		printf("\n %s %i",argv[i],contador[i]);
	}
	printf("\n");

}