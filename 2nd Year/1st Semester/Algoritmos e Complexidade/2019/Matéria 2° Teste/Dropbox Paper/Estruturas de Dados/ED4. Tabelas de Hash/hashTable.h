#define CAPACIDADE 20

// Estes valores estarão definidos nas chaves em si.
// Caso esteja ocupado, é o valor do nó.
#define LIVRE 0
#define APAGADO 1

// Estrutura para a Estratégia de Resolução de Colisões Open Addressing
typedef struct hashOpen {
    int chave;
    int valor;
} hashOpen, HashTableOpen[CAPACIDADE];

// Estrutura para a Estratégia de Resolução de Colisões Close Addressing
typedef struct hashClose {
    int chave;
    int valor;
    struct hashClose *proximo;
} hashClose, *HashTableClose[CAPACIDADE];