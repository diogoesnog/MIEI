#include<stdio.h>


int comuns (int a[], int na, int b[], int nb){

  int conta = 0;
  int e;

  for(int i = 0; i < na; i++){

    e = 0;
    for(int ap = 0; ap < i; ap++){
      if(a[ap] == a[i]) e = 1;
    }

    if (e == 0){
      for(int j = 0; j < nb && a[i] != b[j-1]; j++){
        if (a[i] == b[j]){
          conta++;
        }
      }
    }

  }

  return conta;
}


int main(){

  int a[500];
  int b[500];

  int n = 1;
  while (n) {

  printf("Primeiro array(termina com 0): \n");
  int prox = 1;
  int i = 0;

  while(prox != 0){
    scanf("%d", &prox);
    if (prox != 0) a[i++] = prox;
  }

  printf("Segundo array: \n");

  prox = 1;
  int j = 0;

  while(prox != 0){
    scanf("%d", &prox);
    if (prox != 0) b[j++] = prox;
  }

  printf("%d\n", comuns(a, i, b, j));
  }

  return 0;
}
