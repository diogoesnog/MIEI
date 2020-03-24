#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>

int main(){
	int n, fd, stdOut, stdErr;
	char buffer[1024];

	fd = open("/etc/passwd", O_RDONLY);
	perror("/etc/passwd");
	dup2(fd, 0);

	stdOut = open("saida.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	perror("saida.txt");
	stdErr = open("erros.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	perror("erros.txt");
	dup2(stdOut, 1);
	dup2(stdErr, 2);



	close(fd);
	close(stdOut);
	close(stdErr);


	return 0;
}