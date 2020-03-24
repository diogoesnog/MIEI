#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

int main(int argn, char* args[] ){
	int fd = -1, i;
	fd = open("fifo", O_WRONLY);

	//if(fd!=-1){
	for(i=0; args[i]!=NULL; i++)
		write(fd, args[i], strlen(args[i]));


	puts("cliente terminou");
	return 0;
}