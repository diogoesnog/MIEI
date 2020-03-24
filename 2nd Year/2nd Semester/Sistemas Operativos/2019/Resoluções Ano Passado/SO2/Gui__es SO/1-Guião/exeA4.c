#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int existe(char *a, char* b){
	int r = 0;
	if( strstr(b, a) == NULL) r = 1;
	return r; 
}

int main(int argn, char *args[]){
	int i=2, fd, n;
	char buffer[512];
	char aux[512];
	char *s; 

	if(args[1]!=NULL){

		while(args[i]!=NULL){
			fd = open(args[i], O_RDONLY);
			while((n = read(fd, buffer, sizeof(buffer)))>0){
				s = strtok(buffer, "\n\0");
				while(s!=NULL){
					if(existe(args[1], s) == 0)
						printf("%s: %s\n",args[i], s);
					s = strtok(NULL, "\n\0");
				}

				for(n = 0; n!= sizeof(buffer); buffer[n++] = '\0');
				i++;
			}
			close(fd);
		}

	}

	return 0;
}
