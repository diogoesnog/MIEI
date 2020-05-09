#include <stdio.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdlib.h> 
#include <time.h>

int main(int argc, char *argv[]) {
	
    int i,j;

    int elemento;
	int linhas=5, colunas=10;
	int pid[linhas];
	int matriz[linhas][colunas];
	
	srand((unsigned)time(NULL)); //random seed
	
    // Caso o número de argumento seja inferior a 2, é porque faltam argumentos.
	if (argc<2) { 
        printf("Número em falta. Introduza o elemento a procurar.\n"); 
        return (-1);
    }

    // Converter String num inteiro.
	elemento = atoi(argv[1]);
	
    // Criar uma matriz aleatoriamente.
	for (i = 0; i < linhas; i++) {

		for (j = 0; j < colunas; j++) {
			matriz[i][j] = rand()%10; // Gera números até 10.
			printf("%i\t",matriz[i][j]);
		}
	    printf("\n");
	}
	
	printf("\nPesquisando os resultados...\n");
		
    // Criação de processos paralelos para procurarem todos o elemento.
    // Assim, consegue-se uma procura mais rápida e eficiente.

    /* Como temos muito menos linhas que colunas (segundo o enunciado), faz mais
     * sentido criar um processo paralelo para cada linha. */

	for (i = 0; i < linhas; i++) {

		pid[i] = fork();

        // Os processos filhos é que vão procurar.
		if (pid[i] == 0) {
			for(j = 0; j < colunas; j++) {
				if (matriz[i][j] == elemento) { 
                    printf("Elemento %i presenta na matriz[%i][%i]\n", elemento, i, j); 
                }
			}
		_exit(0);
 		}		
	}

    // O processo pai tem de esperar que cada processo filho termine o seu trabalho.
	for(i = 0; i < linhas; i++) wait(NULL);
	
	return 1;

}