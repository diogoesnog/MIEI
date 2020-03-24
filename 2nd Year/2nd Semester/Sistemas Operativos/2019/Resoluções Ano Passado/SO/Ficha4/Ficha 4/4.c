#include <unistd.h> 
#include <stdio.h>
#include <fcntl.h>
/* 
int dup(int fd);
int dup2(int fd1, int fd2); 
dup2(stdin,0); //saida,entrada*/

/*Escreva um programa redir que permita executar um comando, opcionalmente redireccionando a en-
trada e/ou a sa ́ıda. O programa poder ́a ser invocado, com:
redir [-i fich_entrada] [-o fich_saida] comando arg1 arg2 ...*/

int main(int argc, char const *argv[]){

	int total = argc,i,in=0,out=0,n,m,fd1,fd2;
	char *cmd[total+1];
	printf("Argc = %i\n",argc);
	if(argc < 2) { printf("\nusar ./%s [-i fich_entrada] [-o fich_saida] comando arg1 arg2",argv[0]); } //porque nao está a imprimir???
	//tem -i
	if(strcmp(argv[1],"-i")) { 
		fd1 = open(argv[2],O_RDONLY);
		dup2(fd1,0); 
		in = 2;
	}
	// tem -o
	n = strcmp(argv[1],"-o"); //caso não exista -i
	m = strcmp(argv[3],"-o");
	if(n || m) { 
		if(n) { //caso não exista -i
		fd2 = open(argv[2],O_RDWR|O_TRUNC|O_CREAT);
		dup2(fd2,1); 
		}
		if(m) { //quando existe -i
		fd2 = open(argv[4],O_RDWR|O_TRUNC|O_CREAT);
		dup2(fd2,1); 
		}
		out = 2;
	}
	// ./a.out ps
	//	0		1
	//criar array
	for(i=0+in+out;i<total;i++) {
		if(i+1 == total) cmd[total+1] = NULL;
		else cmd[i] = argv[i+1];

	}
	//comando a executar com os argumentos
	if(!fork()) execvp(cmd[0],cmd);

}