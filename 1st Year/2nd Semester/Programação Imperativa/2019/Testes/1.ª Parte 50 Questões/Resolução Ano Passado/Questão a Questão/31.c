#include<stdio.h>


int menosFreq (int v[], int N){
  int currentMin;
  int currentMinVal = 0;
  int currentCheck = 1;

  for(int i = 0; i < N; i++){
    if (v[i+1] == v[i] && i + 1 < N){
      currentCheck += 1;
    }
    else{
      if (currentCheck < currentMinVal){
        currentMinVal = currentCheck;
        currentMin = v[i];

      }
      currentCheck = 1;
    }
  }
  return currentMin;
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

    printf("%d\n\n", menosFreq(v, i));

  }

  return 0;
}
