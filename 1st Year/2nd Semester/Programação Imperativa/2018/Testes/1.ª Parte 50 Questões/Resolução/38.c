#include<stdio.h>


void somasAc (int v[], int Ac [], int N){

  int last = 0;

  for(int i = 0; i < N; i++){
    Ac[i] = last + v[i];
    last = Ac[i];
  }
}


int main(){

  int v[1000];

  int n = 1;
  while (n) {

    printf("Introduza os números: (termina com 0) \n");

    int prox = 1;
    int i = 0;

    while(prox != 0){
      scanf("%d", &prox);
      if (prox != 0) v[i++] = prox;
    }

    printf("%d\n", minInd(v, i));

  }

  return 0;
}
