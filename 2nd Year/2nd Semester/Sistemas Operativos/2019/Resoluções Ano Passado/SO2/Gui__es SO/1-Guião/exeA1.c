#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argn, char *args[]){
	int i =1, fd, n;
	char buffer[512];
	char *s;

	while(args[i]!=NULL){
		fd = open(args[i], O_RDONLY);
		n = read(fd, buffer, sizeof(buffer));
		if(n>0){
			s = strtok(buffer, "\n\0");
			while(s!=NULL){
				write(1, s, strlen(s));
				putchar('\n');
				s = strtok(NULL, "\n\0");
			}
		}
		putchar('\n');
		for(n=0; n!=512; buffer[n++] = '\0');
		i++;
	}

	return 0;
}