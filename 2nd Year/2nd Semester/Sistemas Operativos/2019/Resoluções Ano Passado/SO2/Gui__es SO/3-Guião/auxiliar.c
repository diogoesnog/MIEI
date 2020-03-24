#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>

int main(int argn, char* args[]){
	int res;
	srandom(time(NULL));
	res = random() % 3;
	printf("%s: %d\n", args[0], res);
	return res;
}

