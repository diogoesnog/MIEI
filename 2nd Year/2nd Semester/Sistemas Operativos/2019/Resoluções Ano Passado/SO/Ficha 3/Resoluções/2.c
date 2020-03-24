#include <unistd.h>
#include <stdio.h>

// int execlp(const char *file, const char *arg0, ..., NULL);

//faz um ls -l num filho
int main(int argc, char *argv[]) {

	int pid;
	pid = fork();
	if(pid == 0) execlp("ls","ls","-l",NULL);
	
	printf("\n");
	return 1;
}