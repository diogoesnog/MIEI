#ifndef openAdressing_h
#define openAdressing_h

// Estruturas definidas

#define HASHSIZE 20
#define EMPTY " "
#define DELETED "-"
typedef char KeyType[9];
typedef void *Info;

typedef struct entry{
	KeyType chave;
	Info informacao;
} Entry, HashTable[HASHSIZE];

// Métodos a Implementar

int hash(KeyType);
void inicializarTabela(HashTable);
void limparTabela(HashTable);

// Linear probing

int hashLP(KeyType);
void inserirTabelaLP(HashTable, KeyType, Info);
void eliminarTabelaLP(HashTable, KeyType);
int procurarTabelaLP(HashTable, KeyType);

// Quadratic Probing

int hashQP(KeyType, int);
void inserirTabelaQP(HashTable, KeyType, Info);
void eliminarTabelaQP(HashTable, KeyType);
int procurarTabelaQP(HashTable, KeyType);

#endif

