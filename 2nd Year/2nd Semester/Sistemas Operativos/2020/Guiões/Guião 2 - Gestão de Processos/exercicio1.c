#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main() {

    // Cria-se um novo processo.
    int pid = fork();

    // Quando o resultado do fork é igual a 0 é o FILHO.
    // Quando o resultado do fork é diferente de 0 é o PAI.
    if(pid == 0) printf("Filho -> Meu PID: %d / PID meu pai: %d\n",getpid(), getppid());
    else{
        printf("Pai -> Meu PID: %d / PID meu pai: %d\n" , getpid(), getppid());
    }

    return 0;
}

/* Discussão dos Resultados

Ao criarmos um fork estamos a criar um novo processo. Repare-se que em termos de terminal
veremos dois processos:

- O meu processo com um determinado PID.
- O processo do meu pai com outro PID.

Note-se que o processo pai do meu pai será a própria bash. */