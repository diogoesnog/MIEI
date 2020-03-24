#include <unistd.h>
#include <fcntl.h>

/*
 * 0 : stdin
 * 1 : stdout
 * 2 : stderr
 */

int main(){
	char c;

	while (read(0,&c,1))
		write(1,&c,1);

	return 0;
}