#include <unistd.h> 
#include <stdio.h>
#include <fcntl.h>
/* 
int dup(int fd);
int dup2(int fd1, int fd2); */

/*
Escreva um programa que redireccione o descritor associado ao seu standard input para o ficheiro
/etc/passwd, e o standard output e error respectivamente para saida.txt e erros.txt. Te-
nha em conta que estes ficheiros dever ̃ao ser abertos – e eventualmente criados – com modos de acessos
compat ́ıveis com o redireccionamento pretendido. Por exemplo, o ficheiro saida.txt ter ́a que ser
aberto para escrita, criando-o se necess ́ario, truncado e com permiss ̃oes apropriadas. Experimente ler
uma linha a partir do seu standard input e repeti-la nos descritores de output e error usando directamente
read() e write(). Experimente ainda realizar as mesmas operac ̧ o  ̃ es atrav ́es de func ̧ o  ̃ es da biblioteca
de C – p. ex., fgets(), printf() ou fprintf(). Em todas as situac ̧ o  ̃ es, repare no conte ́udo
dos ficheiros criados. Note que depois de cada redireccionamento, os descritores dos ficheiros abertos
deixam de ser necess ́arios, e como tal e  ́ boa pr ́atica fech ́a-los de imediato. */

int main(int argc, char const *argv[])
{
	/* code */
	int stdin,stdout,stderr,n;
	char buffer[1024];

	stdin = open("/etc/passwd", O_RDONLY);	
	stdout = open("saida.txt", O_RDWR|O_TRUNC|O_CREAT);	
	stderr = open("erros.txt",O_RDWR|O_CREAT|O_TRUNC);
	dup2(stdin,0);//saida, entrada
	dup2(stdout,1);
	dup2(stderr,2);

	while((n=read(0,buffer,1024)) > 0 ) {
			 write(1, buffer, n);
	  	}
	if (n < 0) write(2,buffer,n);
		 close(stdin); 
		 close(stdout);
		 close(stderr);

}
