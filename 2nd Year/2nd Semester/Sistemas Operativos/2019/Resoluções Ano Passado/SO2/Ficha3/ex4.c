#include <unistd.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 4. 
int main(int argc, char * argv[]){
	
	argv[0] = (char*) malloc(strlen("E começou")*sizeof(char));
	strcpy(argv[0], "E começou");
	execvp("./ex3",argv);

return 0;
}