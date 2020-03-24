#include<stdio.h>


int elimRepOrd (int v[], int n){
  int ind = 1;

  for(int i = 1; i < n; i++){
    if (v[i] != v[i-1]){
      v[ind++] = v[i];
    }
  }

  return ind;
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

    n = elimRepOrd(v, i);

    for(int i = 0; i < n; i++){
      printf("%d ", v[i]);
    }

  }

  return 0;
}
