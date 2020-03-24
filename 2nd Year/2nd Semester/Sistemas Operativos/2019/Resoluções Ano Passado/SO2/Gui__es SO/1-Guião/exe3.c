#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int arg){
	char buffer[arg];
	int lidos; 

	while((lidos = read(0,buffer, arg)) != arg ) {
		read(0,buffer, arg-lidos);
		printf("lidos %d\n", lidos );
	}

	write(1, buffer, arg);
	return 0;
}