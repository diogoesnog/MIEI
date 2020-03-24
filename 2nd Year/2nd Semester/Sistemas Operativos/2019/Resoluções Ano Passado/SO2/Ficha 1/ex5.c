#include <unistd.h>   
#include <fcntl.h>    
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Ideia Função que lê linha a linha e guarda linha a linha no buf */

int readln (int fildes,char * buf,int nbytes){
	int i;
	char c;
	int n = 1;

	for (i=0; n>0 && i<nbytes && c!= '\n';i++){
		n = read(fildes,&c,1);
		if (c!= '\n' && n>0){
			buf[i] = c;
		}
	}

	if (n<0) return n;				 	//Erro na read
	if ((n==0) && (i==0)) return -1; 	//Erro na read
	if (i<nbytes) buf[i] = 0;
	else {
		i--;
		buf[i] = 0;
	}
	return i;	//sucesso
}


int main(int argc, char * argv[]){

	if(argc < 2){
		fprintf(stderr, "Em falta o nome/caminho do ficheiro" );
		exit(0);
	}

	char  * buff = malloc(sizeof(100));
	int filde;
	filde = open(argv[1],O_RDONLY);

	while (readln(filde,buff,100)) write(1,buff,100);
	printf("\n");
	return 0; 
}



