#include<stdio.h>
#include<stdlib.h>


int unionMSet (int N, int v1[N], int v2[N], int r[N]){

  for(int i = 0; i < N; i++){
    r[i] = (v1[i] + v2[i]);
  }

  return 0;
}


int main(){

  int a[500];
  int b[500];
  int r[500];

  int n = 1;
  while (n) {

    printf("Primeiro array(acaba com -1): \n");
    int prox = 1;
    int i = 0;

    while(prox != -1){
    scanf("%d", &prox);
      if (prox != -1) a[i++] = prox;
    }

    printf("Segundo array(acaba com -1): \n");

    prox = 1;
    int j = 0;

    while(prox != -1){
      scanf("%d", &prox);
      if (prox != -1) b[j++] = prox;
    }

    unionMSet(j, a, b, r);

    for(int a = 0; a < j; a++){
      printf("%d ", r[a]);
    }

    printf("\n\n\n\n");
  }

  return 0;
}
