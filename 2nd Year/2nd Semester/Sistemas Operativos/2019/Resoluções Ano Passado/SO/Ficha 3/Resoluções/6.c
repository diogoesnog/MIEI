#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <wordexp.h>

/* Implemente uma vers ̃ao simplificada da func ̧ a  ̃ o system(). Ao contr ́ario da func ̧ a  ̃ o original, n ̃ao tente
suportar qualquer tipo de redireccionamento, ou composic ̧ a  ̃ o/encadeamento de programas execut ́aveis.
O u  ́ nico argumento dever ́a ser uma string que especifica um programa execut ́avel e uma eventual lista de
argumentos. Procure que o comportamento e valor de retorno da sua func ̧ a  ̃ o sejam compat ́ıveis com a
original.*/

int main(int argc, char *argv[]) {

	int pid,res,status,i;
	char *str[argc+1];
	wordexp_t p;
    char **w;
	
	int mysystem(char *cmd[]) {
		pid = fork();		
		if(pid==0) {  execvp(cmd[0],cmd); }
		else {
		waitpid(pid,&status,0);
		if(WIFEXITED(status)) res = WEXITSTATUS(status);
		return res;
		}
	}

	//separa string por espaços e guarda em array, ver exemplo wordexp
	if (argc > 1 ) {
		wordexp(argv[1], &p, 0);
		w = p.we_wordv;
		mysystem(w);
		wordfree(&p);
	}	
				
	return 0;

}