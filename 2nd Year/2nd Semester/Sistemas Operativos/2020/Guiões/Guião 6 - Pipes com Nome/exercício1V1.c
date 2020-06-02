#include <sys/types.h> 
#include <sys/stat.h>

// Programa que cria um pipe com nome "fifo"
int main() {

    mkfifo("fifo", 0777);
    perror("fifo");

    return 0;
}