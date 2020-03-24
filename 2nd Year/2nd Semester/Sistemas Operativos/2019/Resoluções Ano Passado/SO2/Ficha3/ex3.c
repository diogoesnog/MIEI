#include <unistd.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
// 3.
int main(int argc, char* argv[]){

	if (argc<2){
		fprintf(stderr, "Necessita de mais argumentos\n");
		return 1;
	}
	int i = 1;
	while (argv[i]){
		write(1,argv[i],strlen(argv[i]));
		printf("\n");
		i++;
	}
	return 0;
}