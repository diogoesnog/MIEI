#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
	int i=0;

	while(argv[i]!=NULL){
			puts(argv[i]);
			putchar('\n');
			i++;
	}

	return 0;
}