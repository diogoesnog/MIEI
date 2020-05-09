#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>

int main() {
	int pd1[2], pd2[2], pd3[2], n, i;

	// Criação do primeiro Pipe Anónimo.
	pipe(pd1);

	int pid = fork();

	if(pid == 0){

		close(pd1[0]);
		dup2(pd1[1],1);
		close(pd1[1]);
		pipe(pd2);

		int pid = fork();

		if(pid == 0){

			close(pd2[0]);
			dup2(pd2[1],1);
			close(pd2[1]);
			pipe(pd3);

			int pid = fork();

			if(pid == 0){

				close(pd3[0]);
				dup2(pd3[1],1);
				close(pd3[1]);
				execlp("grep", "grep", "-v", "^#", "/etc/passwd", NULL);
				perror("grep");
				_exit(1);
			}
			else {
				dup2(pd3[0],0);
				execlp("cut", "-f7","-d:", NULL);
				perror("cut");
				_exit(1);
			}
		}
		else {
			dup2(pd2[0],0);
			execlp("uniq", "uniq", NULL);
			perror("uniq");
			_exit(1);
		}
	}
	else {
		close(pd1[1]);
		dup2(pd1[0],0);
		execlp("wc", "wc", "-l", NULL);
		perror("wc");
	}
	return 0;
}