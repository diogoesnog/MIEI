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
	int n, fd, i=0;

	fd = open("fifo", O_RDONLY);

	while((n=read(fd,buffer, sizeof(buffer)))>0 && i!=10){
		write(1, buffer, n); i++;
	}

	return 0;
}