#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * O_CREAT : creat file if not exist
 * O_WRONLY : open for writing only
 * O_RDONLY : open for reading only
 * O_APPEND : set append mod
 * O_RDWR : read/write
 */

int main(int argc,char *argv[]){
/* code */
	int n, fd, stdOut, stdErr;
	char buffer[1024];

	fd = open("/etc/passwd", O_RDONLY);
	//perror("/etc/passwd");
	dup2(fd, 0);
	

	stdOut = open("saida.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	perror("saida.txt");
	stdErr = open("erros.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	perror("erros.txt");
	dup2(stdOut, 1);
	
	dup2(stdErr, 2);
	

	while((n=read(fd, buffer, sizeof(buffer))) > 0){
		write(1, buffer, n);
	}

	close(fd);
	close(stdOut);
	close(stdErr);

	return 0;

}