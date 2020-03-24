#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(){

	execlp("/home/ls", "ls", "-l", NULL);

	return 0;
}