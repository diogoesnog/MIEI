#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h> /* random */
#include <time.h> // para rand();

int main(int argc,char*argv[]){

	int l = 5;
	int c = 15;
	int i,j;
	int matrix[l][c];

	srand((unsigned)time(NULL));

	if (argc<2){
		perror("Numero em falta");
		return (-1);
	}
	int n =atoi(argv[1]);
	for(i=0;i<l;i++){
		for(j=0;j<c;j++){
			matrix[i][j] = rand()%10;		//numeros ate 10
			printf("%d\t",matrix[i][j] );
		}
		printf("\n");
	}

	int pid[l];

	for (i=0;i<l;i++){
		pid[i] = fork();
		if (pid[i]==0){
			for(j=0;j<c;j++){
				if (n == matrix[i][j]){
					printf("Numero %d na posição matrix[%d][%d]\n",n,i,j);
				}
			}
			_exit(0);
		}
	}
	
	for(i=0;i<l;i++) wait(NULL);
	return 0;	

}