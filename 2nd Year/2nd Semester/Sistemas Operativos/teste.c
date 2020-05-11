#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(){

    char buf[5];
    char *contents = "abcdefghij";
    int read_bytes = 0;

    int fd = open("ficheiro.txt", O_CREAT, 0777);
    
    write(fd, contents, strlen(contents));
    read_bytes = read(fd, buf, 5);
    write(1, buf, read_bytes);

}