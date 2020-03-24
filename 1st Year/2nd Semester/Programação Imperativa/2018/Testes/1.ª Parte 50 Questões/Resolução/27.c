#include<stdio.h>


void merge (int r [], int a[], int b[], int na, int nb){


  int i = 0;
  int ia, ib;
  ia = ib = 0;



  while(ib < nb && ia < na){
    if (a[ia] < b[ib]) r[i++] = a[ia++];
    else r[i++] = b[ib++];
  }


  if (ia == na){
    while(ib < nb){
      r[i++] = b[ib++];
    }
  }
  else{
    while(ia < na){
      r[i++] = a[ia++];
    }
  }

}



int main(){

  int a[500];
  int b[500];
  int r[1000];

  int n = 1;
  while (n) {

  printf("Primeiro array: \n");
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

  merge(r, a, b, i, j);

  for(int c = 0; c < i + j; c++){
    printf("%d ", r[c]);
  }

  printf("\n\n");

  }
}
