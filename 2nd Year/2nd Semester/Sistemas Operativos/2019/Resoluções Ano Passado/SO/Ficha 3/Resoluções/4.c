#include <unistd.h>
#include <stdio.h>


/* Implemente um programa que execute o programa da quest ̃ao anterior com uma qualquer lista de argu-
mentos. Mantendo o nome do ficheiro que corresponde o programa execut ́avel, experimente alterar o
primeiro elemento da lista de argumentos ( ́ındice zero do argv). */

// int execlp(const char *file, const char *arg0, ..., NULL);
int main(int argc, char *argv[]) {
	
	int i,total = argc;
	char *lista[total+1];
	
	lista[0] = "./3";
	for(i=1;i<total;i++) {
		if(i+1 == total) lista[total+1] = NULL;
		else lista[i] = argv[i];
	}
	//lista[total+1] = NULL;
	
	//printf("Tou aqui");
	execvp("./3",lista);
}



