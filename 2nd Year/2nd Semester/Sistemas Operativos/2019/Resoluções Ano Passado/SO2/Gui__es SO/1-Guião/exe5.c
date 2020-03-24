#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int myreadLine(){
	char buffer[512];
	int i = 1;

	read(0, buffer, 1);
	while( (i!= 512) && (buffer[i-1]!='\n') ){
		read(0, buffer+i, 1);
		i++;
	}
	return --i;
}

int readlinha(int fd, char* buffer, int max){
	int i=1;
	int n;
	n=read(fd, buffer, 1);
	while(i<max && buffer[i-1]!='\n'){
		n=read(fd,buffer+i,1);
		i++;	
	}
	buffer[i]=0;
	return i-1;	
}

int main(void){
	char buffer[512];

	printf("myreadLine: %d\n", myreadLine() );
	printf("readlinha: %d\n", readlinha(0, buffer, 512) );
	printf("%s\n",buffer);
	return 0;
}
