#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int readln(int fildes, char* buf, int nbyte) {
	int i = 0;
	int n = 1;
	char c = ' ';
	
	while ((i < nbyte) && (n > 0) && (c != '\n'))
	{
		n = read(fildes,&c,1);
		if (n && (c != '\n')) 	{
			buf[i] = c;
			i++;
		}
	}
	
	// Adição de EOF == 0 com verificação no caso de chegar ao limite de leitura (N);
	if (i < nbyte)	buf[i] = 0;
	else { 	i--; 	buf[i] = 0;	}
	if (n < 0)	return n;
	if ((n == 0) && (i == 0)) return (-1);
	return i;
}

int main (int argc, char** argv) {
	int N = 1024; 					// Tamanho do buffer de palavras.
	char buffer[N];
	int reader = 0, n = 0, i = 1;

	//se tiver argumento
	if (argc > 1) { reader = open(argv[i], O_RDONLY); }
	
	/* caso não consiga abrir o ficheiro */
	if(reader < 0) 	{ perror(argv[i]); 	}
	else {
		do {
			n = readln(reader, buffer, N);
			if(n > 0) 	{ 
				if((write(1,buffer,n)) && (write(1,"\n",1))) i++;
				else perror("writing error");
				}
		} while(n >= 0);
		close(reader);
			}
	
	return 1;
	
	}
