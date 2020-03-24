#include <unistd.h>
#include <stdio.h>

//3. Implemente um programa que imprima a lista de argumentos recebidos na sua linha de comando.
// int execlp(const char *file, const char *arg0, ..., NULL);
int main(int argc, char *argv[]) {
	
	int i,total = argc;
	
	printf("Lista de argumentos:\t");	
	
	for(i=1;i<total;i++) {
		printf("%s ",argv[i]);
	}
	
	printf("\n");
}