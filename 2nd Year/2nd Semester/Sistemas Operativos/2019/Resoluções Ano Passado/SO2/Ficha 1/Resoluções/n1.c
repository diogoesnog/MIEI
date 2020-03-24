#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]) {

	int n, i=0;
	char buf[1];
	int reader=0;
	char str[10];
	
	if(argc>1){
			reader = open(argv[2],O_RDONLY);
	 }
	
	while(n=read(reader,buf,sizeof(buf)) > 0)  {
		if (buf[0] == '\n') { 
			i++; 
			snprintf(str,sizeof(str)-1, "%d ",i); 
			write(1,str,sizeof(str)); 
			}
		write(1,buf,sizeof(buf));
		

	}
	close(reader);
	
	return 1;
	
	
}