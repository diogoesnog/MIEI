/** Guião 1 **/
// 1.
#include <unistd.h>   
#include <fcntl.h>    
#include <stdio.h>


int main () {
	char ch;
	char buffer[64];
while ((ch = fgets(buffer,64,stdin))!= EOF)
	putchar(ch);
return 0;
}