#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){
	char buffer[1024];
	int n;
	puts("usar ctrl-D para sair");
	while( (n=read(0, buffer, 1024)) > 0 ){
		write(1,buffer, n);
	}

	return 0;
}