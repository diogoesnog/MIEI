#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>  //atoi

int readln (int fildes,char * buf,int nbytes){
	int i;
	char c;
	int n = 1;
	int e = 0;
	for (i=0; n>0 && i<nbytes && c!= '\n';i++){
		n = read(fildes,&c,1);
		if (c!= '\n' && n>0){
			buf[e] = c;
			e++;
		}
		
	}
	if (n<0) return n;				 	//Erro na read
	if ((n==0) && (e==0)) return -1; 	//Erro na read
	if (i<nbytes) buf[e] = '\0';
	else {
		e--;
		buf[e] = '\0';
	}
	return e;	//sucesso
}


int main(int argc, char * argv[]){

	if(argc < 2){
		fprintf(stderr, "Em falta o nome/caminho do ficheiro" );
		exit(0);
	}

	char buff[512];
	int filde;
	filde = open(argv[1],O_RDONLY);
	int size = 0;
	size = readln(filde,buff,512);
	write(1,buff,size);
	printf("\n");
	return 0; 
}