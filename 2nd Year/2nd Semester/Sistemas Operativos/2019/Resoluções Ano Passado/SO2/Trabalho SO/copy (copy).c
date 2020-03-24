#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct notebook{
	char ** comandos;
	int  size;
}Book;


void inicializaNote(Book * nb){
	nb->size = 0;
	nb->comandos = malloc(sizeof(char *)*1);
}

void printNotebook(Book * nb){
	int i;
	for (i=0;i<(nb->size);i++){
		printf("%s\n",nb->comandos[i]);
	}
}

void insereNote (Book * nb, char * txt){
	nb->comandos = realloc(nb->comandos,(sizeof(char*)*nb->size+1));
	int i;
	for(i=0;i<nb->size;i++);
	nb->comandos[i] = malloc(sizeof(char)*strlen(txt));
	strcpy(nb->comandos[i], txt);
	nb->size += 1;
}

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


int insereComando(Book * nb,char * buf, int nbytes){

	int flag = 0;		// Não é comando;
	int i;

	for(i=0;i<nbytes && flag!=1;i++){
		if (buf[i]=='$'&& buf[i+1]=='|' ){
			insereNote(nb,&buf[i+2]);
			flag = 2;
		}
		else if (buf[i]=='$'){
			insereNote(nb,&buf[i+1]);
			flag = 1;
		}
		
	}
	return flag;
}


int processador (Book *nb, char* argv) {
	int N = 1024; 					// Tamanho do buffer de palavras.
	char buffer[N];
	int reader = 0, n = 0, i = 1;

	//se tiver argumento
	reader = open(argv, O_RDONLY);
	
	/* caso não consiga abrir o ficheiro */
	if(reader < 0) 	{ perror(argv); 	}
	else {
		do {
			n = readln(reader, buffer, N);
			if(n > 0) 	{ 
				int flag = insereComando(nb,buffer,n);
			//	printf("Flag = %d\n",flag);
			//	if((write(1,buffer,n)) && (write(1,"\n",1))) i++;
			//	else perror("writing error");
				}
		} while(n >= 0);
		
	}
	close(reader);
	return 1;	
}

int main(int argc, char ** argv){
	Book * nb = (Book *)malloc(sizeof(Book));
	inicializaNote(nb);
	int flag = processador(nb,argv[1]);
	printNotebook(nb);
	execlp("ls","ls",NULL);
	return 0;
}
