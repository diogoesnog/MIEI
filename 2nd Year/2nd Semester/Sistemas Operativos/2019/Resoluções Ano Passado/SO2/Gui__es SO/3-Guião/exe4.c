#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char * argv[]){
	
	argv[0] = (char*) malloc(strlen("E começou")*sizeof(char));
	strcpy(argv[0], "E começou");
	execvp("./exe3",argv);

return 0;
}