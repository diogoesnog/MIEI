#ifndef StackBuffer_h
#define StackBuffer_h

// Estruturas definidas

// 1. Implementação com Listas Ligadas
typedef struct listaLigada{
	int valor;
	struct listaLigada *proximo;
} Lista, *ListaLigada;

// 2. Implementação com Arrays
typedef struct arrays{
	int *valores;
	int tamanhoArray;
	int capacidadeBuffer;
} ArrayBuffer;

// Métodos a Implementar

// 1. Listas Ligadas
void iniciarLL(ListaLigada*);
int vaziaLL(ListaLigada);
int adicionarLL(ListaLigada*, int);
int proximoLL(ListaLigada, int *);
int removerLL(ListaLigada*, int *);

// 2. Arrays
void iniciarA(ArrayBuffer*, int capacidadeBuffer);
int vaziaA(ArrayBuffer*);
int adicionarA(ArrayBuffer*, int);
int proximoA(ArrayBuffer*, int *);
int removerA(ArrayBuffer*, int *);

#endif 

