#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> /* random */
#include <sys/wait.h>

int main(int argc,char * argv[]) {

	if(argc<2) {
		fprintf(stderr, "Nomes em falta.\n");
		return (-1);
	}

	argv[0] = "./ex3";

	execvp(argv[0], argv);
}