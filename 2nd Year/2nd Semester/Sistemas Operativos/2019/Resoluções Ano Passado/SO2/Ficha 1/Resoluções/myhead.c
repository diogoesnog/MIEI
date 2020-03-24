#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int readln_v1(int fildes, char* buf, int nbyte) {
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
	int N = 1024; // Tamanho do buffer de palavras.
	char buffer[N], nums[10];
	int reader = 0, n = 0, i = 1, linhas=0;
	//se tiver argumento
	if (argc > 2) { 
		for(i=2; i<argc;i++) { 
			reader = open(argv[i], O_RDONLY); 
			char name[sizeof(argv[i])+5];
	/* caso não consiga abrir o ficheiro */
	if(reader < 0) 	{ perror(argv[i]); 	}
	else {
		linhas=0;
		int lin = atoi(argv[1]);
		//criar >>> nomeficheiro <<<
		strcpy(name, ">>> "); strcat(name,argv[i]); strcat(name,"\n");
		write(1,name,sizeof(name));
		do {
			n = readln_v1(reader, buffer, N);
			if(n > 0) 	{
				//sprintf(nums, "\t%d\t", i);  // (write(1,"\t",1)) 
				if(write(1,buffer,n) && write(1,"\n",1)) linhas++;
				else perror("writing error");
				}
		} while(n >= 0 && linhas < lin);
		close(reader);
		
			}
	}
	}
	//else para o stdin read(0,O_RDONLY);
	//write(1,"merda",5);
	return 1;
	
	}
		
