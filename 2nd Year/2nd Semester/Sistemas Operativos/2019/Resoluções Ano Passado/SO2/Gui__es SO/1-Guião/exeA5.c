#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int mywc(int argn, char* args[]){
	int i = 1, fd, n, it, words, lines, chars;
	char buffer[512];

	while(args[i]!= NULL){ 
		fd = open(args[i], O_RDONLY);
		n = read(fd, buffer, sizeof(buffer));
		chars=words=lines=0;

		for(it = 0; it!=n; it++){
			chars++;
			if( buffer[it] == '\n' && buffer[it-1]!='\n') { lines++; words++; }
			if( buffer[it] == ' ' && buffer[it-1]!= ' ') words++;
		}
		printf("%d  %d  %d %s\n", lines, words, chars, args[i]);

		for(it=0; it!=n; buffer[it++] = '\0');
		i++;
	}

	return 0;
}

int main(int argn, char* args[]){
	int i = 1;

	while(args[i]!=NULL){
		if(fork()==0){
			execlp("wc", "wc", args[i], NULL);
			perror("wc");
		}else wait(NULL);

		i++;
	}

	mywc(argn, args);

	return 0;
}