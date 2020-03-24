#define EMPTY 0
#define SIZE 10000

typedef struct vendas {
    int codigo;
    int quantidadeTotal;
    double montanteTotal;
    struct vendas *proximaVenda;
} RegistoVenda, *Vendas[SIZE];