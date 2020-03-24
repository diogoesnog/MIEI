#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>

int main(){

	int pd[2];
	char buffer[1024];
	int pid;

	pipe(pd);
	
	pid = fork();

	// Processo filho
	// Vai enviar a execução do primeiro comando ao processo pai
	if(pid == 0){
		
		// Como só vai usar o de escrita fechamos o canal de leitura
		close(pd[0]);
		// Dissemos que o standard output passa a ser o canal de escrita
		dup2(pd[1],1);
		// Podemos então fechar o canal de escrita, dado o redirecionamento feito
		close(pd[1]);

		// O resultado disto vai para o standard output do processo filho
		// Este standard output é o canal de saída/escrita do pipe
		execlp("ls", "ls", "/etc", NULL);
		perror("ls");

		_exit(1);
	}
	// Processo pai
	else{
		
		// O processo pai só vai precisar de ler do canal de entrada o pipe
		close(pd[1]);
		// Dissemos que o input do processo pai será o canal de entrada do pipe
		// Relembrar que o processo filho enviou para este canal precisamente o seu output
		dup2(pd[0],0);
		
		// Comando executado consoante o input recebido do processo filho
		execlp("wc", "wc", "-l", NULL);
		perror("wc");
	}

	return 0;
}