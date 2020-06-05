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
    char *string1 = "teste1\n";
    char *string2 = "teste2\n";

    int fd = open("out.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);
    dup2(fd, 1);
    close(fd);

    if (fork() == 0)
    {
        write(1, string1, strlen(string1));
        _exit(0);
    }
    else
    {
        wait(NULL);
        write(1, string2, strlen(string2));
    }
}