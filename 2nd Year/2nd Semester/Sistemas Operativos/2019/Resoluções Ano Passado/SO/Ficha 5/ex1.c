#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

/*
 * 
 */


int main(){

	int fd[2],n;
	
	pipe(fd);
	
	char buf[512];
	
	printf ("Hello\n");
	int pid = fork();
	if (pid == 0){
		close(fd[1]);
		printf("Sou o filho\n");
		n = read(fd[0], cleabuf, sizeof(buf));
		write(1, buf, n);
		_exit(0);
	}
	else {
		close(fd[0]);
		char *s = "TIFANY\n";
		printf("Sou o pai\n");
	//	sleep(5);
		write(fd[1], s, strlen(s));
	}
	
return 0;
}