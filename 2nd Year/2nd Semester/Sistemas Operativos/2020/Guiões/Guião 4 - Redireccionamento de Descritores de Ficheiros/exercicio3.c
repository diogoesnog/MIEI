#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>

int main() {

	int stdin, stdout, stderr, n;
	char buffer[1024];

	stdin = open("/etc/passwd", O_RDONLY);	
	perror("/etc/passwd");
	dup2(stdin, 0); 

	stdout = open("saida.txt", O_RDWR|O_TRUNC|O_CREAT, 0666);	
	perror("saida.txt");
	stderr = open("erros.txt", O_RDWR|O_CREAT|O_TRUNC, 0666);
	perror("erros.txt");
	dup2(stdout, 1);
	dup2(stderr, 2);

	close(stdin);
	close(stdout);
	close(stderr);

	execlp("wc", "wc", NULL);

	return 0;
}