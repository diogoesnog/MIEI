#ifndef queueBuffer_h
#define queueBuffer_h

// Estruturas definidas

// 1. Implementação com Listas Ligadas
typedef struct listaLigada{
	int valor;
	struct listaLigada *proximo;
} ListaLigada;

typedef struct queue{
	ListaLigada *lista;
	int tamanhoQueue;
} QueueListaLigada;

// 2. Implementação com Arrays
typedef struct arrays{
	int *valores;
	int cabeca;
	int cauda;
	int tamanhoArray;
	int capacidadeBuffer;
} QueueArray;

// Métodos a Implementar

// 1. Listas Ligadas
void iniciarLL(QueueListaLigada*);
int vaziaLL(QueueListaLigada*);
void adicionarLL(QueueListaLigada*, int);
int proximoLL(QueueListaLigada*, int *);
int removerLL(QueueListaLigada*, int *);

// 2. Arrays
void iniciarA(QueueArray*, int capacidadeBuffer);
int vaziaA(QueueArray*);
void adicionarA(QueueArray*, int);
int proximoA(QueueArray*, int *);
int removerA(QueueArray*, int *);

#endif 

