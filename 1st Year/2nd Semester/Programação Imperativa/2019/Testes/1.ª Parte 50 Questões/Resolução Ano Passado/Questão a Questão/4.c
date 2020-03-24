#include<stdio.h>

int bitsUm(unsigned int n){

  int a = 0;

  for(int i = 0; n > 0; i++, n/=2){
    if (n%2 == 1) ++a;
  }

  return a;
}

int main(){
  unsigned int n;

  int x = 1;
  while (x) {

  printf("Que número?\n");
  scanf("%u", &n);
  printf("%d\n\n", bitsUm(n));

  }
}
