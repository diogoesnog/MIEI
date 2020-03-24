#include<stdio.h>

/*
int elimRep (int v[], int n){

  int aux[n];
  int pAux = 0;
  int e = 0;

  for(int i = 0; i < n; i++){
    for(int j = 0; j < pAux; j++){
      if (v[i] == aux[j]) e = 1;
    }
    if (e == 0){
      (aux[pAux++] = v[i]);
    }
    else{
      e = 0;
    }
  }

  for(int i = 0; i < pAux; i++){
    v[i] = aux[i];
  }
  return pAux;
}
*/

/*
int elimRep (int v[], int n){

  int end = n - 1;
  int e = 0;
  int i;

  for(i = 1; i <= end; i++){
    for(int j = 0; j < i; j++){
      if(v[i] == v[j]) e = 1;
    }
    if (e == 1){
      swap(v, i--, end--);
      e = 0;
    }
  }

  return i;
}
*/

void swap (int v[], int x, int y){
  int troca = v[x];
  v[x] = v[y];
  v[y] = troca;
}

int elimRep (int v[], int n){

  int e = 0;
  int i, ind;


  for(i = 1, ind = 1; i < n; i++){
    for(int j = 0; j < ind; j++){
      if(v[i] == v[j]) e = 1;
    }
    if (e == 0){
      v[ind++] = v[i];
    }
    else{
      e = 0;
    }
  }

  return ind;

}



int main(){

  int v[1000];

  int n = 1;
  while (n) {

    printf("\nIntroduza os números: (termina com 0) \n");

    int prox = 1;
    int i = 0;

    while(prox != 0){
      scanf("%d", &prox);
      if (prox != 0) v[i++] = prox;
    }

    n = elimRep(v, i);

    for(int i = 0; i < n; i++){
      printf("%d ", v[i]);
    }

  }

  return 0;
}
