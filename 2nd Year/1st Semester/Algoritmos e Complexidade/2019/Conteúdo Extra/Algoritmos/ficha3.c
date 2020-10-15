#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//Ficha3
//1:
//1
typedef struct btree{
	int value;
	struct btree *left, *right;
} Node, *BTree;

//a)
int size(BTree a){
	if(!a) return 0;
	else return (size(a->left)+size(a->right)+1);
}
/*
(1)T(n)={ teta(1) se n=0
	    { teta(1) + T(n-1) se n>0
	    Pior caso da funçao: teta(n)
(2)T(n)={ teta(1) se n=0
		{ teta(1) + 2T(n/2) se n>0
		Melhor caso da funçao: teta(n)
funçao: teta(n)
*/

//b)
int altura(BTree a){
	if(!a) return 0;
	else{
		int l=altura(a->left)+1;
		int r=altura(a->right)+1;
		return (l>r ? l : r);
	}
}
/*
(1)T(n)={ teta(1) se n=0
	    { teta(1) + T(n-1) se n>0
	    Pior caso da funçao: teta(n)
(2)T(n)={ teta(1) se n=0
		{ teta(1) + 2T(n/2) se n>0
		Melhor caso da funçao: teta(n)
funçao: teta(n)
*/

//c)
BTree add (BTree a, int x){
	BTree aux=a;
	BTree ant=a;
	BTree v=(BTree)malloc(sizeof(Node));
	v->value=x;
	v->left=NULL;
	v->right=NULL;
	while(a){
		ant=a;
		if(a->value>x) a=a->left;
		else a=a->right;
	}
	if(ant==NULL) return v;
	if(ant->value>x) ant->left=v;
	else ant->right=v;
	return aux;
}
/*
(1)T(n)={ teta(1) se n=0
	    { teta(1) + T(n-1) se n>0
	    Pior caso neste caso: O(n)
	    melhor caso neste caso: phi(1)
(2)T(n)={ teta(1) se n=0
		{ teta(1) + 2T(n/2) se n>0
		sempre igual neste caso: teta(log2n)
*/

//d)
int search (BTree a, int x){
	while(a){
		if(x==a->value) return 1;
		else if(x>a->value) a=a->right;
			 else a=a->left;
	}
	return 0;
}
/*
(1)T(n)={ teta(1) se n=0
	    { teta(1) + T(n-1) se n>0
	    Melhor caso neste caso: phi(1)
	    Pior caso neste caso: O(n)
(2)T(n)={ teta(1) se n=0
		{ teta(1) + 2T(n/2) se n>0
		Melhor caso neste caso: phi(1)
		Pior caso neste caso: O(log2n)
*/

//e)
int max (BTree a){
	while(a && a->right) a=a->right;
	return a->value;
}
/*
(1)T(n)={ teta(1) se n=0
	    { teta(1) + T(n-1) se n>0
	    Melhor caso neste caso: phi(1)
	    Pior caso neste caso: O(n)
(2)T(n)={ teta(1) se n=0
		{ teta(1) + 2T(n/2) se n>0
		sempre igual neste caso: O(log2n)
*/

//2
int balanceada (BTree a) {
	if (a) {
		int l = altura (a->left);
		int r = altura (a->right);
		return ((abs (l-r) <= 1) && balanceada (a->left) && balanceada (a->right));
	}
	else return 1;
}
//a e b)
/*Melhor caso(nao estar balenciada na raiz): T(n)=phi(n)
  Pior caso(estar balenciada): O(nlog2n)
       T(n)={ teta(1) se n=0
			{ teta(n) + 2T(n/2) se n>0
*/

//c)
int balanceadaAux (BTree a, int *p) {
	int l, r;
	return 0;
}

int balanceadaC (BTree a) {
	int p;
	return (balanceadaAux (a, &p));
}

void printBTree(BTree a){
	if(a){
	printf("%d\n", a->value);
	printBTree(a->left);
	printBTree(a->right);
	}
}

//2:
typedef struct buffer{
	int *values;
	int used;
	int size;
} *Buffer;
//1) (ver caderno)
/*
(a):
A: add:phi(1) O(n) rem:teta(1)
B: add:teta(1) rem:teta(n)
(b):
A:phi(n) O(n²)
B:phi(n) O(n²)
*/

//2)
#define PARENT(i) (i-1)/2 // o indice do array começa em 0
#define LEFT(i) 2*i + 1
#define RIGHT(i) 2*i + 2

typedef int Elem; // elementos da heap.
typedef struct {
	int size;
	int used;
	Elem *values;
} Heap;
//a) ver caderno
//b)
int minHeapOK (Heap h){
	int i;
	for(i=h.used;i>0;i--){
		if(h.values[i]<h.values[PARENT(i)]) return 0;
	}
	return 1;
}
//c.i)
Heap * newHeap (int size){
	Heap * new=(Heap *)malloc(sizeof(Heap));
	new->size=size;
	new->used=0;
	new->values=(Elem *)malloc(size*sizeof(int));
	return new;
}
//teta(1)

//c.iii)
void swap(int * v,int i, int j){
	int aux=v[i];
	v[i]=v[j];
	v[j]=aux;
}

void bubbleUp(int v[], int p){
	int i;
	for(i=p;v[i]<v[PARENT(i)];i=PARENT(i)) swap(v,i,PARENT(i));
}
//phi(1) O(log2n)

//c.ii)
int insertHeap(Heap h, int x){
	if(h.used==h.size) return 1;
	h.values[h.used]=x;
	bubbleUp(h.values,h.used);
	h.used++;
	return 0;
}
//phi(1) O(log2n)

//c.v)
void bubbleDown(int v[], int i, int used){
	while((LEFT(i)<used && v[i]>v[LEFT(i)]) || (RIGHT(i)<used && v[i]>v[RIGHT(i)])){
		if(RIGHT(i)<used && v[RIGHT(i)]<v[LEFT(i)]){
			swap(v,i,RIGHT(i));
			i=RIGHT(i);
		}else{
			swap(v,i,LEFT(i));
			i=LEFT(i);
		}
	}
}
//phi(1) O(log2n)

//c.iv)
int extractMin(Heap h, int *v){
	if(h.used==0) return 1;
	*v=h.values[0];
	h.used--;
	h.values[0]=h.values[h.used];
	bubbleDown(h.values,0,h.used);
	return 0;
}
//phi(1) O(log2n)

//3:
//1) (ver caderno)
/*2) * 0  1  2  3  4  5  6
	   27 1  15 14 3  9  5

	 * 0  1  2  3  4  5  6
	      1  15 14 3
       
       0  1  2  3  4  5  6
          15 14 3
*/

//3)
#define HASHSIZE 31 // número primo
#define EMPTY ""
#define DELETED "-"
typedef char KeyType[9];
typedef void *Info;

typedef struct entry {
	KeyType key;
	Info info;
} Entry, HashTable[HASHSIZE];

int condition (char *s) { //condicionamento das chaves visto nao serem numeros
	int r = 0;
	while (*s) {
	r += *s++;
	}
	return r;
}
//a)
int Hash(KeyType k){		// funçao de hash
	int r=condition(k);
	return r % HASHSIZE;
}
//teta(k) sendo k o tamanho da chave

void InitializeTable(HashTable h){ // inicializa a tabela de hash
	int i;
	for(i=0;i<HASHSIZE;i++) h[i].info=EMPTY;
}
//teta(HASHSIZE)

void ClearTable(HashTable h){ // limpa a tabela de hash
	free(h);
}
//teta(1)

//b)
// insere uma nova associaçao entre uma chave nova e a restante informaçao
void InsertTable_LP(HashTable h, KeyType k, Info inf){
	int i=0,v=Hash(k);
	while(h[v].info!=EMPTY && i<HASHSIZE && h[v].info!=DELETED){
		v++; 
		i++;
		if(v>HASHSIZE) v=0;
	}
	if(i!=HASHSIZE){
		strcpy(h[v].key,k);
		h[v].info=inf;
	}
}
// phi(1) O(o) sendo o nº de valores ocupados no cluster a partir de v

// apaga o elemento de chave k da tabela
void DeleteTable_LP(HashTable h, KeyType k){
	int i,v=Hash(k);
	for(i=0; i<HASHSIZE && h[v].info!=EMPTY; i++){
		if(h[v].info!=DELETED && strcmp(h[v].key,k)==0) {h[v].info=DELETED; break;}
		v++;
		if(v>HASHSIZE) v=0;
	}
}
// phi(1) O(o+r) sendo r nº de valores removidos no cluster a partir de v

// procura na tabela o elemento de chave k, e retorna o ı́ndice da tabela
// aonde a chave se encontra (ou -1 caso k nao exista)
int RetrieveTable_LP(HashTable h, KeyType k){
	int i,v=Hash(k);
	for(i=0; i<HASHSIZE && h[v].info!=EMPTY; i++){
		if(strcmp(h[v].key,k)==0 && h[v].info!=DELETED) return v;
		else v++;
		if(v>HASHSIZE) v=0;
	}
	return -1;
}
// phi(1) O(o+r)

//c)
// funçao de hash
int Hash_QP(KeyType k, int i){
	int r=condition(k);
	r = r % HASHSIZE;
	r = pow (r,i);
	while(r>HASHSIZE) r=r-HASHSIZE;
	return r;
}
//phi(k+HASHSIZE/r)

// insere uma nova associaçao entre uma chave nova e a restante informaçao
void InsertTable_QP(HashTable h, KeyType k, Info inf){
	int i=0,v=Hash_QP(k,1);
	while(i<HASHSIZE){
		if(h[v].info==EMPTY || h[v].info==DELETED){
			strcpy(h[v].key,k);
			h[v].info=inf;
			break;
		}
		v=Hash_QP(k,i+2);
		i++;
	}
}
//phi(1) O(p) em que p é o nº de interaçoes ate encontrar um empty ou deleted

// apaga o elemento de chave k da tabela
void DeleteTable_QP(HashTable h, KeyType k){
	int i, v=Hash_QP(k,1);
	for(i=0; i<HASHSIZE; i++){
		if(h[v].info!=EMPTY && h[v].info!=DELETED && strcmp(h[v].key,k)==0){
			h[v].info=DELETED;
			break;
		}
		v=Hash_QP(k,i+2);
	}
}
//phi(1) O(t) em que t é o nº de interaçoes ate encontrar a chave

// procura na tabela o elemento de chave k, e retorna o ı́ndice da tabela
// aonde a chave se encontra (ou -1 caso k nao exista)
int RetrieveTable_QP(HashTable h, KeyType k){
	int i, v=Hash_QP(k,1);
	for(i=0; i<HASHSIZE; i++){
		if(h[v].info!=EMPTY && h[v].info!=DELETED && strcmp(h[v].key,k)==0) return v;
		v=Hash_QP(k,i+2);
	}
	return -1;
}
//phi(1) O(t)

//4)
typedef struct entryC {
	KeyType key;
	Info info;
	struct entryC *next;
} EntryC, *HashTableC[HASHSIZE];

//a)
// funç~ao de hash
int HashC(KeyType k){
	int r=condition(k);
	return r % HASHSIZE;
}
//teta(k) sendo k o tamanho da chave

// inicializa a tabela de hash
void InitializeTableC(HashTableC h){
	int i;
	for(i=0; i<HASHSIZE; i++){
		h[i]->info=EMPTY;
		h[i]->next=NULL;
	}
}
//teta(HASHSIZE)

// limpa a tabela de hash
void ClearTableC(HashTableC h){
	int i;
	EntryC * aux;
	for(i=0; i<HASHSIZE; i++){
		aux=h[i]->next;
		h[i]->info=EMPTY;
		while(aux){
			free(aux);
			aux=aux->next;
		}
	}
	free(h);
}
//phi(1) teta(N) seja n o nº de chaves na hashtable 

// insere uma nova associaçao entre uma chave nova e a restante informaçao
void InsertTableC(HashTableC h, KeyType k, Info inf){
	int v=HashC(k);
	if(h[v]->info==EMPTY){
		strcpy(h[v]->key,k);
		h[v]->info=inf;
	}else{
		EntryC * aux=h[v]->next;
		while(h[v]->next){
			aux=h[v]->next;
			h[v]->next=h[v]->next->next;
		}
		aux=(EntryC *)malloc(sizeof(EntryC));
		strcpy(aux->key,k);
		aux->info=inf;
		aux->next=NULL;
	}
}
//phi(1) O(N)

// apaga o elemento de chave k da tabela
void DeleteTableC(HashTableC h, KeyType k){
	int v=HashC(k);
	EntryC * aux;
	if(strcmp(h[v]->key,k)==0){
		if(h[v]->next==NULL) h[v]->info=EMPTY;
		else{
			strcpy(h[v]->key,h[v]->next->key);
			h[v]->info=h[v]->next->info;
			aux=h[v]->next;
			h[v]->next=h[v]->next->next;
			free(aux);
		}
	}else{
		if(strcmp(h[v]->next->key,k)==0){
			free(h[v]->next);
			h[v]->next=NULL;
		}else{
			while(h[v]->next){
				if(strcmp(h[v]->next->key,k)==0) break;
				else{
					aux=h[v]->next;
					h[v]->next=h[v]->next->next;
				}
			}
			aux->next=h[v]->next->next;
			free(h[v]->next);
		}
	}
}
//phi(1) O(N)

// procura na tabela o elemento de chave k, e retorna o apontador
// para a célula aonde a chave se encontra (ou NULL caso k nao exista)
EntryC *RetrieveTableC(HashTableC h, KeyType k){
	int v=HashC(k);
	if(strcmp(h[v]->key,k)==0) return h[v];
	while(h[v]->next){
		if(strcmp(h[v]->key,k)==0) break;
		else h[v]->next=h[v]->next->next;
	}
	return h[v]->next;
}
//phi(1) O(N)

//4:
typedef struct avlTree {
	int value;
	int bal;
	struct avlTree *left, *right;
} AVLNode, *AVLTree;

//1)
int alturaAVL (AVLTree a){
	int i=0;
	while(a){
		if(a->bal>0) a=a->left;
		else a=a->right;
		i++;
	}
	return i;
}
//2)
AVLTree rotateLeft(AVLTree a){
	AVLTree aux;
	if(!a || !a->right) printf("Erro\n");
	else{
		aux=a->right;
		a->right=aux->left;
		aux->left=a;
		a=aux;
	}
	return a;
}

AVLTree rotateRight(AVLTree a){
	AVLTree aux;
	if(!a || !a->left) printf("Erro\n");
	else{
		aux=a->left;
		a->left=aux->right;
		aux->right=a;
		a=aux;
	}
	return a;
}
//3)  
/*              10
			20		30
		  70  40  50
*/

int main(){
	return 0;
}