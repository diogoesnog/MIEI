#include<stdio.h>


int retiraNeg (int v[], int N){
  int aux[N];
  int pAux = 0;

  for(int i = 0; i < N; i++){
    if (v[i] >= 0){
      aux[pAux++] = v[i];
    }
  }

  for(int i = 0; i < pAux; i++){
    v[i] = aux[i];
  }

  return pAux;
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

    int l = retiraNeg(v, i);
    for(int i = 0; i < l; i++){
      printf("%d ", v[i]);
    }
  }

  return 0;
}
