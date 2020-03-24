#include<stdio.h>


int maxCresc (int v[], int N){
  int currentMaxVal = 0;
  int currentCheck = 1;

  for(int i = 0; i < N; i++){
    if (v[i+1] > v[i] && i + 1 < N){ // nos teste assumem maior ou igual
      currentCheck += 1;
    }
    else{
      if (currentCheck > currentMaxVal){
        currentMaxVal = currentCheck;
      }
      currentCheck = 1;
    }
  }
  return currentMaxVal;
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

    printf("%d\n\n", maxCresc(v, i));

  }

  return 0;
}
