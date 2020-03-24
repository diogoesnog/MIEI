#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

int main(){
	int fd1, fd2, n;
	char buffer[1014];
	char *s = "\n";

	fd1 = open("fifo", O_RDONLY);
	fd2 = open("log.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);

	dup2(fd2, 1); close(fd2);
	dup2(fd1,0); close(fd1);

	while((n=read(0, buffer, sizeof(buffer)))>0){
		write(1, buffer, n);
	}
	
	return 0;
}