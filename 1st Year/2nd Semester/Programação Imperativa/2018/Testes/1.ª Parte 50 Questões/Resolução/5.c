#include <stdio.h>
#include <math.h>

int trailingZ (unsigned int n){

  int e = 0;
  int p = 2;

  while (n%p == 0 && p <= n) {
    ++e;
    p *= 2;
  }

  return e;
}


int main(){

  unsigned int n;

  int n = 1;
  while (n) {

  printf("Que número?\n");

  scanf("%u", &n);
  printf("%d\n\n", trailingZ(n));

  }
}
