#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int n, char *args []){
	int i, fd;
	fd = open(args[1], O_CREAT | O_WRONLY , 0666);

	for(i = 0; i!= 1*8*1024*1024; i++)
		/* i != 1024*1024 ----> write(fd, "aaaaaaaa*, 8); */
		write(fd, "a", 1);

	return 0;
}
