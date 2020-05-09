#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> /* random */
#include <sys/wait.h>

int main(int argc,char * argv[]) {

	if (argc < 2) {
		perror("Falta os argumentos.");
		return (-1);
	}

	int i;

	for(i = 1; i < argc; i++) printf("%s\n", argv[i]);
	
	return 0;

}