#include <unistd.h>
#include <stdio.h>

// int execlp(const char *file, const char *arg0, ..., NULL);
/*Implemente um programa que execute o comando ls -l. Note que no caso da execuc ̧ a  ̃ o ser bem
sucedida, mais nenhuma outra instruc ̧ a  ̃ o e  ́ executada do programa original.*/

int main(int argc, char *argv[]) {
	
	execlp("ls","ls","-l",NULL);
	
}