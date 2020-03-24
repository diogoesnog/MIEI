#include<stdio.h>


int cardinalMSet (int N, int v[N]){
  int soma = 0;

  for(int i = 0; i < N; i++){
    soma +=v[i];
  }

  return soma;
}


int main(){

  int v[1000];

  int n = 1;
  while (n) {

    printf("Introduza os números: (termina com -1) \n");

    int prox = 1;
    int i = 0;

    while(prox != -1){
      scanf("%d", &prox);
      if (prox != -1) v[i++] = prox;
    }

    printf("%d\n\n", cardinalMSet(i, v));

  }

  return 0;
}
