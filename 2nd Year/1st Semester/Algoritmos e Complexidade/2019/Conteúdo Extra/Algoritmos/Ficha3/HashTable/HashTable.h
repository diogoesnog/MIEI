#ifndef HashTable_h
#define HashTable_h

#define HASHSIZE 7
#define KEYSIZE 9

typedef char KeyType[KEYSIZE];
typedef void *Info;

typedef struct hashTable *HashTable;

HashTable InitializeTable(void);
void InsertTable(HashTable, KeyType, Info);
void DeleteTable(HashTable, KeyType);
Info RetrieveTable(HashTable, KeyType);
void ClearTable(HashTable);
void Print(HashTable);

#endif 

