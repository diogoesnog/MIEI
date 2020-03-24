#include<stdio.h>
#include<ctype.h>
#include<string.h>




int crescente (int a[], int i, int j){

  for(int c = i; c < j; c++){
    if (a[c] > a[c+1]) return 0;
  }

  return 1;

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

  int a, b;
  printf("\nOs dois indices(separados por um espaço): ");
  scanf("%d %d", &a, &b);


  printf("%d\n\n", crescente(v , a, b));

  }
}
