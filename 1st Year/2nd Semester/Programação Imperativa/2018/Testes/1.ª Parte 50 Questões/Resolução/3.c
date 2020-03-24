#include<stdio.h>


int main(){
  int maior, smaior;
  int prox = 0;

  scanf(" %d\n", &prox);
  maior = prox;

  scanf(" %d\n", &prox);
  if (prox > maior) {
    smaior = maior;
    maior = prox;
  }
  else smaior = prox;

  while (prox != 0){
    scanf(" %d", &prox);
    if (prox > maior) {
      smaior = maior;
      maior = prox;
    }
    else if (prox < maior && prox > smaior){
      smaior = prox;
    }
  }

  printf("%d\n", smaior);

  return 0;

}
