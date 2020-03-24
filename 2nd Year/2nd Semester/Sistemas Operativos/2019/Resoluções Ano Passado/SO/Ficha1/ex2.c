#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

/*
 * O_CREAT : creat file if not exist
 * O_WRONLY : open for writing only
 * O_RDONLY : open for reading only
 * O_APPEND : set append mod
 */

/*
 * 421 421 421
 * rwx rwx rwx
 *  u   g   o
 */

/*
 * 1 Mb = 1024 Kb
 * 1 Kb = 1024 b
 * 1 b = 8 bits
 */

int main(int argc, char *argv[]){

	if(argc<2){
		fprintf(stderr, "Nome do ficheiro inexistente\n");
		return -1;
	}

	int fd = open(argv[1],O_CREAT | O_WRONLY,0666);
	int i;
	
	int tamanho = 1*1024*1024*8;
	for(i=0;i<tamanho;i++)
		write(fd,"a",1);
	return 0;

}