#define MAX 100
#define NE 0 // Caso uma aresta não exista, usamos o NE que também indica a inexistência de um peso.

// Grafos Pesados definidos de uma outra forma.
typedef struct bloco {
  int destino;
  int peso;
  struct bloco *proximo;
} *GrafoL[MAX];
