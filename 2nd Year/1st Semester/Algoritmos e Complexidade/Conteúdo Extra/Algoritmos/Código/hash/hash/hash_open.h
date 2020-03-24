#define HASHSIZE    31
#define EMPTY       ""
#define DELETED     "-"

typedef char KeyType[9];

typedef void *Info;

typedef struct entry {
  KeyType  key;
  Info info;
} Entry;

typedef Entry *HashTable;

int Hash(KeyType);
void InitializeTable(HashTable);
void ClearTable(HashTable);

void InsertTable_LP(HashTable, KeyType, Info);
void DeleteTable_LP(HashTable, KeyType);
int RetrieveTable_LP(HashTable, KeyType);

void InsertTable_QP(HashTable, KeyType, Info);
void DeleteTable_QP(HashTable, KeyType);
int RetrieveTable_QP(HashTable, KeyType);