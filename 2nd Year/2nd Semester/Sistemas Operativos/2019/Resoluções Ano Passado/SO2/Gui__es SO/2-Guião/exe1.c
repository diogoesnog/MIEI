#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(){
		printf("Pid: %d, Pid pai: %d\n",getpid(), getppid());

		return 0;
}