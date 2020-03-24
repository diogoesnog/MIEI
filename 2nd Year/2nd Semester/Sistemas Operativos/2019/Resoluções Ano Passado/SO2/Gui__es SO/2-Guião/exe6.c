#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define L 10
#define C 100000

int main(){
	int i, j, n;
	int matriz[L][C];

	for(i=0; i!=L; i++)
		for(j=0; j!=C; j++)
			matriz[i][j] = 0;

	matriz[1][568] = 12;
	matriz[9][899] = 8;
	matriz[4][84767] = 8;
	matriz[1][10] = 8;
	n = 8;

	for(i=0; i!= L; i++){
		if(fork()==0){			
		
			for(j=0; j!=C; j++){
		
				if(matriz[i][j] == n){
					printf("encontrou o valor %d em matriz[%d][%d]\n",
						n, i, j);
				}
			}
			_exit(1);
		}
	}

	for(i=0; i!=L; i++) wait(NULL);

	return 0;
}