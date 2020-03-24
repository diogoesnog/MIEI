#include<stdio.h>


int minInd (int v[], int n){

  int currentMin = v[0];
  int currentInd = 0;

  for(int i = 1; i < n; i++){
    if (v[i] < currentMin){
      currentMin = v[i];
      currentInd = i;
    }
  }

  return currentInd;
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
