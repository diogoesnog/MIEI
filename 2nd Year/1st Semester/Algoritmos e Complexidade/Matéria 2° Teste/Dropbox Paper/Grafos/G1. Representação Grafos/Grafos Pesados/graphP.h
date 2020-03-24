#define MAX 100
#define NE 0 // Caso uma aresta não exista, usamos o NE que também indica a inexistência de um peso.

// Matriz de Adjacência
// Aqui usamos int que será usado para o peso em si.
typedef int GraphM[MAX][MAX];

// Lista de Adjacência
typedef struct bloco {
  int destino;
  int peso;
  struct bloco *proximo;
} bloco;

typedef struct bloco *GraphL[MAX];