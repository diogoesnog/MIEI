#ifndef closeAdressing_h
#define closeAdressing_h

// Estruturas definidas

#define HASHSIZE 20
typedef char KeyType[9];
typedef void *Info;

typedef struct entry{
	KeyType chave;
	Info informacao;
	struct entry *proximo;
} Entry, *HashTable[HASHSIZE];

// Métodos a Implementar

int hash(KeyType);
void inicializarTabela(HashTable);
void limparTabela(HashTable);
void inserirTabela(HashTable,KeyType,Info);
Entry* procurarTabela(HashTable,KeyType);

#endif

