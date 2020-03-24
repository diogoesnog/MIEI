#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h> /* random */
#include <time.h> // para rand();

//2.
/*
int main(){

	int pid = fork();
	printf("Pid %d\n",pid);
	if (pid==0){
		printf("Eu sou o FILHO e o meu pid é %d e o pid do meu pai é %d\n",getpid(),getppid() );
	}
	else{
		printf("Eu sou o PAI e o meu pid é %d e o pid do meu filho é %d\n",getpid(),pid);
	}
	return 0;
}
*/

// 3. Nunca fazer por ser sequencial
/*
int main(){
	int i, pid,status;

	for (i=0;i<10;i++){
		if((pid=fork())==0){
			printf("Eu sou o FILHO e o meu pid é %d e o pid do meu pai é %d\n",getpid(),getppid() );
			_exit(i+1);
		}
		else {
			wait(&status);
			if (WIFEXITED(status)) {
			 printf("Eu sou o PAI e o meu pid é %d e o pid do meu filho é %d\nO codigo de terminação do meu filho é %d\n",getpid(),pid,WEXITSTATUS(status));
			}
		}
	}
	return 0;
}
*/

//4.
/*
* No ciclo onde coloco um fork não coloco um wait - programa concorrente
* O pai nunca termina a sua execução antes de os filhos todos terminarem
*/
/*
int main(){
	int pid[10],status,i;

	for(i=0;i<10;i++){
		pid[i] = fork();
		if (pid[i]==0){
			printf("Eu sou o FILHO e o meu pid é %d e o pid do meu pai é %d\n ",getpid(),getppid());
			_exit(i+1);
		}
	}

	for(i=0;i<10;i++){
		waitpid(pid[i],&status,0);
		if(WIFEXITED(status)){
			//printf("Eu sou o pai e o meu pid é %d e o do meu filho é %d\n O codigo é %d\n", getpid(),pid[i],WEXITSTATUS(status));
		}
	}

	//sleep(10);
	return 0;
}
*/
/*Criar quantos processos quantos nº de linhas
**/
//6.
/*
int main(int argc, char*argv[]){
	int l = 5;
	int c = 10;
	int i,j;
	int mat[l][c];
	int pid[l],status;
	
	srand((unsigned)time(NULL)); //random seed

	if(argc<2){
	//	printf("Não foi passado como argumento o numero que se procura\n");
		return 0;
	}
	
	for(i=0;i<l;i++){
		for(j=0;j<c;j++){
			mat[i][j] = rand() % 10;
			printf("%i\t",mat[i][j] );
		}
		printf("\n");
	}

	int find = atoi(argv[1]);
	int r,s;
	
	printf("Procurando o numero %d\n",find );

	for(r=0;r<l;r++){
		pid[r] = fork();
		if (pid[r]==0){
			//printf("Eu sou FILHO com pid = %d\n",getpid());
			for(s=0;s<c;s++){	
				if (mat[r][s]==find) {
				printf("O numero encontra-se na posição mat[%d][%d]\n",r,s );
				}
			}
			_exit(0);

		}
	}

	int k;
	for (k=0;k<l;k++){
		wait(NULL);
	}
	
return 0;
}
*/
int main(int argc, char*argv[]){
	int l = 5;
	int c = 10;
	int i,j;
	int mat[l][c];
	int x,status;
	
	srand((unsigned)time(NULL)); //random seed

	if(argc<2){
	//	printf("Não foi passado como argumento o numero que se procura\n");
		return 0;
	}
	
	for(i=0;i<l;i++){
		for(j=0;j<c;j++){
			mat[i][j] = rand() % 10;
			printf("%i\t",mat[i][j] );
		}
		printf("\n");
	}

	int find = atoi(argv[1]);
	int r,s;
	
	printf("Procurando o numero %d\n",find );

	for(r=0;r<l;r++){
		x = fork();
		if (x==0){
			//função que vai à linha i e que conta o numero de ocorrencias do num
			c = conta(i,num);
			//printf("Eu sou FILHO com pid = %d\n",getpid());
			_exit(c);
			}
			
	}


	int k;
	c=0;
	for (k=0;k<l;k++){
		wait(&status);
		c += WEXITSTATUS(&status)
	}
	
return 0;
}

/*
* Programa sequencial
*/
//7.
/*
int main(int argc, char*argv[]){
	int l = 5;
	int c = 10;
	int i,j;
	int mat[l][c];
	int pid[l+1],status;
	
	srand((unsigned)time(NULL)); //random seed

	if(argc<2){
	//	printf("Não foi passado como argumento o numero que se procura\n");
		return 0;
	}
	
	for(i=0;i<l;i++){
		for(j=0;j<c;j++){
			mat[i][j] = rand() % 10;
			printf("%i\t",mat[i][j] );
		}
		printf("\n");
	}

	int find = atoi(argv[1]);
	int r,s;
	
	
	printf("Procurando o numero %d\n",find );
	
	pid = fork();
	printf("Eu sou o FILHO e o meu pid é = %d  e o pid do meu PAI é = %d\n",getpid(),getppid() );
	
		for(r=0;r<l;r++){
			if  (pid==0){
				pid= fork()
				printf("Eu sou o FILHO e o meu pid é = %d  e o pid do meu PAI é = %d\n",getpid(),getppid() );
			}
		}
	/*
	for(r=0;r<l;r++){
		pid = fork();
		if (pid==0){
			//printf("Eu sou FILHO com pid = %d\n",getpid());
			for(s=0;s<c;s++){	
				if (mat[r][s]==find) {
					printf("O numero encontra-se na posição mat[%d][%d]\n",r,s );
				}
			}
			_exit(0);
		}
		else {
			wait(&status);
		}
	}


	
return 0;
}
*/
