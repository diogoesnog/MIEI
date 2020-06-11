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
    int bytes_read;

    int fd = open("log.txt", O_CREAT | O_WRONLY, 0666);
    while ((bytes_read = read(0, buffer, MAX_BUFFER)) > 0)
    {
        pipe(p);
        switch (fork())
        {
        case -1:
            perror("fork");
            return -1;
        case 0:
            dup2(p[1], 1);
            close(p[1]);

            execlp("date", "date", "+%Y-%m-%d_%H:%M", NULL);
            _exit(-1);
        default:
            close(p[1]);
            while (read(p[0], &c, 1))
                write(fd, &c, 1);
            close(p[0]);
            wait(&status);
            lseek(fd, -1, SEEK_END);
            write(fd, &space, 1);
            write(fd, buffer, bytes_read);
        }
    }
    close(fd);
}
