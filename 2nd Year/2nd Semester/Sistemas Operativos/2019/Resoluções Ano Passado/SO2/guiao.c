/** Guião 1 **/
// 1.
#include <unistd.h>   
#include <fcntl.h>    
#include <stdio.h>
#include <stdlib.h>

// Versão simples
/*
int main () {
	char ch;
	char buffer[64];
while (fgets(buffer,64,stdin))
	printf("%s",buffer);
return 0;
}
*/

// Versão complicated
/*
int main(){
	int r;
	char *c;
	while ((r=read(0,&c,1)) == 1)
		write(1,&c,1);
	if (r==0) return 0;
	else return -1;
}*/
//1
/*
int main(void){
	char c;
	while (read(0,&c,1)!=0)
		write(1,&c,1);
	_exit(0);
}
*/ 

// 2.
/*
int main(int argc, char *argv[]){

	int i;
	

	int fd = open(argv[1],O_WRONLY|O_CREAT,0600);

	for(i=0;i<10*1024;i++){
		write(fd,"x",1);
	}
	close(fd);
	return 0;
}
*/

// 3. 
/*
int main(int argc, char *argv[]){
	int N = atoi(argv[1]);
	char * buffer = malloc(N);
	int n;

	while ((n=read(0,buffer,N))==1)
		write(1,buffer,N);
	return 0;
}
*/


// 5

int readLn (int fildes, char * buf, size_t nbyte) {
	int i=0;
	int n=1;
	char c = ' ';

	while ((i<nbyte ) && (n>0) && (c != '\n')){
		n = read(fildes,&c,1); // caracter a carater
		if (n && (c!= '\n')){
			buf[i++]=c;
		}
	}

	// EOF = 0  e verificação de chegar ao limite do buf
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

/*
int main(){
	char buffer[1000];
	readLn(0,buffer,1000);
	printf ("A linha lida é %s \n",buffer);
	return 0;
}

*/

int main(int argc, char *argc ){
	char buff[1024];
	int r;
	int i=1;
	int reader = 0 			// 0 para ler do stdin caso não seja um fich
	// Caso de ser um fich

	if (argc>1)
		reader = open(argv[2])
}
