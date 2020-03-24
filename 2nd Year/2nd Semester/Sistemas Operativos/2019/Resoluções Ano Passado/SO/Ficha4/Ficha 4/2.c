#include <unistd.h> 
#include <stdio.h>
#include <fcntl.h>
/* 
int dup(int fd);
int dup2(int fd1, int fd2); */

/*
anterior mas executar pelo filho */

int main(int argc, char const *argv[])
{

	int stdin,stdout,stderr,n,pid;
	char buffer[1024];

	stdin = open("/etc/passwd", O_RDONLY);	
	stdout = open("saida.txt", O_RDWR|O_TRUNC|O_CREAT);	
	stderr = open("erros.txt",O_RDWR|O_CREAT|O_TRUNC);
	dup2(stdin,0); //entrada,saida
	dup2(stdout,1);
	dup2(stderr,2);
	

	if(fork()==0) {
	while((n=read(stdin,buffer,1024)) > 0 ) {
			 write(stdout, buffer, n);
	  	}
	if (n < 0) write(stderr,buffer,n);
	}
		close(stdin); 
		close(stdout);
		close(stderr);





}