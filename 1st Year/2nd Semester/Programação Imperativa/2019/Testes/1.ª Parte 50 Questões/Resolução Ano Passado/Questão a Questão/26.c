#include<stdio.h>
#include<ctype.h>
#include<string.h>




void insere (int v[], int N, int x){

  int i = 0;
  while(i < N && x > v[i]) i++;

  int j;
  for(j = N; j > i; j--){
    v[j] = v[j-1];
  }
  v[i] = x;
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

  printf("\nQue número quer inserir: ");
  scanf("%d", &prox );

  insere(v, i, prox);

  for(int j = 0; j <= i; j++)
    printf("%d ", v[j]);
  }
}
