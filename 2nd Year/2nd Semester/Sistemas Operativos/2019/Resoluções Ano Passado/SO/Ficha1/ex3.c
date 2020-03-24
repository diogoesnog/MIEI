#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>  //atoi

int main(int argc, char * argv[]){

	if (argc < 2){
		fprintf(stderr, "Nome de ficheiro em falta e/ou nº de bytes\n");
		return -1;
	}

	int size = atoi(argv[1]);
	char buffer[size];
	int n;
	while((n=read(0,&buffer,size)) > 0){
		write(1,&buffer,n);
	}

	return 0;
}