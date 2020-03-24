#include <unistd.h>   
#include <fcntl.h> 
/*

    O_RDONLY - abrir apenas para leitura;
    O_WRONLY - abrir apenas para escrita;
    O_APPEND - adicionar registros no final do arquivo;
    O_CREAT - criar arquivo se ele ainda não existir;
    O_TRUNC - zerar arquivo se ele já existir. 

*/

int main (int argc, char *argv[]){

	int file;			
	if (argc<2){
		fprintf(stderr, "Em falta nome do ficheiro");
		exit(0);
	}

	file = open(argv[1],O_RDONLY);

	// Com vem a leitura ser linha a linha -> para ja caracter a carater.

	while (read(file,))

}