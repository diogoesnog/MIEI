#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h> /* random */
#include <time.h> // para rand();

// 1.
/**
int main(void){

	printf("Eu sou o pai %d \n e eu o filho %d \n",getppid(),getpid());
	return 0;
}
**/

// 2.
/*

int main(){
	int pid;
	pid = fork();			//este pid corresponde ao identificador do processo filho
	if(pid<0){
	 perror("Fork falhou");
	 return 0;
	}
	// Processo filho
	if (pid==0){
		printf("Eu sou o FILHO \n O pid do processo PAI é %d e o pid do processo FILHO é %d\n",getppid(),getpid());
	}
	else{
	//	wait(NULL);	// espero até que um filho qualquer termine
		printf("Eu sou o pai \n O pid do processo PAI é %d e o pid do processo FILHO é %d\n",getpid(),pid);
	}
	return 0;
}
*/
/*
//3

int main(){
	int i, status;
	pid_t pid;

	for (i=0;i<10;i++){
		if((pid=fork())==0){
			printf("Eu sou o FILHO e o meu pid é %d, e o meu PAI tem pid = %d\n",getpid(),getppid());
			_exit(i+1);		// o primeiro filho criado termina com valor 1;
		}
		else {
			wait(&status);
			if(WIFEXITED(status))
				printf("Sou o Pai: O filho %d com pid = %d retornou: %d\n",i, pid, WEXITSTATUS(status));
		}
	}
	
	return 0;
}
*/

// 4 - filhos deverão executar potencialmente em concorrencia

/*
int main(){
	int pid[10], i, status,wpid;

	for(i=0; i!=10; i++){
		if((pid[i]=fork())==0){
			printf("Sou o filho Nº%d pid = %d\n",i+1,getpid());
			_exit(i+1);
		}
	}

	for(i=0; i<10 ; i++){
		
		waitpid(pid[i], &status, 0);
		if(WIFEXITED(status))
			printf("O filho %d retornou %d\n",pid[i], WEXITSTATUS(status));
	}
	return 0;
} 
*/

// 5.
/*
int main(){
	int status,i;
	pid_t pid;

	pid = fork();

	for (i=0;i<10;i++){
		

		//caso de erro
		if(pid<0){
			perror("Falha a executar o fork()");
			return 0;
		}

		// O FILHO executa
		if (pid==0){
			printf("Eu sou o FILHO e tenho pid = %d e o meu pai tem pid = %d\n",getpid(),getppid());
			pid = fork();

		}

		// O pai executa
		else{
			wait(NULL);			//espera que qualquer filho termine.
			// printf("Eu sou o PAI e tenho pid = %d e o meu filho tem pid = %d\n",getpid(),pid );

		}
		
	}
	return 0;
}
*/

//6.
/*
int main(int argc, char * argv[]){
	int number;
	int linhas =5;
	int colunas =10;
	int matriz[linhas][colunas];
	int i,c,z;
	int pid[linhas];				//compensa mais procurar por linha visto que linhas<colunas
	int flag = 0;
	
	srand((unsigned)time(NULL)); //random seed

	// nº em falta
	if (argc<2){
		printf("Numero em falta \n");
		exit(1);
	}

	// numero que se pretende procurar na matriz
    number = atoi(argv[1]);

	// preencher a matriz com numeros aleatorios:
	for (i=0;i<linhas;i++){
		printf("\n");
		for (c=0;c<colunas;c++){
			matriz[i][c] = rand()%10+1;				//numeros aleatorios entre 1-50;
			printf("%i\t",matriz[i][c] );
		}
	}


	printf("\n\nProcurando o numero %d na matriz\n",number );

	printf("\n");
	// Iniciando a busca em paralelo
	for (i=0;i<linhas;i++) {
		pid[i] = fork();
	//	printf("Eu sou o FILHO com pid = %d e o meu pai tem pid = %d\n", getpid(),getppid());
		if (pid[i] == 0) {
			for(z=0;z<colunas;z++) {
				printf("Eu sou o FILHO com pid = %d e o meu pai tem pid = %d matriz[%i][%i]\n", getpid(),getppid(),i,z);
				if (matriz[i][z] == number) { printf("Found %i at matriz[%i][%i]\n",number,i,z);}
			}
		 _exit(0);
 		}		
	}

	for (i=0;i<linhas;i++) wait(NULL);

	if (flag==0) printf("Numero não se encontra na matriz\n");
	return 1;	
}
*/