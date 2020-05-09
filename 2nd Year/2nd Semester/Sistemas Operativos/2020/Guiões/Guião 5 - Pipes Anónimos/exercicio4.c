#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>

int main() {

	int pd[2];
	char buffer[1024];
	int pid;

	// Criação do Pipe Anónimo.
	pipe(pd);
	
	// Criação do Processo Filho.
	pid = fork();

	// Processo Filho.
	// Vai enviar a execução do primeiro comando ao Processo Pai.
	if(pid == 0){
		
		// Fecha-se o canal de leitura.
		// Dado que só vai usar o de Escrita.
		close(pd[0]);

		// O nosso canal de Escrita passa a ser o output do terminal em si.
		// Logo, o que supostamente daria em terminal, é enviado pelo canal.
		dup2(pd[1], 1);

		// Como já redirecionamos.
		// Fecha-se o canal de Escrita.
		close(pd[1]);

		// O resultado do terminal stdout já está a ser mandando pelo canal de Escrita do Pipe.
		execlp("ls", "ls", "/etc", NULL);
		perror("ls");

		_exit(1);
	}

	// Caso seja o Processo Pai.
	else{
		
		// Fecha-se o canal de Escrita.
		// Dado que apenas vai ler do canal de Leitura.
		close(pd[1]);

		// Como recebemos pelo canal o output do primeiro comando.
		// Redirecionamos esse output para o terminal em si, de modo a poder fazer o segundo comando e imprimir no terminal.
		dup2(pd[0],0);

		execlp("wc", "wc", "-l", NULL);
		perror("wc");
	}

	return 0;
}