#include <unistd.h>
#include <fcntl.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <signal.h>

int main()
{
int fd =  open("fifo", O_WRONLY);

write(fd, ...);

close(fd);
}
