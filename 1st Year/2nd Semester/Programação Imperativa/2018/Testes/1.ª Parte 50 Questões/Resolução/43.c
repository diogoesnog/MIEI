#include<stdio.h>


int intersectSet (int N, int v1[N], int v2[N], int r[N]){

  for(int i = 0; i < N; i++){
    r[i] = v1[i] && v2[i];
    //if (v1[i] == 1 || v2[i] == 1) r[i] = 1;
    //else r[i] = 0;                                 ambas funcionam
  }

  return 0;
}


int main(){

  int a[500];
  int b[500];
  int r[500];

  int n = 1;
  while (n) {

    printf("Primeiro array(acaba com 2): \n");
    int prox = 1;
    int i = 0;

    while(prox != 2){
    scanf("%d", &prox);
      if (prox != 2) a[i++] = prox;
    }

    printf("Segundo array(acaba com 2): \n");

    prox = 1;
    int j = 0;

    while(prox != 2){
      scanf("%d", &prox);
      if (prox != 2) b[j++] = prox;
    }

    intersectSet(j, a, b, r);

    for(int a = 0; a < j; a++){
      printf("%d ", r[a]);
    }

    printf("\n\n\n\n");
  }

  return 0;
}
