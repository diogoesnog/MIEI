#include <unistd.h> 
#include <stdio.h>
#include <fcntl.h>
/* 
int dup(int fd);
int dup2(int fd1, int fd2); */

/*
1.c mas executar wc sem argumentos, mantem os fd */

int main(int argc, char const *argv[])
{
	/* code */
	int stdin,stdout,stderr,n;
	int novo;
	char buffer[1024];

	novo = open("entrada.txt", O_RDWR|O_TRUNC|O_CREAT,0666);
	write(novo, "OLAAAAAA", 8);

	stdin = open("entrada.txt", O_RDONLY);	
	stdout = open("saida.txt", O_RDWR|O_TRUNC|O_CREAT,0666);	
	stderr = open("erros.txt",O_RDWR|O_CREAT|O_TRUNC,0666);
	dup2(stdin,0); //saida,entrada
	dup2(stdout,1);
	dup2(stderr,2);
	execlp("wc","wc",NULL);



	while((n=read(stdin,buffer,1024)) > 0 ) {
			 write(stdout, buffer, n);
	  	}
		  
	if (n < 0) write(stderr,buffer,n);
		 close(stdin); 
		 close(stdout);
		 close(stderr);





}