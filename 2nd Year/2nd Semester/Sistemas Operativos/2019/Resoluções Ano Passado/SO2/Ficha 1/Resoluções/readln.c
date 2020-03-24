#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {

	char buffer[1024];
	int n, i=0;
	char buf[1];
	// 0 stdin
	// 1 stdout
	// 2 stderr
	while(n=read(0,buf,sizeof(buf)) > 0)  {
		//if (buf[0] == '\n') { buffer[i] = '\0' ; printf("%s\n",buffer) ; i=0 ; }
		//else buffer[i] = buf[0];
		//i++;
		//tem um char a mais no inicio ao repetir, nao sei se onde vem.
		write(1,buf,sizeof(buf));
	}
	
	return 1;
	
	
}