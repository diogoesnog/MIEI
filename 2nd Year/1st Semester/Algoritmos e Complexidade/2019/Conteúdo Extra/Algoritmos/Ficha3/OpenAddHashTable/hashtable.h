#ifndef hashtable_h
#define hashtable_h

#define HASHSIZE 7
#define KEYSIZE 9
#define EMPTY    ""
#define DELETED  "-"

typedef char KeyType[9];
typedef void *Info;

typedef struct hashTable *HashTable;

HashTable InitializeTable(void);

void InsertTableLP(HashTable, KeyType, Info);
void DeleteTableLP(HashTable, KeyType);
Info RetrieveTableLP(HashTable, KeyType);

void InsertTableQP(HashTable, KeyType, Info);
void DeleteTableQP(HashTable, KeyType);
Info RetrieveTableQP(HashTable, KeyType);

void ClearTable(HashTable);
void Print(HashTable);

#endif