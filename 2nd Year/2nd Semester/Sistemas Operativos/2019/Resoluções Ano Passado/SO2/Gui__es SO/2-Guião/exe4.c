#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>



int main(){
	int pid[10], i, status;

	for(i=0; i!=10; i++){
		if((pid[i]=fork())==0){
			printf("Sou o filho Nº%d pid = %d\n",i+1,getpid());
			_exit(i+1);
		}
	}
	return 0;
} 


