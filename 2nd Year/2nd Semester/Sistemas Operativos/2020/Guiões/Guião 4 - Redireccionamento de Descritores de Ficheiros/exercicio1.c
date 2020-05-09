#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char const *argv[]) {
	
	int stdin, stdout, stderr, n;
	char buffer[1024];

	stdin = open("/etc/passwd", O_RDONLY);	
	stdout = open("saida.txt", O_RDWR|O_TRUNC|O_CREAT);	
	stderr = open("erros.txt", O_RDWR|O_CREAT|O_TRUNC);

	// O nosso input será o conteúdo do ficheiro passwd.
	dup2(stdin, 0); 
	dup2(stdout, 1);
	dup2(stderr, 2);

	while( (n = read(0, buffer, 1024)) > 0 )
		write(1, buffer, n);

	// Caso exista algum erro na leitura por parte do input.
	if (n < 0) write(2, buffer, n);
	
	close(stdin); 
	close(stdout);
	close(stderr);

}