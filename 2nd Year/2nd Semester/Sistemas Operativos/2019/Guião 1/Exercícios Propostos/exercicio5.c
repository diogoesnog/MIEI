#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Fazer uma implementação da função readln, cujo protótipo é compatível com a chamada ao sistema read.
// Basicamente, ler caracter a caracter de uma linha no input e devolver o número de bytes.
int lerLinha(int fildes, void *buf, size_t nbyte){

    int res = 0;
    int i = 0;
    
    while(i<nbyte && (read(fildes, &buf[i], 1))>0){

        if(((char*) buf)[i]=='\n') return i;
        i++;
    }

    return i;

}
int main(void){
	char buffer[10];

	printf("readlinha: %d\n", lerLinha(0, buffer, 10) );
	return 0;
}