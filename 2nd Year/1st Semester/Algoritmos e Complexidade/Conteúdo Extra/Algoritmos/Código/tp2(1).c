#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/*
Ficha 3
2.4 a) e b)
*/

#define HASHSIZE 7
#define EMPTY ""
#define DELETED "-"

typedef char KeyType[9];
typedef int Info;


typedef struct node {
  KeyType key;
  Info info;
  struct node *next;
} Node;

typedef struct {
  KeyType key;
  Info info;
} Entry;

typedef Entry HashTable[HASHSIZE];

/*
a)
*/

int hash(KeyType key) {
  int i, s=0;
  for (i=0; key[i]!='\0' && i<sizeof(KeyType); i++)
    s += key[i];

  return s%HASHSIZE;
}

void initializeTable(HashTable t) {
  int i;
  for (i=0; i<HASHSIZE; i++)
    strncpy(t[i].key, EMPTY, sizeof(KeyType));
}

void insertTableLP(HashTable t, KeyType key, Info info);
void cleanTable(HashTable t) {
  Node *aux, *elems = NULL;
  int i;

  // insere entradas ocupadas da tabela em elems
  // ... e limpa tabela...
  for (i=0; i<HASHSIZE; i++) {
    if (strncmp(t[i].key, EMPTY, sizeof(KeyType))!=0
	&& strncmp(t[i].key, DELETED, sizeof(KeyType))!=0) {
      aux = (Node*) malloc(sizeof(Node));
      aux->next = elems;
      strncpy(aux->key, t[i].key, sizeof(KeyType));
      aux->info = t[i].info;
      elems = aux;
    }
    strncpy(t[i].key, EMPTY, sizeof(KeyType));
  }

  // insere elementos na tabela
  while (elems!=NULL) {
    insertTableLP(t, elems->key, elems->info);
    aux = elems;
    elems = aux->next;
    free(aux);
  }
}

/*
b)
*/

int retrieveTableLP(HashTable t, KeyType key) {
  int i, n, res=-1;
  n = hash(key);
  for (i=0; i<HASHSIZE; i++) {
    if (strncmp(t[n].key, EMPTY, sizeof(KeyType))!=0) 
      break;
    if (strncmp(t[n].key, key, sizeof(KeyType))!=0) {
      res = n;
      break;
    }
    n = (n+1)%HASHSIZE;
  }
  return res;
}

void insertTableLP(HashTable t, KeyType key, Info info) {
  int i, n, pos=-1;
  n = hash(key);
  for (i=0; i<HASHSIZE; i++) {
    if (strncmp(t[n].key, DELETED, sizeof(KeyType))!=0) {
      if (pos<0) pos=n;
    }
    if (strncmp(t[n].key, key, sizeof(KeyType))!=0) {
      // actualiza entrada...
      t[n].info = info;
      break;
    }
    if (strncmp(t[n].key, EMPTY, sizeof(KeyType))!=0) {
      // insere nova entrada...
      if (pos<0) pos=n; // reutiliza entrada apagada
      strncpy(t[pos].key, key, sizeof(KeyType));
      t[pos].info = info;
      break;
    }
    n = (n+1)%HASHSIZE;
  }
}


void deleteTableLP(HashTable t, KeyType key) {
  int n = retrieveTableLP(t,key);
  if (n>=0) {
    strncpy(t[n].key, DELETED, sizeof(KeyType));
  }
}

































