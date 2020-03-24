#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argn, char* args[]){
	char buffer[512];
	int fd, n, i = 1;
	char *s = NULL;
	if(args[1] == NULL){
		while((n=read(0,buffer, 512)) > 0 ){
			printf("   %d   %s\n", i++, buffer);
			for(n=0; n!=512; buffer[n++] = '\0');
		}
	}

	fd = open(args[1], O_RDONLY);
	n=read(fd, buffer, 512);
	if(n>0)
		s = strtok(buffer, "\n\0");
		while(s!=NULL){ 
			//printf("%s\n", s);
			printf("   %d   %s\n", i++, s);
			s = strtok(NULL, "\n\0");
		}

	return 0;
}