#include<stdio.h>


int comunsOrd (int a[], int na, int b[], int nb){

  int conta = 0;
  int ap = 0;
  int bp = 0;

  while(ap < na && bp < nb){
    if (a[ap] == b[bp]){
      conta++;
      ap++;
      bp++;
    }
    else if (a[ap] < b[bp]){
      ap++;
    }
    else{
      bp++;
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

  printf("%d\n", comunsOrd(a, i, b, j));

  return 0;
  }
}
