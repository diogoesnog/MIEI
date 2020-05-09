#include <unistd.h>
#include <stdio.h>

/*
 * retornam -1 se houver erro
 * as funções que tem p no final (ex: ecxlp) basta indicar o nome do ficheiro executavel
 + as restantes têm que incluir o path compelto
 */

int main() {

	execlp("ls","ls","-l",NULL);
	
	return 0;
}
