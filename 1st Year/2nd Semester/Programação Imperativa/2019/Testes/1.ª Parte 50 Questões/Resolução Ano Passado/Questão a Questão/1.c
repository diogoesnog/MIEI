#include<stdio.h>


int main(){
  int maior;
  int prox = 0;

  printf("Introduiz os números: ");
  scanf(" %d\n", &prox);
  maior = prox;

  while (prox != 0){
    scanf(" %d", &prox);
    if (prox > maior) maior = prox;
  }

  printf("%d\n", maior);

  return 0;

}
