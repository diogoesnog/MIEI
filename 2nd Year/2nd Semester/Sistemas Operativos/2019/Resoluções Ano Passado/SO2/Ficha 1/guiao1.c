#include <unistd.h>   
#include <fcntl.h>    
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int readln(int fildes,char *buf,int nbyte);


// 1.
/*
int main(){
	char c;

	while (read(0,&c,1))
		write(1,&c,1);
	return 0;
}
*/
/*
// 2
int main(int argc, char *argv[]){
	int file;
	int i;

	if (argc<2){
		printf("Nome do ficheiro em falta\n");
		return 0;
	}

	file = open(argv[1],O_CREAT|O_WRONLY,0666);

	for (i=0;i<10*1024;i++)
		write(file,"a",1);
	return 0;

}
*/
/*
//3.
int main(int argc, char *argv[]){
	
	if (argc <2){
	printf("Não foi referido o nº de bytes\n");
	return 0;
	}
	
	int nbytes = atoi(argv[1]);
	char *buff = malloc(nbytes);

	while (read(0,buff,nbytes))
		write(1,buff,nbytes);
	return 0;
}

*/
// 4  ----

// 5.
int main(int argc, char *argv[]){

	if (argc<3){
		printf("Não especificou o filde/nbytes \n Primeiro especifique o filde e depois os nbytes");
		return 0;
	}

	int filde = atoi(argv[1]);
	int nbytes = atoi(argv[2]);
	char *buff = malloc(nbytes);
	readln(filde,buff,nbytes);
	write(1,buff,nbytes);
	
	return 0;
}

int readln(int fildes,char *buf,int nbyte){
	int i;
	char c;
	int n = 1;

	for (i=0;n>0 && i<nbyte && c!= '\n';i++){
		n=read(fildes,&c,1);
		if (c!='\n'){
			buf[i++] = c;
		}
	}

	if (i<nbyte) buf[i]=0;
	else{
		i--;
		buf[i] = 0;
	}
	// erro no read
	if (n<0) return n;
	// caso não tenha lido nada
	if ((n==0) && (i==0)) return (-1);
	// caso de sucesso
	return i;	
}