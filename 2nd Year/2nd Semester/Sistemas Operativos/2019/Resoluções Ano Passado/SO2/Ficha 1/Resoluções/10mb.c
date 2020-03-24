#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
	
	FILE *fp;
	int X, f, i =1,f2;
	int dezmb = 1024 * 1024;
	char buffer[10] = "aaaaaaaaaa";
	//buffer[0] = 'a';
	
	//nao foi especificado nenhum ficheiro
	 if(argc<2){
    		printf("usar ./bin <nome> \n");
    		return 0;
	 }
	
	//fp = fopen(argv[1],"w");
	f = open(argv[1], O_WRONLY|O_APPEND|O_CREAT);	
	//f2 = open("merda",O_WRONLY|O_APPEND|O_CREAT);
	//write(f2,buffer,1);
	//printf("\n conteudo do buffer: %s",buffer);
	while(i<dezmb) {
		printf("tou aqu %i\n",i);
		write(f,buffer,10);
		//printf("nao acabei o write\n");
		i++;
	}
	
	/*
	//10 * 1MB = 10 * 1024B (-1 do char \0) 
	X = 10 * 1024 - 1;
    fseek(fp, X , SEEK_SET);
    fputc('\0', fp);
    fclose(fp);*/
	close(f);
	//close(f2);
	
	}