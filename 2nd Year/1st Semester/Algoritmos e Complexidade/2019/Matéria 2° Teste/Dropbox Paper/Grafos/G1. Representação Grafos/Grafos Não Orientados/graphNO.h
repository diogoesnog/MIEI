#define MAX 100

// Matriz de Adjacência
// Tipo char. Poderia ser int.
typedef char GraphM[MAX][MAX];

// Lista de Adjacência
typedef struct bloco {
  int destino;
  struct bloco *proximo;
} bloco;

typedef struct bloco *GraphL[MAX];