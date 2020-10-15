#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define HASHSIZE 31 //Nº primo
#define EMPTY ""
#define DELETED "-"
typedef char keyType[9];
typedef void *Info;

typedef struct entry{
    keyType key;
    Info info;
}Entry, HashTable[HASHSIZE];

// a)
int hash(keyType k){
    int i, sum=0;
    for(i=0;i<9 && k[i];i++){
        sum += k[i];
        
    }
    return (sum%HASHSIZE);
}

void initializeTable(HashTable h){
   
    int i;
    for(i=0;i<HASHSIZE;i++){
        strcpy(h[i].key,EMPTY);
      //  h[i].info = (char*)malloc((sizeof(char)));
      //  strcpy(h[i].info,EMPTY);
    }
    
}

void clearTable(HashTable h){
    initializeTable(h);
}

void insertTable_LP(HashTable h, keyType k, Info i){
    int c = hash(k);
    
    int j=0, flag =0;
    while(j<HASHSIZE && (!flag)){
        if (!(strcmp(h[c].key,EMPTY)) || !(strcmp(h[c].key,DELETED))){
            strcpy(h[c].key,k);
            h[c].info = i;
            flag =1;
        }
        else if (c==(HASHSIZE-1)) c=0;
        else c++;
        j++;
    }
}


void deleteTable_LP(HashTable h,keyType k){
    int c = hash(k);
    printf("Hash code %d\n",c);
    int i=0, flag=0;
    while(i<HASHSIZE && !flag){
        if(!strcmp(h[c].key,k)){
            printf("Igual\n");
            strcpy(h[c].key,DELETED);
            flag = 1;
        }
        else if(c==(HASHSIZE-1)) c=0;
        else c++;
        i++;
    }
}

// procura na tabela o elemento de chave k, e retorna o ndice da tabela
// aonde a chave se encontra (ou -1 caso k n~ao exista)
int retrieveTable_LP(HashTable h, keyType k){
    int c = hash(k);
    int i=0,flag =0,pos=-1;
    while(i<HASHSIZE && !flag){
        if(!strcmp(h[c].key,k)){
            pos = c;
            flag = 1;
        } else if(c==(HASHSIZE-1)) c=0;
        else c++;
        i++;
    }
    
    return pos;
}


// c)
int hash_QP(keyType k){
    int i, sum =0;
    for(i=0;i<9 && k[i];i++){
        sum += k[i];
    }
   
    return (sum%HASHSIZE);

}

void insertTable_QP(HashTable h, keyType k, Info inf){
    int c = hash_QP(k);
    int i = 0, flag = 1;
    while (i<HASHSIZE && flag){
        int r = c + (i*i);
        if (!(strcmp(h[r].key,EMPTY)) || !(strcmp(h[r].key,DELETED))){
            strcpy(h[r].key,k);
            h[r].info = inf;
            flag = 0;
        }
        else if (r==(HASHSIZE-1)) c=0;
        i++;
    }
}

void deleteTable_QP(HashTable h, keyType k){
    int c = hash_QP(k);
    int i = 0, flag =1;
    while (i<HASHSIZE && flag){
        int r = c + (i*i);
        if (!(strcmp(h[r].key,k))){
            strcpy(h[r].key,DELETED);
            h[r].info = "";
            flag = 0;
        } 
        else if(c==(HASHSIZE-1)) c=0;
        i++;
    }
}

int retrieveTable_QP(HashTable h, keyType k){
    int c = hash_QP(k);
    int i = 0, flag =-1;
    while(i<HASHSIZE && (flag == -1)){
        int r = c + (i*i);
        if(!(strcmp(h[r].key,k))) flag = r;
        else if (c==(HASHSIZE-1)) c=0;
        i++;
    }
    return flag;
}

// Imprime a hashTable
void printTabela(HashTable h){
    int i;
    for(i=0;i<HASHSIZE;i++){      
        printf("Info da posição %d com key %s \n",i,h[i].key);
    }
}

int main(){
    
    HashTable h;
    Info i = "hello";

    initializeTable(h);
    
    keyType k = "a";
    keyType k1 = "sarah";
    keyType k2 = "lucia";
    keyType k3 = "armindo";
    keyType k4 = "DIOGO";
    keyType k5 = "TIAGO";
    insertTable_LP(h,k,i);

    //deleteTable_LP(h,k1);
    //int x = retrieveTable_QP(h,k1);
    //printf("Posição %d com key= %s\n\n",x,k1);
    int y = hash(k);
    printf("Hash %d\n",y);
    //printTabela(h);
    return 0;
}