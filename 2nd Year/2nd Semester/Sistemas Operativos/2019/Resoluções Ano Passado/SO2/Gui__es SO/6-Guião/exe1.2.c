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
	char buffer[1024];
	int n, fd;

	fd = open("fifo", O_WRONLY);
	while((n=read(0,buffer, sizeof(buffer)))>0){
		write(fd, buffer, n);
	}

	return 0;
}