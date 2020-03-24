#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h> 
#include <sys/stat.h>
#include <ctype.h>
#include <sys/stat.h>
#include <locale.h>
#include <time.h>

#include "sv.h"
#include "ma.h"

int main(int argc, char const *argv[])
{

    int ficheiroStock = open("stock.txt", O_RDONLY, 0666);
    
    struct ArtigoStock artigoLido;    
    
    while(read(ficheiroStock, &artigoLido, sizeof(struct ArtigoStock))){
        printf("%d - %d\n", artigoLido.codigoArtigo, artigoLido.quantArtigo);
    }
    return 0;
}
