#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
	
	FILE *fp;
	int i,n;
	char ch;
	int f;
	char buffer[1024];
	
	//nao foi especificado nenhum ficheiro
	 if(argc<2){
    		printf("usar mycat <ficheiro> \n");
    		return 0;
	 }
	
	
	  for(i=1; i<argc;i++){
	   	//fp = fopen(argv[i],"r");
		f = open(argv[i], O_RDONLY);
		//Nao existe ficheiro
		//if(f == NULL) {
		if(f == -1) {
      	 printf("%s: Nao existe esse ficheiro\n", argv[i]);
       		return 0;
    		}
	
		/*
		while((ch=fgetc(fp)) != EOF){
         putchar(ch);
    		}
		*/
		 while((n=read(f,buffer,1024)) > 0) {
			//printf("%s",buffer);
			 write(1, buffer, n);
	  	}
    	//fclose(f);
		 close(f); 
		 
	  }
		
	
	return 1;
}