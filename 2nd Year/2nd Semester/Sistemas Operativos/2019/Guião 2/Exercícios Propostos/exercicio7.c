#include <stdio.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdlib.h> /* random */
#include <time.h> // para rand();

int main(int argc, char *argv[]) {
	
	int num,i,j,z,status;
	int linhas=5, colunas=10;
	int pid[linhas];
	int matriz[linhas][colunas];
	int resultados[linhas];
	int val = 0;
	
	srand((unsigned)time(NULL)); //random seed
	
	if (argc < 2) { printf("Number to search is missing use:\n ./%s number\n",argv[0]); exit(1);}
	num = atoi(argv[1]);
	
	//create random matrix
	for (i = 0; i<linhas; i++) {
		printf("\n");
		for (j = 0; j<colunas; j++) {
			matriz[i][j] = rand()%10; //matrix with randoms from 1-50
			printf("%i\t",matriz[i][j] );
		}
	}
	
	//printf("\n\nSearch Results:\n");
		
	//create paralell process to search matrix
	printf("\n");
	for (i=0;i<linhas;i++) {
		pid[i] = fork();
		if (pid[i] == 0) {
			for(z=0;z<colunas;z++) {
				//if (matriz[i][z] == num) { printf("Found %i at matriz[%i][%i]\n",num,i,z); }
				if (matriz[i][z] == num) { _exit(1);}
				}
			_exit(0);
 		}
	}
	
	for(i=0;i<linhas;i++) {
		waitpid(pid[i],&status,0);
		if((WIFEXITED(status))==1) { resultados[i] = WEXITSTATUS(status) ; }
		else resultados[i] = 0;
	}
	
	printf("\nFoi encontrado o numero nas linhas:\t");
	for(i=0;i<linhas;i++) {
		if(resultados[i] == 1) printf("%i \t",i);
	}
}